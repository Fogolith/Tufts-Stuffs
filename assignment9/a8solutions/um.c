            /* Implementation of the Universal Machine */

/* Written by Norman Ramsey for a programming contest in July, 2006.
   Adapted for 64-bit hardware in November, 2008. This code was never
   intended to be seen by students.  It is, however, a reasonable
   example of efficient code written by an experienced C89 programmer */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "umsegment.h"
#include "um.h"

/* A UM segment is represented as a pointer to the second element
   of a C array of type uint32_t*.  The first element contains 
   number of bytes in the array */

static Umsegment_T dupseg(Umsegment_T seg) { /* duplicate a UM segment */
  uint32_t len = seg[-1];
  Umsegment_T s2 = malloc(len);
  assert(s2);
  memcpy(s2, seg-1, len);
  return s2+1;
}

/* In C99 these macros would more properly be static inline functions,
   except macros RA, RB, and RC, which refer to lvalues */

#define SEGMENT(N) ((N)==0 ? prog : Umsegment_of_id(amap, (N)))
#define OP(N) ((Um_Opcode)((N)>>28))
#define A(N) (((N) >> 6) & 0x7)
#define B(N) (((N) >> 3) & 0x7)
#define C(N) (((N) >> 0) & 0x7)
#define RA (regs[A(instruction)])
#define RB (regs[B(instruction)])
#define RC (regs[C(instruction)])

uint64_t instructions_decoded = 0; /* instrumentation! */

void Um_run(Um_program prog) {
  Umsegment_Map amap = Umsegment_newmap(); /* mapping from 32-bit IDs to pointers */
  uint32_t regs[8];
  memset(regs, 0, sizeof(regs)); /* per UM spec, regs must be initialized to zero */
  Um_instruction *pc = prog;
  uint64_t decoded = 0; /* local cache for instructions_decoded */
  for (;;) {
    Um_instruction instruction = *pc++;
    decoded++;

    switch(OP(instruction)) {
      case CMOV:     if (RC != 0) RA = RB; break;
      case SLOAD:    RA = SEGMENT(RB)[RC]; break;
      case SSTORE:   SEGMENT(RA)[RB] = RC; break;
      case ADD:      RA = RB + RC; break;
      case MUL:      RA = RB * RC; break;
      case DIV:      RA = RB / RC; break;
      case NAND:     RA = ~(RB & RC); break;
      case HALT:     Umsegment_freemap(&amap); free(prog-1);
                     instructions_decoded += decoded;
                     return; 
      case ACTIVATE: RB = Umsegment_new(amap, RC); break;
      case INACTIVATE:  Umsegment_inactivate(amap, RC); break;
      case OUT:   assert((RC & 255) == RC); putchar((char)RC); fflush(stdout);
                  break;
      case IN:;   int i = getchar();
                  if (i == EOF)
                    RC = ~0;
                  else
                    RC = (uint32_t)i;
                  break;
      case LOADP: if (RB != 0) { /* optimization: don't copy SEGMENT(0) to itself */
                    free(prog-1);
                    prog = dupseg(SEGMENT(RB));
                  }
                  pc = prog + RC;
                  break;
      case LV:;   unsigned ra = (instruction >> 25) & 0x7;
                  regs[ra] = (instruction << 7) >> 7;
                  break;
      default: assert(0);
    }
  }
}
