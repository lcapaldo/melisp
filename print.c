#include "print.h"
static void print_int( struct mel_value* value );
static void print_dotted_pair( struct mel_value* value );
static void print_pair( struct mel_value* value );
static void print_list( struct mel_value* value );
static void print_sym( struct mel_value* value );
static void print_float( struct mel_value* value );
static void print_string( struct mel_value* value );
static void print_cfunc( struct mel_value* value );
static void print_char( struct mel_value* value );
static void print_lispfun( struct mel_value* value );
void mel_print( struct mel_value* value ) {
  if( value == 0 ) {
    printf("nil");
    return;
  }

  switch( value->mel_type ) {
    case mel_pairt:
      print_pair( value );
      break;
    case mel_intt:
      print_int( value );
      break;
    case mel_flot:
      print_float( value );
      break;
    case mel_symt:
      print_sym( value );
      break;
    case mel_strt:
      print_string( value );
      break;
    case mel_cfunt:
      print_cfunc( value );
      break;
    case mel_chart:
      print_char( value );
      break;
    case mel_lisp_funt:
      print_lispfun( value );
      break;
    default:
      break;
  }
}

static void print_int( struct mel_value* value ) {
  printf("%d", value->value.int_val.val);
}

static void print_pair( struct mel_value* value ) {
  if( value->value.pair_val.snd == 0 || value->value.pair_val.snd->mel_type == mel_pairt ) {
    // It's probably a list
    print_list( value );
  } else {
    // a dotted pair
    print_dotted_pair( value );
  }
}

static void print_list( struct mel_value* value ) {
  struct mel_value* cursor = value;
  printf("(");
  
  while( cursor != 0 ) {
    mel_print( cursor->value.pair_val.fst );
    cursor = cursor->value.pair_val.snd;
    if( cursor != 0 ) { printf(" "); }
  }

  printf(")");
}

static void print_dotted_pair( struct mel_value* value ) {
  printf("(");
  mel_print( value->value.pair_val.fst );
  printf(" . ");
  mel_print( value->value.pair_val.snd );
  printf(")");
}

static void print_sym( struct mel_value* value ) {
  struct mel_value* cursor = value;
  while( cursor != 0 ) {
    printf("%c", cursor->value.pair_val.fst->value.char_val.val);
    cursor = cursor->value.pair_val.snd;
  }
}

static void print_float( struct mel_value* value ) {
  printf("%f", value->value.flo_val.val);
}

static void print_string( struct mel_value* value ) {
  printf("\"");
  struct mel_value* cursor = value;
  while( cursor != 0 ) {
    printf("%c", cursor->value.pair_val.fst->value.char_val.val);
    cursor = cursor->value.pair_val.snd;
  }

  printf("\"");
}

static void print_cfunc( struct mel_value* value ) {
  static int len = sizeof(void *) * 2;
  static char fmt[128];
  sprintf(fmt, "#<c-function 0x%%0%dx>", len);
  printf(fmt, (unsigned int)value->value.cfun_val.cfun);
}

static void print_char( struct mel_value* value ) {
  printf("?%c", value->value.char_val.val);
}

static void print_lispfun( struct mel_value* value ) {
  printf("#<lambda: ");
  mel_print( mel_car( value ) );
  printf(" -> ");
  mel_print( mel_car ( mel_cdr( value ) ) );
  if( mel_car( mel_cdr( mel_cdr( value ) ) ) ) {
    printf(" closure: ");
    mel_print( mel_car( mel_cdr( mel_cdr( value ) ) ) );
  }
  printf(">");
}

