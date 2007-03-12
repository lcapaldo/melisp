#ifndef MEL_FUNCTIONS_H
#define MEL_FUNCTIONS_H
#include "memory.h"
#include "types.h"
struct mel_value* mel_make_fn(struct mel_pool* p, struct mel_value* expr);
void mel_push_activation_frame( struct mel_pool* p, struct mel_value* func, struct mel_value* args);
void mel_pop_activation_frame(struct mel_pool* p);
#endif
