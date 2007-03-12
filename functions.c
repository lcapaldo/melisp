#include "functions.h"
#include "list.h"
struct mel_value* mel_make_fn(struct mel_pool* p, struct mel_value* expr) {
  struct mel_value* rv;
  struct mel_value* arg_list;
  struct mel_value* closure = 0;
  if ( mel_cdr( p->env ) != 0 ) {
    closure = mel_car( mel_cdr( p->env ) );
  }
  struct mel_value* body;
  arg_list = mel_car( expr );
  body = mel_car( mel_cdr( expr ) );
  rv = mel_cons(p, arg_list, mel_cons(p, body, mel_cons(p, closure, 0)));
  rv->mel_type = mel_lisp_funt;
  return rv;
}

void mel_push_activation_frame( struct mel_pool* p, struct mel_value* func, struct mel_value* args) {
  struct mel_value* arg_names = mel_car( func );
  struct mel_value* e = mel_zip(p, arg_names, args);
  struct mel_value* close = mel_car( mel_cdr( mel_cdr( func ) ) );
  struct mel_value* total_e = mel_append(p, e, close);
  p->env->value.pair_val.snd = mel_cons(p, total_e, p->env->value.pair_val.snd);

}


void mel_pop_activation_frame(struct mel_pool* p) {
  p->env->value.pair_val.snd = mel_cdr( p->env->value.pair_val.snd );
}

