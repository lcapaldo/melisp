#ifndef MEL_LIST_H
#define MEL_LIST_H
#include "memory.h"
#include "types.h"

//void mel_dolist(struct mel_value* list, (void)(f*)(struct mel_value* v));
//struct mel_value*  mel_maplist(struct mel_pool* p, struct mel_value* list, (void)(f*)(struct mel_value* v));
struct mel_value* mel_cdr(struct mel_value* list);

struct mel_value* mel_car(struct mel_value* list);
#endif

