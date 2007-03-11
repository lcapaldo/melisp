#include "symbols.h"
char* mel_sym_to_cstr( struct mel_value* sym ) {
  static char s[2048];
  int i = 0;
  struct mel_value* c = sym;
  while( c ) {
    s[i++] = c->value.pair_val.fst->value.char_val.val;
    c = c->value.pair_val.snd;
  }

  s[i] = '\0';
  return s;
}

