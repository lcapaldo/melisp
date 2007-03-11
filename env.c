#include "env.h"
#include "types.h"
#include "list.h"
static struct mel_value* lookup_r(struct mel_pool* p, struct mel_value* name, struct mel_value* env);
struct mel_value* mel_lookup(struct mel_pool* p, struct mel_value* name, struct mel_value* env) {
  return lookup_r(p, name, mel_car( env ));
}


static struct mel_value* lookup_r(struct mel_pool* p, struct mel_value* name, struct mel_value* env) {
  if( env == 0 ) return 0; 
  if( mel_sym_eq(mel_car( mel_car( env ) ), name) ) {
    return mel_cdr( mel_car( env ) );
  } else {
    return lookup_r(p, name, mel_cdr( env ));
  }
}





struct mel_value* mel_set_global(struct mel_pool* p, struct mel_value* name, struct mel_value* val, struct mel_value* env) {
  env->value.pair_val.fst = mel_cons(p, mel_cons(p, name, val ), mel_car( env ));
  return env;
}

struct mel_value* mel_standard_env(struct mel_pool* p) {
  struct mel_value* env = mel_cons(p, 0, 0);
  return mel_set_global(p, mel_cdr(mel_read(p, "bar")), mel_alloc_float(p, 2.3), mel_set_global(p, mel_cdr(mel_read(p, "foo" ) ), mel_alloc_int(p, 7), env));
}


