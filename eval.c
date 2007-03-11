#include "eval.h"

static struct mel_value* eval_special_form(struct mel_pool* p, struct mel_value* expr);
static struct mel_value* eval_function_call(struct mel_pool* p, struct mel_value* expr);
struct mel_value* mel_eval(struct mel_pool* p, struct mel_value* expr, struct mel_value* env) {
  switch( expr->mel_type ) {
    case mel_intt:
    case mel_chart:
    case mel_symt:
    case mel_flot:
    case mel_strt:
      return expr;
    case mel_pairt:
      if ( is_special_form( expr->value.pair_val.fst ) ) {
        return eval_special_form( expr );
      } else {
        return eval_function_call( expr );
      }
      break;
  }
}


