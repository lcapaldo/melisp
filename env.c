#include "env.h"
struct mel_value* mel_lookup(struct mel_pool* p, char *name, struct mel_value* env) {
  return 0;
}

void mel_set_global(struct mel_pool* p, char *name, struct mel_value* val, struct mel_value* env);
struct mel_value* mel_standard_env(struct mel_pool* p);
