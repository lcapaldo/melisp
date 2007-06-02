#include "env.h"
#include "types.h"
#include "list.h"
#include "symbols.h"
#include "eval.h"
#include "print.h"
#include <stdlib.h>
static struct mel_value* lookup_global_r(struct mel_pool* p, struct mel_value* name, struct mel_value* env);
static struct mel_value* lookup_local_r(struct mel_pool* p, struct mel_value* name, struct mel_value* env);
static struct mel_value* add( struct mel_pool* p, struct mel_value* args);
static struct mel_value* mul( struct mel_pool* p, struct mel_value* args);
static struct mel_value* cons(struct mel_pool* p, struct mel_value* args);
static struct mel_value* car(struct mel_pool* p, struct mel_value* args);
static struct mel_value* cdr(struct mel_pool* p, struct mel_value* args);
static struct mel_value* string_to_list(struct mel_pool* p, struct mel_value* args);
static struct mel_value* eval(struct mel_pool* p, struct mel_value* args);
static struct mel_value* list(struct mel_pool* p, struct mel_value* args);
static struct mel_value* id(struct mel_pool* p, struct mel_value* args);
static struct mel_value* obj_count(struct mel_pool* p, struct mel_value* args);
static struct mel_value* print_memory(struct mel_pool* p, struct mel_value* args);
static struct mel_value* print(struct mel_pool* p, struct mel_value* args);
static struct mel_value* eq(struct mel_pool* p, struct mel_value* args);
static struct mel_value* quit(struct mel_pool* p, struct mel_value* args);
struct mel_value* mel_lookup(struct mel_pool* p, struct mel_value* name) {
  struct mel_value* rv = 0;
  if( mel_cdr( p->env ) != 0 ) {
    rv = lookup_local_r(p, name, mel_car( mel_cdr( p->env ) ));
  }
  if( rv == 0 ) {
    return lookup_global_r(p, name, mel_car( p->env ));
  } else {
    return rv;
  }
}


static struct mel_value* lookup_global_r(struct mel_pool* p, struct mel_value* name, struct mel_value* env) {
  if( env == 0 ) return 0; 
  if( mel_sym_eq(mel_car( mel_car( env ) ), name) ) {
    return mel_cdr( mel_car( env ) );
  } else {
    return lookup_global_r(p, name, mel_cdr( env ));
  }
}

static struct mel_value* lookup_local_r(struct mel_pool* p, struct mel_value* name, struct mel_value* env) {
  if( env == 0 ) return 0; 
  if( mel_sym_eq(mel_car( mel_car( env ) ), name) ) {
    return mel_cdr( mel_car( env ) );
  } else {
    return lookup_local_r(p, name, mel_cdr( env ));
  }
}




struct mel_value* mel_set_global(struct mel_pool* p, struct mel_value* name, struct mel_value* val) {
  p->env->value.pair_val.fst = mel_cons(p, mel_cons(p, name, val ), mel_car( p->env ));
  return p->env;
}

struct mel_value* mel_standard_env(struct mel_pool* p) {
  p->env = mel_cons(p, 0, 0);
  mel_set_global(p, mel_cdr(mel_read(p, "+")), mel_alloc_cfun(p, add));
  mel_set_global(p, mel_cdr(mel_read(p, "*")), mel_alloc_cfun(p, mul));
  mel_set_global(p, mel_cdr(mel_read(p, "nil")), 0);
  mel_set_global(p, mel_cdr(mel_read(p, "cons")), mel_alloc_cfun(p, cons));
  mel_set_global(p, mel_cdr(mel_read(p, "car")), mel_alloc_cfun(p, car));
  mel_set_global(p, mel_cdr(mel_read(p, "cdr")), mel_alloc_cfun(p, cdr));
  mel_set_global(p, mel_cdr(mel_read(p, "string->list")), mel_alloc_cfun(p, string_to_list));
  mel_set_global(p, mel_cdr(mel_read(p, "copy-list")), mel_alloc_cfun(p, string_to_list));
  mel_set_global(p, mel_cdr(mel_read(p, "eval")), mel_alloc_cfun(p, eval));
  mel_set_global(p, mel_cdr(mel_read(p, "list")), mel_alloc_cfun(p, list));
  mel_set_global(p, mel_cdr(mel_read(p, "id")), mel_alloc_cfun(p, id));
  mel_set_global(p, mel_cdr(mel_read(p, "object-count")), mel_alloc_cfun(p, obj_count));
  mel_set_global(p, mel_cdr(mel_read(p, "print-memory")), mel_alloc_cfun(p, print_memory));
  mel_set_global(p, mel_cdr(mel_read(p, "print")), mel_alloc_cfun(p, print));
  mel_set_global(p, mel_cdr(mel_read(p, "quit")), mel_alloc_cfun(p, quit));
  mel_set_global(p, mel_cdr(mel_read(p, "=")), mel_alloc_cfun(p, eq));


  return p->env; 
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

static struct mel_value* mul( struct mel_pool* p, struct mel_value* args) {
  int res = 1;
  double dres = 1.0;
  int n_dbls = 0;

  struct mel_value* c = args;
  while( c != 0 ) {
    if ( mel_car( c )->mel_type == mel_intt ) {
      res *= mel_car( c )->value.int_val.val;
      dres *= mel_car( c )->value.int_val.val;
    } else if( mel_car( c )->mel_type == mel_flot ) {
      dres *= mel_car( c )->value.flo_val.val;
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
static struct mel_value* string_to_list1( struct mel_pool* p, struct mel_value* arg ) {
  if( arg == 0 ) { return 0; }
  return mel_cons(p, mel_car( arg ), string_to_list1(p, mel_cdr( arg )));
}

static struct mel_value* string_to_list(struct mel_pool* p, struct mel_value* args) {
  struct mel_value* arg = mel_car( args );
  return mel_cons(p, mel_car( arg ), string_to_list1(p, mel_cdr( arg ) ));
}

static struct mel_value* eval(struct mel_pool* p, struct mel_value* args) {
  return mel_eval(p, mel_car( args ));
}

static struct mel_value* list(struct mel_pool* p, struct mel_value* args) {
  return args;
}

static struct mel_value* id(struct mel_pool* p, struct mel_value* args) {
  return mel_car( args );
}

static struct mel_value* obj_count(struct mel_pool* p, struct mel_value* args) {
  return mel_alloc_int(p, p->obj_count);
}

static struct mel_value* print_memory(struct mel_pool* p, struct mel_value* args) {
  struct mel_value* i; 
  int cnt = p->obj_count;
  for( i = p->start; i < (struct mel_value*)p->start + (cnt * sizeof(struct mel_value)); i++ ) {
    mel_print( i );
    printf("\n");
  }
  return 0;
}

static struct mel_value* print( struct mel_pool* p, struct mel_value* args ) {
  mel_print( mel_car( args ) );
  printf("\n");
  return 0;
}

static struct mel_value* quit(struct mel_pool* p, struct mel_value* args) {
  exit( 0 );
}
static struct mel_value* eq(struct mel_pool* p, struct mel_value* args) {
  if( mel_equal( *mel_car( args ), *mel_car( mel_cdr( args ) ) )) {
      return args;
    } else {
      return 0;
    }
}


