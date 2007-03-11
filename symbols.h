#ifndef MEL_SYMBOLS_H
#define MEL_SYMBOLS_H
#include "types.h"
#include "memory.h"
#include "list.h"
#include <string.h>
char* mel_sym_to_cstr( struct mel_value* sym );
int mel_sym_eq_to_cstr(struct mel_value* sym, char *name);
int mel_sym_eq(struct mel_value* sym1, struct mel_value* sym2);
#endif
