#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "um-load.h"
#include "um-seqi.h"

Um_instruction *Um_load(const char *file) {
  struct stat buf; // file metadata
  int rc = stat(file, &buf);
  if (rc != 0) {
    perror(file);
    exit(1);
  }
  size_t len = buf.st_size; // bytes in file
  FILE *fp = fopen(file, "rb");
  assert(len % 4 == 0);
  Um_instruction *a = malloc(len+4);
  assert(a);
  *a++ = len; /* size in BYTES */
  for (unsigned i = 0; i < len / 4; i++) {
    unsigned A, B, C, D;
    A = getc(fp);
    B = getc(fp);
    C = getc(fp);
    D = getc(fp);
    a[i] = (A << 24) | (B << 16) | (C << 8) | D;
  }
  fclose(fp);
  return a;
}

Um_instruction *Um_load_file(FILE *fp) {
  Seq_T instructions = Seq_new(200);
  for (;;) {
    int A, B, C, D;
    A = getc(fp);
    if (A == EOF) break;
    B = getc(fp);
    assert (B != EOF);
    C = getc(fp);
    assert (C != EOF);
    D = getc(fp);
    assert (D != EOF);
    emit(instructions, (A << 24) | (B << 16) | (C << 8) | D);
  }
  int len = Seq_length(instructions);
  Um_instruction *seg = malloc((len+1)*sizeof(*seg));
  assert(seg);
  *seg++ = len * sizeof(*seg); /* size in BYTES */
  for (int i = 0; i < len; i++)
    seg[i] = (unsigned long)Seq_get(instructions, i);
  return seg;
}
