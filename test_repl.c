#include <stdio.h>
#include "memory.h"
#include "types.h"
#include "print.h"
#include "read.h"
#include "symbols.h"
#include "eval.h"
int main() {
  struct mel_value* s;
  struct mel_pool p;
  struct mel_value* env;
  char input[1024];
  if ( mel_init_pool(&p, 1000000) == -1 ) {
    fprintf(stderr, "Error initing pool\n");
    exit( 1 );
  }
  env = mel_standard_env(&p);
  printf("> ");
  while( fgets( input, 1024, stdin ) ) {
    if( input[0] == '!' ) {
      printf("%s\n", mel_sym_to_cstr(mel_read( &p, input + 1 )->value.pair_val.snd));
      continue;
    } else if ( input[0] == '?' ) {
      mel_print( env->value.pair_val.snd );
    }

    s = mel_read( &p, input );
    if( s->value.pair_val.fst->value.int_val.val != mel_noerr ) {
      printf("parse error\n");
    }
    mel_print( s->value.pair_val.snd );
    printf(" => ");
    mel_print( mel_eval(&p, s->value.pair_val.snd, env ) );
    printf("\n> ");
  }

  return 0;
} 
