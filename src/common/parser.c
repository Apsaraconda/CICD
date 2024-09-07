#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct OPT Parser(int argc, char *argv[], struct OPT Ent_Opt,
                  int grep_util_ID) {
  if (argc > 1) {
    Ent_Opt.option_b = 0;
    Ent_Opt.option_e = 0;
    Ent_Opt.option_E = 0;
    Ent_Opt.option_s = 0;
    Ent_Opt.option_t = 0;
    Ent_Opt.option_T = 0;
    Ent_Opt.option_n = 0;
    Ent_Opt.option_v = 0;
    Ent_Opt.option_i = 0;
    Ent_Opt.option_c = 0;
    Ent_Opt.option_l = 0;
    Ent_Opt.option_h = 0;
    Ent_Opt.option_o = 0;
    Ent_Opt.Parser_Error = 0;
    Ent_Opt.e_pattern_flag = 0;
    Ent_Opt.pattern_num = 0;
    int count = 1;
    int cat_option_order_flag = 0;
    for (int i = 0; i < NUM_PATTERN; i++) {
      Ent_Opt.e_pattern[i][0] = '\0';
    }
    while (argv[count]) {
      if ((argv[count][0] == '-') && (cat_option_order_flag == 0)) {
        for (int i = 1; argv[count][i] != '\0';
             i++) {  // Если опции слитно с одной '-', парсим их
          if (argv[count][i] == 'e') {
            Ent_Opt.option_e = 1;
            if ((grep_util_ID == 1) && (argv[count][i + 1])) {
              int j = 0;
              while (argv[count][i + 1]) {
                Ent_Opt.e_pattern[Ent_Opt.pattern_num][j] = argv[count][i + 1];
                i++;
                j++;
              }
              Ent_Opt.e_pattern[Ent_Opt.pattern_num][j] = '\0';
              Ent_Opt.pattern_num++;
              Ent_Opt.e_pattern_flag++;
              break;
            } else if ((grep_util_ID == 1) && (argv[count][i] == 'e') &&
                       (!argv[count][i + 1])) {  // записываем в шаблон
                                                 // следующий аргумент
              if (argv[count + 1]) {
                int j = 0;
                while (argv[count + 1][j]) {
                  Ent_Opt.e_pattern[Ent_Opt.pattern_num][j] =
                      argv[count + 1][j];
                  j++;
                }
                Ent_Opt.e_pattern[Ent_Opt.pattern_num][j] = '\0';
                Ent_Opt.pattern_num++;
                Ent_Opt.e_pattern_flag++;
                memset(argv[count + 1], '\0',
                       strlen(argv[count + 1]));  // Зануляем найденную опцию
              } else {  //  если ввели в конце -е без аргумента
                fprintf(stderr, "option requires an argument -- e\n");
                Ent_Opt.Parser_Error++;
              }
              break;
            }
          } else if ((argv[count][i] == 'f') &&
                     (grep_util_ID == 1)) {  //  опция -f
            if (argv[count][i + 1]) {  // шаблон из файла (слитно)
              char filename[1024];
              int j = 0;
              while (argv[count][i + 1]) {
                filename[j] = argv[count][i + 1];
                j++;
                i++;
              }
              filename[j] = '\0';
              Ent_Opt = F_Option_pattern_set(filename, Ent_Opt, argv[count]);
            } else if (!argv[count][i + 1]) {  // шаблон из файла отдельно через
                                               // пробел от f
              if (argv[count + 1]) {
                char filename[1024];
                int j = 0;
                while (argv[count + 1][j]) {
                  filename[j] = argv[count + 1][j];
                  j++;
                }
                filename[j] = '\0';
                Ent_Opt = F_Option_pattern_set(filename, Ent_Opt, argv[count]);
                memset(argv[count + 1], '\0',
                       strlen(argv[count + 1]));  // Зануляем найденную опцию
              } else {  //  если ввели в конце -е без аргумента
                fprintf(stderr, "option requires an argument -- f\n");
                Ent_Opt.Parser_Error++;
              }
            }
            break;
          } else {
            if (argv[count][i] == 'b') {
              Ent_Opt.option_b = 1;
            } else if ((argv[count][i] == 'E') && (grep_util_ID == 0)) {
              Ent_Opt.option_E = 1;
            } else if (argv[count][i] == 's') {
              Ent_Opt.option_s = 1;
            } else if ((argv[count][i] == 't') && (grep_util_ID == 0)) {
              Ent_Opt.option_t = 1;
            } else if ((argv[count][i] == 'T') && (grep_util_ID == 0)) {
              Ent_Opt.option_T = 1;
            } else if (argv[count][i] == 'n') {
              Ent_Opt.option_n = 1;
            } else if (argv[count][i] == 'v') {
              Ent_Opt.option_v = 1;
            } else if ((argv[count][i] == 'i') && (grep_util_ID == 1)) {
              Ent_Opt.option_i = 1;
            } else if ((argv[count][i] == 'c') && (grep_util_ID == 1)) {
              Ent_Opt.option_c = 1;
            } else if ((argv[count][i] == 'l') && (grep_util_ID == 1)) {
              Ent_Opt.option_l = 1;
            } else if ((argv[count][i] == 'h') && (grep_util_ID == 1)) {
              Ent_Opt.option_h = 1;
            } else if ((argv[count][i] == 'o') && (grep_util_ID == 1)) {
              Ent_Opt.option_o = 1;
            } else if ((argv[count][i] == '-') && (grep_util_ID == 0)) {
              if (strcmp(argv[count], "--number-nonblank") == 0) {
                Ent_Opt.option_b = 1;
                break;
              } else if (strcmp(argv[count], "--number") == 0) {
                Ent_Opt.option_n = 1;
                break;
              } else if (strcmp(argv[count], "--squeeze-blank") == 0) {
                Ent_Opt.option_s = 1;
                break;
              } else if (!argv[count][i + 1]) {
              } else {
                fprintf(stderr, "no such '--' option '%s' ERROR\n",
                        argv[count]);
                Ent_Opt.Parser_Error++;
                break;
              }
            } else {
              fprintf(stderr, "no such '-' option '%s' ERROR\n", argv[count]);
              Ent_Opt.Parser_Error++;
              break;
            }
          }
        }
        memset(argv[count], '\0',
               strlen(argv[count]));  // Зануляем найденную опцию
      } else if ((grep_util_ID == 0) && (count == 1)) {
        cat_option_order_flag =
            1;  //  если флаги не идут вначале, больше не сканируем
      }
      count++;
    }
  } else {
    Ent_Opt.Parser_Error++;
  }
  return Ent_Opt;
}

