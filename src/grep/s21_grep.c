#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/parser.h"

struct OPT Search_String_set(char *argv[], struct OPT Option);
void Search(char *argv[], struct OPT Option);
void Print_line(char *Line);

int main(int argc, char *argv[])   {
  struct OPT Ent_Opt;
        int grep_util_ID = 1;
  Ent_Opt = Parser(argc, argv, Ent_Opt, grep_util_ID);
  if (Ent_Opt.Parser_Error == 0)          {
    Ent_Opt = Search_String_set(
        argv, Ent_Opt);  // Определяем шаблон, если парсер не нашел флаги -e,-f
    Search(argv, Ent_Opt);
           }
  return 0;
         }

struct OPT Search_String_set(char *argv[], struct OPT Option) {
  int count = 1;
  int console_pattern_flag = 0;
  int num_pattern = 0;
  while (argv[count]) {
    if (argv[count][0] != '\0') {
            if ((console_pattern_flag == 0) && (Option.e_pattern_flag == 0)) {
             int i = 0;
                 while (argv[count][i]) {
          Option.e_pattern[num_pattern][i] = argv[count][i];
          i++;
               }
                  Option.e_pattern[num_pattern][i] = '\0';
                  num_pattern++;
        console_pattern_flag = 1;
        memset(argv[count], '\0',
               strlen(argv[count]));  // Зануляем найденную опцию
        break;
      }
    }
    count++;
  }
  return Option;
}

void Search(char *argv[], struct OPT Option) {
  regex_t REGEX;
  int regflag = 0;
  char temp_line[990];
  int count = 1;
  int Success;
  int pattern_quantity;
  int file_counter = 0;
  int success_string_counter = 0;
  int string_counter = 0;
  int Compare = 0;
  int Success_flag = 1;
  regmatch_t pmatch[100];
  int eflag = 0;
  if (Option.option_v == 1) {
    Compare = REG_NOMATCH;
    Option.option_o = 0;
  }
  if (Option.option_i == 1) regflag = REG_ICASE;
  while (argv[count]) {  //  считаем количество заданных файлов
    if (argv[count][0] != '\0') {
      file_counter++;
    }
    count++;
  }
  count = 1;
  while (argv[count]) {
    if (argv[count][0] != '\0') {
      pattern_quantity = 0;
      FILE *filestream = fopen(argv[count], "r");
      if (filestream == NULL) {
        if (Option.option_s == 0) {
          fprintf(stderr, "file %s open ERROR\n",
                  argv[count]);  //  Проверка открытия файла
        }
      } else {
        int L_Success_flag = 0;
        int perevod_str_flag = 0;
        while ((!feof(filestream)) &&
               (L_Success_flag == 0)) {  //  Длина найденной строки
          if (fgets(temp_line, sizeof(temp_line), filestream) != NULL) {
            string_counter++;
            pattern_quantity = 0;
            while ((Option.e_pattern[pattern_quantity][0]) != '\0') {
              if (Option.e_pattern[pattern_quantity][0] == '\n') {
                perevod_str_flag = 1;
                if (Option.option_o == 1) (Option.option_o = 0);
              }
              if (regcomp(&REGEX, Option.e_pattern[pattern_quantity],
                          regflag) == REG_EESCAPE) {
                fprintf(stderr, "Trailing backslash ERROR\n");
                if (fclose(filestream) == EOF) {
                  if (Option.option_s == 0)
                    fprintf(stderr, "file %s close ERROR\n", argv[count]);
                  exit(1);
                }
                exit(1);
              } else {  // компилирование регулярного выражения
                Success = regexec(&REGEX, temp_line, 1, pmatch,
                                  eflag);  // поиск регулярного выражения
                Success_flag = Success_flag * Success;
                if ((perevod_str_flag == 1) && (feof(filestream)) &&
                    (Success_flag != 0) &&
                    Option.e_pattern[pattern_quantity + 1][0] == '\0') {
                  if ((Option.option_v == 0) || (Option.option_l == 0)) {
                    if (Option.option_v == 1) {
                      Success_flag = 0;
                    } else {
                      Success_flag = Compare;
                    }
                  } else {
                    Success_flag = 0;
                  }
                }
                if ((Success_flag == Compare) && (Option.option_l == 0)) {
                  if ((Option.option_c == 0) && (Option.option_o == 1) &&
                      (perevod_str_flag == 0) && (Option.option_v == 0)) {
                    if ((file_counter > 1) && (Option.option_h == 0))
                      printf("%s:", argv[count]);
                    if (Option.option_n == 1) printf("%d:", string_counter);
                    char *ps = NULL;
                    char *ps_temp = NULL;
                    ps = temp_line;
                    regfree(&REGEX);
                    while (Option.e_pattern[pattern_quantity][0] != '\0') {
                      ps_temp = Option.e_pattern[pattern_quantity];
                      regcomp(&REGEX, Option.e_pattern[pattern_quantity],
                              regflag);
                      while (regexec(&REGEX, ps, 1, pmatch, eflag) == 0) {
                        for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo;
                             i++) {
                          printf("%c", ps[i]);
                        }
                        ps += pmatch[0].rm_eo;
                        printf("\n");
                      }
                      regfree(&REGEX);
                      pattern_quantity++;
                      if (Option.e_pattern[pattern_quantity][0] != '\0') {
                        regcomp(&REGEX, Option.e_pattern[pattern_quantity],
                                regflag);
                        while (regexec(&REGEX, ps_temp, 1, pmatch, eflag) ==
                               0) {
                          for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo;
                               i++)
                            printf("%c", ps_temp[i]);
                          ps_temp += pmatch[0].rm_eo;
                          printf("\n");
                        }
                        regfree(&REGEX);
                      }
                    }
                  }
                }
                regfree(&REGEX);
                if ((Option.e_pattern[pattern_quantity][0] == '.') &&
                    (Option.e_pattern[pattern_quantity][1] == '\0') &&
                    (temp_line[1] == '\n')) {
                  Success_flag = 1;
                }
              }
              pattern_quantity++;
            }
            if ((Success_flag == Compare) && (Option.option_l == 0) &&
                (Option.option_o == 0)) {
              if ((Option.option_c == 0)) {
                if ((file_counter > 1) && (Option.option_h == 0))
                  printf("%s:", argv[count]);
                if (Option.option_n == 1) printf("%d:", string_counter);
                Print_line(temp_line);
                Success_flag = 0;
              }
            } else if ((Success_flag == Compare) && (Option.option_l == 1)) {
              L_Success_flag = 1;
            }
            if (Success_flag == Compare) success_string_counter++;
            Success_flag = 1;
          }
        }
        if (fclose(filestream) == EOF) {
          if (Option.option_s == 0)
            fprintf(stderr, "file %s close ERROR\n", argv[count]);
          exit(1);
        }
        if ((Option.option_c == 1)) {
          if ((Option.option_h == 0) && (file_counter > 1))
            printf("%s:", argv[count]);
          printf("%d\n", success_string_counter);
          success_string_counter = 0;
        }
        if ((L_Success_flag == 1) && (Option.option_l == 1))
          printf("%s\n", argv[count]);
      }
    }
    string_counter = 0;
    count++;
  }
}

void Print_line(char *Line) {
  int i = 0;
  while (Line[i] != '\0') {
    printf("%c", Line[i]);
    i++;
  }
  if (Line[i - 1] != '\n') printf("\n");
}
