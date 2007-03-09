#include <stdio.h>
#include "memory.h"
#include "types.h"

int main() {
  struct mel_value* s;
  struct mel_pool p;
  mel_init_pool(&p, 10000);
  s = mel_create_string(&p, "Hello, world!");
  
  return 0;
} 
