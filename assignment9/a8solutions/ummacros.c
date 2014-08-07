/****************** Universal Machine Macro Assembler *****************/
// macro instructions

#include <assert.h>
#include <stdint.h>

#include "fmt.h"

#include "ummacros.h"
#include "bitpack.h"

/*****************************************************************************/
// functions and definitions from the lab on unit-testing the UM

typedef uint32_t Um_instruction;

#define T Umsections_T

static Um_instruction three_register(Um_Opcode op, int ra, int rb, int rc) 
{
  uint64_t word = 0;
  word = Bitpack_newu(word, 4, 28, op);
  word = Bitpack_newu(word, 3, 6, ra);
  word = Bitpack_newu(word, 3, 3, rb);
  word = Bitpack_newu(word, 3, 0, rc);
  return (Um_instruction) word;
}

static Um_instruction loadval(unsigned ra, unsigned val) {
  uint64_t word = 0;
  word = Bitpack_newu(word,  4, 28, LV);
  word = Bitpack_newu(word,  3, 25, ra);
  word = Bitpack_newu(word, 25,  0, val);
  return (Um_instruction) word;
}

static inline void emit(T asm, Um_instruction w) {
  Umsections_emit_word(asm, w);
}

/*****************************************************************************/
// regular instructions and macro instructions

static void register_op(T asm, Um_Opcode operator,
                        Ummacros_Reg A, Ummacros_Reg B, Ummacros_Reg C) {
  assert(asm);
  assert(operator < LV);
  emit(asm, three_register(operator, A, B, C));
}

static void must_have_temp(T asm, int temporary, const char *s) {
  if (temporary == -1)
    Umsections_error(asm,
        Fmt_string("Cannot implement %s without a temporary register", s));
}

void Ummacros_op(T asm, Ummacros_Op operator, int tmp,
                 Ummacros_Reg A, Ummacros_Reg B, Ummacros_Reg C) {
  assert(asm);
  // careful here in case A == B or A == C, especially with SUB
  switch (operator) {
  case COM: // justification: x = x & x, so ~x = ~(x & x)
    register_op(asm, NAND, A, B, B);
    break;
  case MOV: // justification: x = ~(~x)
    emit(asm, three_register(NAND, A, B, B));
    emit(asm, three_register(NAND, A, A, A));
    break;
  case NEG: // justification: -x = ~x + 1
    must_have_temp(asm, tmp, "two's-complement negation");
    register_op(asm, NAND, tmp, B, B);
    Ummacros_load_literal(asm, -1, A, 1);
    register_op(asm, ADD, A, A, tmp);
    break;
  case SUB: // justification: x - y = (x + ~y) + 1
    must_have_temp(asm, tmp, "subtraction");
    register_op(asm, NAND, tmp, C, C);
    register_op(asm, ADD, A, B, tmp);
    Ummacros_load_literal(asm, -1, tmp, 1);
    register_op(asm, ADD, A, A, tmp);
    break;
  case AND: // justification: x & y = ~(~(x & y))
    register_op(asm, NAND, A, B, C);
    register_op(asm, NAND, A, A, A);
    break;
  case OR:  // justification: x | y = ~(~x & ~y)
    must_have_temp(asm, tmp, "bitwise or");
    register_op(asm, NAND, tmp, B, B);
    register_op(asm, NAND, A, C, C);
    register_op(asm, NAND, A, tmp, A);
    break;
  default:
    assert(0);
    break;
  }
}

void Ummacros_load_literal(T asm, int tmp, Ummacros_Reg A, uint32_t k) {
  // best case: small unsigned literal, single instruction
  // next best case: small negative literal, load complement then complement
  // worst case: big literal, requires multiply and add
  assert(asm);
  if (Bitpack_fitsu(k, 25)) { // then k = getu(k, 25, 0)
    emit(asm, loadval(A, k));
  } else if (Bitpack_fitsu(~k, 25)) { // then k = ~getu(~k, 25, 0)
    emit(asm, loadval(A, ~k));
    emit(asm, three_register(NAND, A, A, A));
  } else { // justification: k = getu(k, 16, 16) << 16 + getu(k, 16, 0)
    must_have_temp(asm, tmp, "loading a wide value");
    uint32_t hi = Bitpack_getu(k, 16, 16);
    uint32_t lo = Bitpack_getu(k, 16, 0);
    emit(asm, loadval(A, hi));
    emit(asm, loadval(tmp, 1<<16));
    emit(asm, three_register(MUL, A, A, tmp)); // hi in correct spot in A
    emit(asm, loadval(tmp, lo));
    emit(asm, three_register(ADD, A, A, tmp));
  }
}
