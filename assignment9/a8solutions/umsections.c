/****************** Universal Machine Macro Assembler *****************/
// sections

#include <string.h>

#include "umsections.h"

#include "table.h"
#include "fmt.h"
#include "seq.h"
#include "mem.h"
#include "atom.h"
#include "assert.h"

#include "bitpack.h"

/*****************************************************************************/
// Sequence of named sections

#define T Umsections_T

struct T {
  Table_T sections;   // all sections, keyed by (atom) name of section
  Seq_T secnames;     // char * section names in order of appearance, 
                      // which is also the order of layout at link time
  Seq_T instructions;  // current section; element is word cast to pointer
  const char *secname; // name of current section (key in 'sections' table)
  int (*error)(void *errstate, const char *message);
  void *errstate;
};
  // Invariant: a name appears in 'secnames' iff it is a key in 'sections'.
  // Invariant: instructions == Table_get(sections, secname).

T Umsections_new(const char *secname, 
                 int (*error)(void *errstate, const char *message),
                 void *errstate)
{
  assert(sizeof(uintptr_t) >= sizeof(Umsections_word)); // required or casts fail
  T asm;
  NEW(asm);
  asm->sections = Table_new(5, NULL, NULL);
  asm->secnames = Seq_new(5);
  asm->error     = error;
  asm->errstate  = errstate;
  Umsections_section(asm, secname); // treat the initial section like any other
  return asm;
}

static void free_section(const void *key, void **value, void *cl) {
  // function is used with Table_map to free every section in asm->sections
  Seq_T *sp = (Seq_T *)value;
  Seq_free(sp);
  (void)cl; (void)key; // no warnings
}

void Umsections_free(T *p) {
  assert(p && *p);
  Table_map((*p)->sections, free_section, NULL);
  Table_free(&(*p)->sections);
  Seq_free(&(*p)->secnames);
  FREE(*p);
}

void Umsections_section(T asm, const char *secname) {
  assert(asm && secname);
  secname = Atom_string(secname);
  Seq_T instructions = Table_get(asm->sections, secname);
  if (instructions == NULL) {
    instructions = Seq_new(1000);
    Table_put(asm->sections, secname, instructions);
    Seq_addhi(asm->secnames, (void*)secname);
  }
  asm->instructions = instructions;
  asm->secname      = secname;
}
    
int Umsections_error(const T asm, const char *msg) {
  assert(asm);
  return asm->error(asm->errstate, msg);
}

/****************************************************************/
/******* access to words *******/

static inline Umsections_word get_inst(Seq_T instructions, int i) {
  return (Umsections_word)(uintptr_t) (Seq_get(instructions, i));
}

static inline void put_inst (Seq_T instructions, int i, Umsections_word inst) {
  Seq_put(instructions, i, (void *)(uintptr_t) inst);
}

void Umsections_map(T asm, void apply(const char *name, void *cl), void *cl) {
  assert(asm);
  for (int i = 0; i < Seq_length(asm->secnames); i++) {
    apply(Seq_get(asm->secnames, i), cl);
  }
}
  
static Seq_T contents(T asm, const char *name) {
  assert(asm);
  assert(name);
  Seq_T contents = Table_get(asm->sections, Atom_string(name));
  if (contents == NULL)
    Umsections_error(asm, Fmt_string("No section named '%s'.", name));
  return contents;
}

int Umsections_length(T asm, const char *name) {
  return Seq_length(contents(asm, name));
}

static inline void boundscheck(T asm, const char *name, int i, Seq_T words) {
  if (i < 0 || i >= Seq_length(words))
    Umsections_error(asm, Fmt_string("Index %d into section '%s' is out of bounds.",
                                i, name));
}

Umsections_word Umsections_getword(T asm, const char *name, int i) {
  Seq_T words = contents(asm, name);
  boundscheck(asm, name, i, words);
  return get_inst(words, i);
}

void Umsections_putword(T asm, const char *name, int i, Umsections_word w) {
  Seq_T words = contents(asm, name);
  boundscheck(asm, name, i, words);
  put_inst(words, i, w);
}

void Umsections_emit_word(T asm, uint32_t data) {
  assert(asm);
  Seq_addhi(asm->instructions, (void *)(uintptr_t)data);
}

/****************************************************************/
/******* writing the UM binary *******/

static void write_words(Seq_T words, FILE *output) {
  int n = Seq_length(words);
  for (int i = 0; i < n; i++) {
    Umsections_word inst = get_inst(words, i);
    for (int lsb = 24; lsb >= 0; lsb -= 8)
      putc(Bitpack_getu(inst, 8, lsb), output);
  }
}

void Umsections_write(T asm, FILE *output) {
  assert(output && asm);
  int n = Table_length(asm->sections);
  assert(n == Seq_length(asm->secnames));
  for (int i = 0; i < n; i++)
    write_words(contents(asm, Seq_get(asm->secnames, i)), output);
}
