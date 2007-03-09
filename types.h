#ifndef MEL_TYPES_H
#define MEL_TYPES_H
enum mel_types { mel_str, mel_int, mel_flo, mel_pair, mel_fun, mel_sym };

struct mel_str {
  int len;
  char* val;
};

struct mel_sym {
  int len;
  char *val; // yeah its the same as a string for now
};

struct mel_int {
  int val;
};

struct mel_flo {
  double val;
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
    struct mel_str str_val;
    struct mel_sym sym_val;
    struct mel_int int_val;
    struct mel_flo flo_val;
    struct mel_pair pair_val;
  } value;
};

#endif
