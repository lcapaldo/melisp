#include "symbols.h"
char* mel_sym_to_cstr( struct mel_value* sym ) {
  static char s[2048];
  int i = 0;
  struct mel_value* c;
  c  = sym;
  while( c != 0 ) {
    s[i] = c->value.pair_val.fst->value.char_val.val;
    c = c->value.pair_val.snd;
    i += 1;
  }

  s[i] = '\0';
  return strdup(s);
}
int mel_sym_eq_to_cstr(struct mel_value* sym, char *name) {
  if( strcmp( mel_sym_to_cstr( sym ), name ) == 0 ) {
    return 1;
  } else {
    return 0;
  }
}  

int mel_sym_eq(struct mel_value* sym1, struct mel_value* sym2) {
  if( sym1 == sym2 ) {
    return 1;
  }

  if( sym1 == 0 || sym2 == 0 ) {
    return 0;
  }

  if( sym1->mel_type != mel_symt || sym2->mel_type != mel_symt ) {
    return 0;
  }

  if( mel_car( sym1 )->value.char_val.val == mel_car( sym2 )->value.char_val.val ) {
    return mel_sym_eq( mel_cdr( sym1 ), mel_cdr( sym2 ) );
  } else {
    return 0;
  }

}

