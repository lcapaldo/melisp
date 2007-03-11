#include "env.h"
struct mel_value* mel_lookup(struct mel_pool* p, char *name, struct mel_value* env) {
  return 0;
}

void mel_set_global(struct mel_pool* p, char *name, struct mel_value* val, struct mel_value* env) {
  struct mel_value* sym_name = mel_read(p, name)->value.pair_val.snd;
  env->value.pair_value.fst = mel_cons(p, mel_cons(p, sym_name, val), env->value.pair_value.fst);
}

struct mel_value* mel_standard_env(struct mel_pool* p) {
  struct mel_value* env = mel_cons(p, 0, 0);
  mel_set_global(p, "a", mel_alloc_int(p, 1), env);
  return env;
}


