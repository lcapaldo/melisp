#include <stdio.h>
#include "memory.h"
#include "types.h"
#include "print.h"
int main() {
  struct mel_value* s;
  struct mel_pool p;
  char input[1024];
  if ( mel_init_pool(&p, 10000) == -1 ) {
    fprintf(stderr, "Error initing pool\n");
    exit( 1 );
  }
  printf("> ");
  while( fgets( input, 1024, stdin ) ) {
    s = mel_read( &p, input );
    mel_print( s->value.pair_val.snd );
    printf("\n> ");
  }

  return 0;
} 
