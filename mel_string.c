#include "mel_string.h"
mel_string_appendc(mel_value* v, char c) {
  if ( v->type != mel_str ) {
    error();
  }
  if( v->value.str_val.capa > v->value.str_val.len ) {
    v->value.str_val.val[v->value.str_val.len++] = c;
  } else {
    grow_it();
  }
}


