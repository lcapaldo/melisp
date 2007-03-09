#ifndef MEL_MEMORY_H
#define MEL_MEMORY_H
struct mel_pool {
  void* current;
  void* start;
  void* end;
  int obj_count;
};

int mel_init_pool( struct pool* pool, int count );
void mel_free_pool( struct mel_pool* pool );
#endif
