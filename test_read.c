#include <stdio.h>
#include "memory.h"
#include "types.h"

int main() {
  struct mel_value* s;
  struct mel_pool p;
  if ( mel_init_pool(&p, 10000) == -1 ) {
    fprintf(stderr, "Error initing pool\n");
    exit( 1 );
  }
  s = mel_read(&p, "(1 2 4)");
  
  return 0;
} 
