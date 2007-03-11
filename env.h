#ifndef MEL_ENV_H
#define MEL_ENV_H
#include "types.h"
#include "memory.h"
struct mel_value* mel_lookup(struct mel_pool* p, char *name, struct mel_value* env);
struct mel_value* mel_standard_env(struct mel_pool* p);
#endif
