#include <stdio.h>
#include "memory.h"
#include "types.h"
#include "print.h"
int main() {
  struct mel_value* s;
  struct mel_pool p;
  if ( mel_init_pool(&p, 10000) == -1 ) {
    fprintf(stderr, "Error initing pool\n");
    exit( 1 );
  }
  s = mel_read(&p, "(1 2 4)");
  printf("%d = 0\n", s->value.pair_val.fst->value.int_val.val);
  printf("%d = 1\n", s->value.pair_val.snd->value.pair_val.fst->value.int_val.val);
  mel_print( s );
  s = mel_read( &p, "anc");
  mel_print( s );
  printf("\n"); 
  return 0;
} 
