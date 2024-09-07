#include <stdio.h>
#include <stdlib.h>

#include "../common/parser.h"

void Output(char *argv[], struct OPT Option);

int main(int argc, char *argv[]) {
  struct OPT Ent_Opt;
  int util_ID = 0;
  Ent_Opt = Parser(argc, argv, Ent_Opt, util_ID);
  if (Ent_Opt.Parser_Error == 0) {
    Output(argv, Ent_Opt);
  }
  return 0;
}

void Output(char *argv[], struct OPT Option) {
  int count = 1;
  FILE *file_stream;
                     if (Option.option_b == 1) {
    Option.option_n = 0;
  }
  while (argv[count]) {
    if (argv[count][0] != '\0') {
      file_stream = fopen(argv[count], "r");
      if (file_stream == NULL) {
        fprintf(stderr, "file %s open ERROR\n",
                argv[count]);  //  Проверка открытия файла
      } else {
        char Print_char = getc(file_stream);
        char Next_char = '\0';
        int empty_string = 0;
        int Fst_empty_string = 0;
        if (Print_char != EOF) {  // Если файл не пустой, работаем с ним
          int str = 1;
          if ((Option.option_n == 1) ||
              ((Option.option_b == 1) &&
               (Print_char !=
                '\n'))) {  //  Если флаг n то нумеруем первую строку
            printf("%6d\t", str);
            str++;
          }
          if (Print_char == '\n') {
            Fst_empty_string = 1;
          }
          while (Next_char != EOF) {
            Next_char = getc(file_stream);
            if (Next_char != '\n') {
              Fst_empty_string = 0;
            }
            if ((Option.option_s == 1)) {
              if ((Print_char == '\n') && (Next_char == '\n')) {
                empty_string++;
                if ((empty_string > 1) || (Fst_empty_string == 1)) {
                  while (Next_char == '\n') {
                    Next_char = getc(file_stream);
                  }
                  empty_string = 0;
                  Fst_empty_string = 0;
                }
              } else {
                empty_string = 0;
              }
            }
            if ((Option.option_e == 1) || (Option.option_E == 1)) {
              if (Print_char == '\n') {
                printf("$");
              }
            }
            if ((Option.option_t == 1) || (Option.option_T == 1)) {
              if (Print_char == '\t') {
                Print_char = 'I';
                printf("^");
              }
            }
            if (((Option.option_t == 1) || (Option.option_e == 1) ||
                 (Option.option_v == 1)) &&
                ((((int)Print_char >= 0) && ((int)Print_char <= 8)) ||
                 (((int)Print_char >= 11) && ((int)Print_char <= 31)))) {
              Print_char = Print_char + 64;
              printf("^%c", Print_char);
            } else if (((Option.option_t == 1) || (Option.option_e == 1) ||
                        (Option.option_v == 1)) &&
                       ((int)Print_char == 127)) {
              Print_char = Print_char - 64;
              printf("^%c", Print_char);
            } else {
              printf("%c", Print_char);
            }
            if (Option.option_b == 1) {
              if ((Print_char == '\n') && (Next_char != '\n') &&
                  (Next_char != EOF)) {
                printf("%6d\t", str);
                str++;
              }
            }
            if (Option.option_n == 1) {
              if ((Print_char == '\n') && (Next_char != EOF)) {
                printf("%6d\t", str);
                str++;
              }
            }
            Print_char = Next_char;
          }
        }
        if (fclose(file_stream) == EOF) {
          fprintf(stderr, "file %s close error\n", argv[count]);
          exit(1);
        }
      }
    }
    count++;
  }
}
