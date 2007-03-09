#include "read.h"
#include <ctypes.h>

static char *skip_ws(char *s);

mel_value* mel_read(char *s) {
  char* s1 = skip_ws(s);
}

static char *skip_ws(char *s) {
  char* rv = s;
  if ( ! rv ) { return rv; } 
  if( ! isspace( *rv ) ) {
    return rv;
  }
  
  while( isspace( *rv ) ) {
    rv++;
  }

  return rv;
}





