#include "types.h"
int mel_equal(struct mel_value v1, struct mel_value v2) {
  if( v1.mel_type != v2.mel_type ) return 0;
  switch( v1.mel_type ) {
    case mel_intt:
    return (v1.value.int_val.val == v2.value.int_val.val);
    case mel_chart:
    return (v1.value.char_val.val == v2.value.char_val.val);
    case mel_flot:
    return (v1.value.flo_val.val == v2.value.flo_val.val);
    case mel_cfunt:
    return (v1.value.cfun_val.cfun == v2.value.cfun_val.cfun);
    case mel_pairt:
    case mel_lisp_funt:
    case mel_envt:
    case mel_strt:
    case mel_symt:
    return (v1.value.pair_val.fst == v2.value.pair_val.fst &&
        v1.value.pair_val.snd == v2.value.pair_val.snd);
    default:
    return 0;
  }
}
