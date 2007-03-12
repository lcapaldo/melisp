#include "memory.h"

int mel_init_pool( struct mel_pool* pool, int count ) { 
  void* buf = 0;
  if ( ! ( buf = malloc( sizeof(struct mel_value) * count ) ) ) {
    return -1;
  }

  pool->start = buf;
  pool->current = buf;
  pool->end = buf + sizeof(struct mel_value) * count;
  pool->env = mel_standard_env(pool);
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
  cons_cell->mel_type = mel_pairt;
  cons_cell->value.pair_val.fst = first;
  cons_cell->value.pair_val.snd = second;
  return cons_cell;
}

struct mel_value* mel_alloc_int(struct mel_pool* p, int v) {
  struct mel_value* r;
  r = mel_alloc_value(p);
  r->mel_type = mel_intt;
  r->value.int_val.val = v;
  return r;
}

struct mel_value* mel_alloc_char(struct mel_pool* p, char v) {
  struct mel_value* r;
  r = mel_alloc_value(p);
  r->mel_type = mel_chart;
  r->value.char_val.val = v;
  return r;
}
struct mel_value* mel_alloc_float(struct mel_pool* p, double v) {
  struct mel_value* r;
  r = mel_alloc_value(p);
  r->mel_type = mel_flot;
  r->value.flo_val.val = v;
  return r;
}

struct mel_value* mel_create_string1(struct mel_pool* p, char* s); // internal
struct mel_value* mel_create_string(struct mel_pool* p, char* s) {
  struct mel_value* r;
  if( *s == '\0' ) {
    r = mel_cons(p, 0, 0);
    r->mel_type = mel_strt;
  } else {
    r = mel_create_string1(p, s);
  }

  return r;
}

struct mel_value* mel_create_string1(struct mel_pool* p, char* s) {
  if ( *s == '\0' ) {
    return 0;
  } else {
    struct mel_value* cons;
    cons = mel_cons(p, mel_alloc_char(p, *s), mel_create_string1(p, s + 1));
    cons->mel_type = mel_strt;
    return cons;
  }
}

struct mel_value* mel_alloc_cfun(struct mel_pool* p, struct mel_value* (*f)(struct mel_pool* p, struct mel_value* args)) {
  struct mel_value* v = mel_alloc_value(p);
  v->mel_type = mel_cfunt;
  v->value.cfun_val.cfun = f;
  return v;
}

