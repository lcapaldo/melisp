#ifndef MEL_MEMORY_H
#define MEL_MEMORY_H
#include "types.h"
#include <stdlib.h>
struct mel_pool {
  void* current;
  void* start;
  void* end;
  int obj_count;
};

int mel_init_pool( struct mel_pool* pool, int count );
void mel_free_pool( struct mel_pool* pool );
struct mel_value* mel_alloc_value( struct mel_pool* pool );
struct mel_value* mel_cons(struct mel_pool* pool, struct mel_value* first, struct mel_value* second);
struct mel_value* mel_alloc_int(struct mel_pool* p, int v);
struct mel_value* mel_alloc_float(struct mel_pool* p, double v);
#endif
