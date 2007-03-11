#ifndef MEL_READ_H
#define MEL_READ_H
#include "types.h"
#include "memory.h"
struct mel_value* mel_read(struct mel_pool* p, char* s);
enum { mel_noerr, mel_eof, mel_err };
#endif
