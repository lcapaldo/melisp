#include "read.h"
#include <ctype.h>

static char *skip_ws(char *s);

mel_value* mel_read(char *s) {
  if( ! s ) { return 0; } 
  char* s1 = skip_ws(s);
  if( ! s1 ) { return 0; }
  char* s2 = 0;
  switch( *s1 ) {
    case '(': 
      mel_read_list( s1 ); 
      break;
    case '0','1','2','3','4','5','6','7','8','9':
      mel_read_number( s1 );
      break;
    case '"':
      mel_read_string( s1 );
      break;
    default:
      mel_read_sym( s1 );
      break;
  }
}

static char *skip_ws(char *s) {
  char* rv = s;
  if ( ! rv ) { return rv; } 
  if( ! isspace( *rv ) ) {
    return rv;
  }

  while( rv && isspace( *rv ) ) {
    rv++;
  }

  return rv;
}





