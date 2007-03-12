#include "list.h"
/*
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
*/
struct mel_value* mel_cdr(struct mel_value* list) {
  return list->value.pair_val.snd;
}

struct mel_value* mel_car(struct mel_value* list) {
  return list->value.pair_val.fst;
}


struct mel_value* mel_zip(struct mel_pool* p, struct mel_value* lst1, struct mel_value* lst2) {
  if( lst1 == 0 || lst2 == 0 ) { return 0; }
  return mel_cons(p, mel_cons(p, mel_car( lst1 ), mel_car( lst2 )), mel_zip(p, mel_cdr( lst1 ), mel_cdr( lst2 )));
}

struct mel_value* mel_append(struct mel_pool* p, struct mel_value* lst1, struct mel_value* lst2) {
  if( lst1 == 0 ) {
    return lst2;
  }

  return mel_cons(p, mel_car( lst1 ), mel_append(p, mel_cdr( lst1 ), lst2 ));
}

