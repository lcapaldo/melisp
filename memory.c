#include "memory.h"
int mel_init_pool( struct pool* pool, int count ) { 
  void* buf = 0;
  if ( ! ( buf = malloc( sizeof(struct mel_value) * count ) ) ) {
    return -1;
  }

  pool->start = buf;
  pool->current = buf;
  pool->end = buf + sizeof(struct mel_value) * count;
  pool->obj_count = 0;

  return 0;
}

void mel_free_pool( struct mel_pool* pool ) { 
  free( pool->start );
  pool->start = pool->current = pool->end = 0;
  pool->obj_count = 0;
}

struct mel_value* mel_alloc_value( struct mel_pool* pool ) {
  if( pool->current + sizeof(struct mel_value) > pool->end ) {
    // TODO: write mel_collect();
    return 0;
  } else {
   struct mel_value* r;
   r = pool->current;
   pool->current += sizeof(struct mel_value);
   pool->obj_count++;
   return r;
  }
}

struct mel_value* mel_cons(struct mel_pool* pool, struct mel_value* first, struct mel_value* second) {
  struct mel_value* cons_cell;
  cons_cell = mel_alloc_value(pool);
  cons_cell->mel_type = mel_pair;
  cons_cell->value.pair_val.fst = first;
  cons_cell->value.pair_val.snd = second;
  return cons_cell;
}

struct mel_value* mel_alloc_int(struct mel_pool* p, int v) {
  struct mel_value* r;
  r = mel_alloc_value(p);
  r->mel_type = mel_int;
  r->value.int_val = v;
  return r;
}

struct mel_value* mel_alloc_float(struct mel_pool* p, double v) {
  struct mel_value* r;
  r = mel_alloc_value(p);
  r->mel_type = mel_flo;
  r->value.flo_val = v;
  return r;
}

