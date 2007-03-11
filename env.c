#include "env.h"
#include "types.h"
#include "list.h"
#include "symbols.h"
static struct mel_value* lookup_r(struct mel_pool* p, struct mel_value* name, struct mel_value* env);
static struct mel_value* add( struct mel_pool* p, struct mel_value* args);
static struct mel_value* cons(struct mel_pool* p, struct mel_value* args);
static struct mel_value* car(struct mel_pool* p, struct mel_value* args);
static struct mel_value* cdr(struct mel_pool* p, struct mel_value* args);
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
  mel_set_global(p, mel_cdr(mel_read(p, "+")), mel_alloc_cfun(p, add), env);
  mel_set_global(p, mel_cdr(mel_read(p, "nil")), 0, env);
  mel_set_global(p, mel_cdr(mel_read(p, "cons")), mel_alloc_cfun(p, cons), env);
  mel_set_global(p, mel_cdr(mel_read(p, "car")), mel_alloc_cfun(p, car), env);
  mel_set_global(p, mel_cdr(mel_read(p, "cdr")), mel_alloc_cfun(p, cdr), env);

  return env; 
}


static struct mel_value* add( struct mel_pool* p, struct mel_value* args) {
  int res = 0;
  double dres = 0.0;
  int n_dbls = 0;

  struct mel_value* c = args;
  while( c != 0 ) {
    if ( mel_car( c )->mel_type == mel_intt ) {
      res += mel_car( c )->value.int_val.val;
      dres += mel_car( c )->value.int_val.val;
    } else if( mel_car( c )->mel_type == mel_flot ) {
      dres += mel_car( c )->value.flo_val.val;
      n_dbls++;
    } else {
      return 0;
    }
    c = mel_cdr( c );
  }

  if( n_dbls > 0 ) {
    return mel_alloc_float(p, dres);
  } else {
    return mel_alloc_int(p, res);
  }
}

static struct mel_value* cons(struct mel_pool* p, struct mel_value* args) {
  return mel_cons(p, mel_car( args ), mel_car( mel_cdr( args ) ));
}

static struct mel_value* car(struct mel_pool* p, struct mel_value* args) {
  return mel_car( mel_car( args ) );
}


static struct mel_value* cdr(struct mel_pool* p, struct mel_value* args) {
  return mel_cdr( mel_car( args ) );
}

