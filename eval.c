#include "eval.h"
#include "symbols.h"

static struct mel_value* eval_special_form(struct mel_pool* p, struct mel_value* expr, struct mel_value* env);
static struct mel_value* eval_function_call(struct mel_pool* p, struct mel_value* expr, struct mel_value* env);
static int is_special_form( struct mel_value* expr );
struct mel_value* mel_eval(struct mel_pool* p, struct mel_value* expr, struct mel_value* env) {
  switch( expr->mel_type ) {
    case mel_intt:
    case mel_chart:
    case mel_flot:
    case mel_symt:
      return mel_lookup(p, mel_sym_to_cstr( expr ), env);
    case mel_strt:
      return expr;
    case mel_pairt:
      if ( is_special_form( expr->value.pair_val.fst ) ) {
        return eval_special_form(p, expr, env );
      } else {
        return eval_function_call(p, expr, env );
      }
      break;
  }
}


static struct mel_value* eval_special_form(struct mel_pool* p, struct mel_value* expr, struct mel_value* env) {  return 0; }
static struct mel_value* eval_function_call(struct mel_pool* p, struct mel_value* expr, struct mel_value* env) {  return 0; }
static int is_special_form( struct mel_value* expr ) { return 0; }
