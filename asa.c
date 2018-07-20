#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "args.h"
#include "mem.h"
#include "buffer.h"

//==============================================================================

int Search(uint32_t pivot, uint8_t can){

  switch(pivot){
    // 1-WAY:
    case 'M': if(can == 'H')                                           return 1;
    case 'W': if(can == 'P')                                           return 1;
    case 'Q': if(can == 'L')                                           return 1;
    // 2-WAY:
    case 'N': if(can == 'I' || can == 'V')                             return 1;
    case 'D': if(can == 'I' || can == 'V')                             return 1;
    case 'Y': if(can == 'I' || can == 'V')                             return 1;
    case 'K': if(can == 'F' || can == 'L')                             return 1;
    case 'E': if(can == 'F' || can == 'L')                             return 1;
    case 'C': if(can == 'T' || can == 'A')                             return 1;
    case 'H': if(can == 'M' || can == 'V')                             return 1;
    case 'F': if(can == 'K' || can == 'E')                             return 1;
    // 3-WAY:
    case 'L': if(can == 'Q' || can == 'K' || can == 'E')               return 1;
    case 'I': if(can == 'N' || can == 'D' || can == 'Y')               return 1;
    case 'P': if(can == 'R' || can == 'G' || can == 'W')               return 1;
    // 4 WAY:
    case 'V': if(can == 'N' || can == 'D' || can == 'Y' || can == 'H') return 1;
    case 'S': if(can == 'R' || can == 'G' || can == 'T' || can == 'A') return 1;
    case 'T': if(can == 'R' || can == 'G' || can == 'C' || can == 'S') return 1;
    case 'A': if(can == 'R' || can == 'G' || can == 'C' || can == 'S') return 1;
    case 'R': if(can == 'T' || can == 'A' || can == 'S' || can == 'P') return 1;
    case 'G': if(can == 'T' || can == 'A' || can == 'S' || can == 'P') return 1;
    default: break;
    }

  return 0;
  }

//==============================================================================

int main(int argc, char *argv[]){

  uint32_t  window = 0, length = 0, n, x, k;
  int32_t   pivot = 0, match = 0, limit = 0;
  BUF       *B;
  uint8_t   *bin, *sym;

  if(argc != 2){
    fprintf(stderr, "Usage: ASA [window] < in.seq > seq.txt\n");
    return EXIT_SUCCESS;
    }
  
  window = atol(argv[1]);
  length = FNBytes(stdin);

  fprintf(stderr, "Window size: %u\n", window);
  fprintf(stderr, "File length: %u\n", length);
  
  bin = (uint8_t *) Calloc(length + 1, sizeof(uint8_t));
  sym = (uint8_t *) Calloc(length + 1, sizeof(uint8_t));

  n = 0;
  B = CreateBuffer(BUF_SIZE);
  while((k = fread(B->buf, 1, B->size, stdin))){
    for(x = 0 ; x < k ; ++x){
      sym[n] = B->buf[x];
      bin[n++] = '0';
      }
    }
  RemoveBuffer(B); 

  fprintf(stderr, "String: %s\n", sym);
  fprintf(stderr, "Binary: %s\n", bin);

  for(x = 0 ; x < length ; ++x){

    pivot = sym[x];
    limit = x + 3 + window;
    for(k = x + 3 ; k < limit ; ++k){

      if(Search(pivot, sym[k]) == 1 && Search(sym[x+1], sym[k-1]) == 1 ||  Search(sym[x+2], sym[k-2]) == 1){
        bin[x] = '1';
        bin[x+1] = '1';
        bin[x+2] = '1';
        bin[k-2] = '1';
        bin[k-1] = '1';
        bin[k] = '1';
/*
        for(n = 0 ; n < window ; ++n){
          ;         

          }
*/
        }
      }
    }

  fprintf(stderr, "Binary: %s\n", bin);

  free(bin);
  free(sym);
  return EXIT_SUCCESS;
  }

//==============================================================================


 
