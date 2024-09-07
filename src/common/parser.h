#ifndef COMMON_PARSER_H
#define COMMON_PARSER_H

#define NUM_PATTERN 150
#define PATTERN_LENGTH 990
struct OPT {
  int option_b;
  int option_e;
  int option_E;
  int option_s;
  int option_t;
  int option_T;
  int option_n;
  int option_v;
  int option_i;
  int option_c;
  int option_l;
  int option_h;
  int option_o;
  int Parser_Error;
  char e_pattern[NUM_PATTERN][PATTERN_LENGTH];
  int e_pattern_flag;
  int pattern_num;
};

struct OPT Parser(int argc, char *argv[], struct OPT Ent_Opt, int grep_util_ID);
struct OPT F_Option_pattern_set(char *filename, struct OPT Ent_Opt, char *argv);

#endif  // COMMON_PARSER_H
