#ifndef MEL_ENV_H
#define MEL_ENV_H
#include "types.h"
#include "memory.h"
#include "read.h"
#include "list.h"
struct mel_value* mel_lookup(struct mel_pool* p, struct mel_value* name, struct mel_value* env);
struct mel_value* mel_set_global(struct mel_pool* p, struct mel_value* name, struct mel_value* val, struct mel_value* env);
struct mel_value* mel_standard_env(struct mel_pool* p);
#endif
