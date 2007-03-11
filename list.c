#include "list.h"

void mel_dolist(struct mel_pool* p, struct mel_value* list, (void)(f*)(struct mel_value* v, struct mel_pool* p)) {
  struct mel_value* cursor = list;
  while( cursor ) {
    f( cursor->value.pair_val.fst, p );
    cursor = cursor->value.pair_val.snd;
  }
}

struct mel_value*  mel_maplist(struct mel_pool* p, struct mel_value* list, (struct mel_value* )(f*)(struct mel_value* v, struct mel_pool* p)) {
  if ( list ) {
  return mel_cons(p, f(list->value.pair_val.fst, p), mel_maplist(p, list->value.pair_val.snd, f));
  } else {
    return 0;
  }
}