struct OPT F_Option_pattern_set(char *filename, struct OPT Ent_Opt,
                                char *argv) {
  FILE *file_stream;
  file_stream = fopen(filename, "r");
  if (file_stream == NULL) {
    fprintf(stderr, "file %s open ERROR\n",
            filename);  //  Проверка открытия файла
    Ent_Opt.Parser_Error++;
    exit(1);
  } else {
    int j = 0;
    Ent_Opt.e_pattern[Ent_Opt.pattern_num][j] = getc(file_stream);
    while (Ent_Opt.e_pattern[Ent_Opt.pattern_num][j] != EOF) {
      if (Ent_Opt.e_pattern[Ent_Opt.pattern_num][j] == '\n') {
        if ((j != 0) || ((j != 0) && (Ent_Opt.pattern_num == 0)))
          Ent_Opt.e_pattern[Ent_Opt.pattern_num][j] = '\0';
        Ent_Opt.pattern_num++;
        j = 0;
        Ent_Opt.e_pattern[Ent_Opt.pattern_num][j] = getc(file_stream);
      } else {
        j++;
        Ent_Opt.e_pattern[Ent_Opt.pattern_num][j] = getc(file_stream);
      }
    }
    if (fclose(file_stream) == EOF) {
      fprintf(stderr, "file %s close error\n", argv);
      Ent_Opt.Parser_Error++;
      exit(1);
    }
    Ent_Opt.e_pattern[Ent_Opt.pattern_num][j] = '\0';
    Ent_Opt.pattern_num++;
    Ent_Opt.e_pattern_flag++;
  }
  return Ent_Opt;
}