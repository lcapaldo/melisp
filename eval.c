#include "eval.h"
#include "symbols.h"
#include "string.h"
#include "list.h"
#include "types.h"
#include "read.h"
#include <stdio.h>
static struct mel_value* eval_special_form(struct mel_pool* p, struct mel_value* expr);
static struct mel_value* eval_function_call(struct mel_pool* p, struct mel_value* expr);
static int is_special_form(struct mel_pool* p, struct mel_value* expr );
static struct mel_value* eval_arg_list(struct mel_pool* p, struct mel_value* args);
struct mel_value* mel_eval(struct mel_pool* p, struct mel_value* expr) {
  switch( expr->mel_type ) {
    case mel_intt:
      return expr;
    case mel_chart:
      return expr;
    case mel_flot:
      return expr;
    case mel_symt:
       return mel_lookup(p, expr);
    case mel_strt:
      return expr;
    case mel_pairt:
      if ( is_special_form(p, expr) ) {
        return eval_special_form(p, expr );
      } else {
        return eval_function_call(p, expr );
      }
      break;
  }
  return 0;
}


static struct mel_value* eval_special_form(struct mel_pool* p, struct mel_value* expr) { 

  if( mel_sym_eq( mel_car( expr ), mel_cdr(mel_read(p, "set")) ) ) {
    struct mel_value* binding;
    struct mel_value* val;
    binding = mel_car( mel_cdr( expr ) );
    val = mel_eval(p,  mel_car( mel_cdr( mel_cdr( expr ) ) ));
    mel_set_global(p, binding, val);
    return val; 
  } else if ( mel_sym_eq( mel_car( expr ), mel_cdr( mel_read(p, "quote")))) {
    return mel_car( mel_cdr( expr ) );
  } else if ( mel_sym_eq( mel_car( expr ), mel_cdr( mel_read(p, "env")))) {
    return p->env;
  } else if ( mel_sym_eq( mel_car( expr ), mel_cdr( mel_read(p, "if")))) {
    struct mel_value* when_true;
    struct mel_value* when_false;
    struct mel_value* cond;
    cond = mel_car( mel_cdr( expr ) );
    when_true = mel_car( mel_cdr( mel_cdr( expr ) ) );
    when_false = mel_car( mel_cdr( mel_cdr( mel_cdr( expr ))));
    struct mel_value* cond_val = mel_eval(p, cond);
    if( cond_val != 0 ) {
      return mel_eval(p, when_true);
    } else {
      return mel_eval(p, when_false);
    }
  } else if ( mel_sym_eq( mel_car( expr ), mel_cdr( mel_read(p, "lambda")))) {
    return mel_make_fn(p,  mel_cdr( expr ));
  }
  return 0;
}

static struct mel_value* eval_function_call(struct mel_pool* p, struct mel_value* expr) {
  struct mel_value* fname = mel_car( expr );
  struct mel_value* arg_list = eval_arg_list(p,  mel_cdr( expr ) );
  struct mel_value* f = mel_lookup(p, fname);
  if( f == 0 ) {
    printf("Think you're clever?\n");
    return 0;
  }
  if( f->mel_type == mel_cfunt ) {
    return f->value.cfun_val.cfun(p, arg_list);
  } else if( f->mel_type == mel_lisp_funt ) {
    struct mel_value* rv;
    mel_push_activation_frame(p, f, arg_list);
    mel_eval(p, mel_cdr(mel_read(p, "(env)")));
    rv = mel_eval(p, mel_car( mel_cdr( f ) ));
    mel_pop_activation_frame(p);
    return rv; 
  }

  return 0; // other functions not yet implemented
}

static struct mel_value* eval_arg_list(struct mel_pool* p, struct mel_value* args) {
  if( args == 0) { return 0; } else {
  return mel_cons(p, mel_eval(p, mel_car( args )), eval_arg_list(p, mel_cdr( args ))); }
}

static int is_special_form(struct mel_pool* p, struct mel_value* expr ) {
  if( mel_sym_eq( mel_car( expr ), mel_cdr(mel_read(p, "set"))) ) {
    return 1;
  } else if ( mel_sym_eq( mel_car( expr ), mel_cdr( mel_read(p, "quote")))) {
    return 1;
  } else if ( mel_sym_eq( mel_car( expr ), mel_cdr( mel_read(p, "env")))) {
    return 1;
  } else if ( mel_sym_eq( mel_car( expr ), mel_cdr( mel_read(p, "if")))) {
    return 1;
  } else if ( mel_sym_eq( mel_car( expr ), mel_cdr( mel_read(p, "lambda")))) {
    return 1;
  } else {
    return 0;
  }
}

