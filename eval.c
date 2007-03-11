#include "eval.h"
struct mel_value* mel_eval(struct mel_pool* p, struct mel_value* expr) {
  switch( expr->mel_type ) {
    case mel_intt:
    case mel_chart:
    case mel_symt:
    case mel_flot:
    case mel_strt:
      return expr;
      break;
  }
}
