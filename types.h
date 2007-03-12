#ifndef MEL_TYPES_H
#define MEL_TYPES_H
#include "memory.h"
enum { mel_strt, mel_intt, mel_flot, mel_pairt, mel_cfunt, mel_symt, mel_chart, mel_envt, mel_lisp_funt };



struct mel_int {
  int val;
};

struct mel_flo {
  double val;
};

struct mel_char {
  char val;
};

struct mel_value;

struct mel_cfun {
  struct mel_value* (*cfun)(struct mel_pool* p, struct mel_value* arg_list);
};

struct mel_pair {
  struct mel_value *fst;
  struct mel_value *snd;
};

struct mel_fun {
};

struct mel_value {
  int mel_type;
  union {
    struct mel_int int_val;
    struct mel_char char_val;
    struct mel_flo flo_val;
    struct mel_cfun cfun_val;
    struct mel_pair pair_val;
  } value;
};

#endif
