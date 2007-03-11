#ifndef MEL_TYPES_H
#define MEL_TYPES_H
enum { mel_strt, mel_intt, mel_flot, mel_pairt, mel_funt, mel_symt, mel_chart, mel_envt };



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
    struct mel_pair pair_val;
  } value;
};

#endif
