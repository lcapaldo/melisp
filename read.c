#include "read.h"
#include "memory.h"
#include "types.h"
#include <ctype.h>
#include "list.h"
static void skip_ws(char **s);
static struct mel_value* read_number(struct mel_pool* p, char **s, int* success);
static struct mel_value* read_expr(struct mel_pool* p, char **s, int* success);
static struct mel_value* read_string(struct mel_pool* p, char **s, int* success);
static struct mel_value* read_sym(struct mel_pool* p, char **s, int* success);
static struct mel_value* read_list(struct mel_pool* p, char **s, int* success);
static struct mel_value* read_listing(struct mel_pool* p, char **s, int* success );
static struct mel_value* read_inner_string(struct mel_pool* p, char **s, int* success);
static struct mel_value* read_quote(struct mel_pool* p, char **s, int* success);


struct mel_value* mel_read(struct mel_pool* p, char *s) {
  char *s1 = s;
  int parse_status = 0;
  struct mel_value* rv = mel_alloc_value(p);
  rv->mel_type = mel_pairt;
  skip_ws(&s1);
  rv->value.pair_val.snd = read_expr(p, &s1, &parse_status);
  rv->value.pair_val.fst = mel_alloc_int(p, parse_status);

  return rv;
}


struct mel_value* read_expr(struct mel_pool* p, char **s, int* success) {
  if ( **s == '\0' ) {
    *success = mel_eof;
    return 0;
  }
  switch( **s ) {
    case '(': 
      return read_list(p, s, success ); 
      break;
    case '0': case '1': case '2': case '3': case '4': case '5':
    case '6': case '7':case '8': case '9':
      return read_number(p, s, success );
      break;
    case '"':
      return read_string(p, s, success );
      break;
    case '\'':
      return read_quote(p, s, success );
      break;
    default:
      return read_sym(p, s, success );
      break;
  }
}

static void skip_ws(char **s) {
  char* rv = *s;
  if ( ! rv ) { return; } 
  if( ! isspace( *rv ) ) {
    return; 
  }

  while( isspace( *rv ) ) {
    rv++;
  }
  *s = rv;
}



static struct mel_value* read_list(struct mel_pool* p, char **s, int* success ) {
  if( **s != '(' ) {
    *success = mel_err;
    return 0;
  } 
  *s = *s + 1;
  skip_ws(s);
  return read_listing(p, s, success );
}

static struct mel_value* read_listing(struct mel_pool* p, char **s, int* success ) {

  if( **s == '\0' ) {
    *success = mel_err;
    return 0;
  }
  if ( **s == ')' ) {
    *s = *s + 1;
    return 0;
  }

  struct mel_value* item = read_expr(p, s, success );
  if( *success != 0 ) { return 0; }
  skip_ws( s );
  struct mel_value* rem = read_listing(p,  s, success );
  if( *success != 0 ) { return 0; }
  return mel_cons(p, item, rem);
}

static struct mel_value* read_number(struct mel_pool* p, char **s, int* success) {
  int v = 0;
  if ( **s == '\0' || !isdigit( **s )) {
    *success = mel_err;
    return 0;
  }
  while( isdigit( **s ) ) {
    v = v * 10 + (**s - '0');
    *s = *s + 1;
  }
  if( **s != '.' ) {
    return mel_alloc_int(p, v);
  } else {
    int n = 0;
    int frac = 0;
    *s = *s + 1;
    while( isdigit( **s ) ) {
      frac = frac * 10 + (**s - '0');
      n += 1;
      *s = *s + 1;
    }

    double f = (double)frac;

    int i;
    for(i = 0; i < n; i++) {
      f = f / 10;
    }

    return mel_alloc_float(p, f + (double)v);
  }
}

static struct mel_value* read_string(struct mel_pool* p, char **s, int* success) {
  *s = *s + 1;
  return read_inner_string(p, s, success);
}
static struct mel_value* read_inner_string(struct mel_pool* p, char **s, int* success)
{
  struct mel_value* rv;
  struct mel_value* c;
  if( **s == '"' ) {
    *s = *s + 1;
    return 0;
  }

  if( **s == '\0' ) {
    *success = mel_err;
    return 0;
  }

  c = mel_alloc_char(p, **s);
  *s = *s + 1;
  rv = mel_cons(p, c, read_inner_string(p, s, success));
  rv->mel_type = mel_strt;
  return rv;
}

static struct mel_value* read_sym(struct mel_pool* p, char **s, int* success)
{
  struct mel_value* rv;
  struct mel_value* c;
  if( ! isspace(**s) && **s != '(' && **s != ')' && **s != '\0') {
    c = mel_alloc_char(p, *s[0]);
    *s = *s + 1;
    rv = mel_cons(p, c, read_sym(p, s, success));
    rv->mel_type = mel_symt;
    return rv;
  } else {
    return 0;
  }
}

static struct mel_value* read_quote(struct mel_pool* p, char **s, int* success) {
  *s = *s + 1;
  struct mel_value* expr;
  skip_ws( s );
  expr = read_expr(p, s, success);
  return mel_cons(p, mel_cdr( mel_read(p, "quote") ), mel_cons(p, expr, 0));
}

