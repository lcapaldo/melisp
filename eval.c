#include "eval.h"
#include "symbols.h"
#include "string.h"
#include "list.h"
static struct mel_value* eval_special_form(struct mel_pool* p, struct mel_value* expr, struct mel_value* env);
static struct mel_value* eval_function_call(struct mel_pool* p, struct mel_value* expr, struct mel_value* env);
static int is_special_form(struct mel_value* p, struct mel_value* expr );
struct mel_value* mel_eval(struct mel_pool* p, struct mel_value* expr, struct mel_value* env) {
  switch( expr->mel_type ) {
    case mel_intt:
      return expr;
    case mel_chart:
      return expr;
    case mel_flot:
      return expr;
    case mel_symt:
       return mel_lookup(p, expr, env);
    case mel_strt:
      return expr;
    case mel_pairt:
      if ( is_special_form(p, mel_car(expr) ) ) {
        return eval_special_form(p, expr, env );
      } else {
        return eval_function_call(p, expr, env );
      }
      break;
  }
}


static struct mel_value* eval_special_form(struct mel_pool* p, struct mel_value* expr, struct mel_value* env) { 

  if( mel_sym_eq( mel_car( expr ), mel_cdr(mel_read(p, "set")) ) ) {
    env = mel_set_global( p, mel_car( mel_cdr( expr ) ), mel_eval(p,mel_car( mel_cdr( mel_cdr( expr ))), env), env);
  }
}

static struct mel_value* eval_function_call(struct mel_pool* p, struct mel_value* expr, struct mel_value* env) {  return 0; }
static int is_special_form(struct mel_value* p, struct mel_value* expr ) {
  if( mel_sym_eq( expr->value.pair_val.fst , mel_cdr( mel_read(p, "set")) ) ) {
    return 1;
  }
}

