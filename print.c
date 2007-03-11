#include "print.h"
static void print_int( struct mel_value* value );
static void print_dotted_pair( struct mel_value* value );
static void print_pair( struct mel_value* value );
static void print_list( struct mel_value* value );
void mel_print( struct mel_value* value ) {
  if( value == 0 ) {
    printf("nil");
  }

  switch( value->mel_type ) {
    case mel_pairt:
      print_pair( value );
      break;
    case mel_intt:
      print_int( value );
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

