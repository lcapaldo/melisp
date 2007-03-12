#ifndef MEL_EVAL_H
#define MEL_EVAL_H
#include "types.h"
#include "memory.h"
#include "env.h"
struct mel_value* mel_eval(struct mel_pool* p, struct mel_value* expr);
#endif
