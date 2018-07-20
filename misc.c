#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"
#include "mem.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// REPLACE STRING
//
char *Cat(char *a, char *b){
  char *c = (char *) Malloc(strlen(a)+strlen(b)+1);
  strcpy(c, a);
  strcat(c, b);
  return c;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// SIMPLE OPEN FILE
//
FILE *Fopen(const char *p, const char *m){
  FILE *F = fopen(p, m);
  if(F == NULL){
    fprintf(stderr, "[x] Error opening: %s (mode %s). Does it exists?\n", p, m);
    exit(1);
    }
  return F;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// CHECK IF FILE EXISTS WHEN PARAM FORCE IS NOT ON
//
void CheckFile(uint8_t s, char *fn){
  if(access(fn, F_OK) != -1 && s == 0){
    fprintf(stderr, "[x] Error: file %s already exists!\n", fn);
    if(access(fn, W_OK) != -1)
      fprintf(stderr, "[i] Note: file has write permission.\n[i] Tip: to force "
      "writing rerun with \"-f\" option.\n[i] On forcing, the old file will be "
      "deleted permanently.\n");
    exit(1);
    }
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// NUMBER OF BYTES IN A FILE
//
uint64_t FNBytes(FILE *F){
  uint64_t n = 0;
  fseeko(F, 0, SEEK_END);
  n = ftello(F);
  rewind(F);
  return n;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PROGRESS PERCENTAGE OF A COMPUTATION
//
void Progress(uint64_t s, uint64_t i){
  if(i%(s/100) == 0 && s > 99)
    fprintf(stderr, "Progress:%3d %%\r", (uint8_t) (i/(s/100)));
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// REVERSE A STRING
//
void ReverseStr(uint8_t *a, uint8_t *b, uint32_t s){
  uint64_t n;
  for(n = 0 ; n < s ; ++n)
    b[s-n-1] = a[n];
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

