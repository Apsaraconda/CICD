CC=gcc
CFLAGS=-c -Wall -Werror -Wextra -std=c11
LDFLAGS=-Wall -Werror -Wextra -std=c11 
SOURCES=s21_grep.c ../common/parser.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main

all: s21_grep s21_cat

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf *.o all *.o $(OBJECTS)
rebuild: clean all

s21_grep.o:
	$(CC) $(CFLAGS) s21_grep.c
parser.o:
	$(CC) $(CFLAGS) ../common/parser.c
s21_grep: s21_grep.o parser.o
	$(CC) $(LDFLAGS) s21_grep.c ../common/parser.c -o s21_grep
	rm -rf *.o
s21_cat.o:
	$(CC) $(CFLAGS) ../cat/s21_cat.c
s21_cat: s21_cat.o parser.o
	$(CC) $(LDFLAGS) ../cat/s21_cat.c ../common/parser.c -o ../cat/s21_cat
	rm -rf *.o
s21_grep_z.o:
	$(CC) $(CFLAGS) s21_grep_z.c
s21_grep_z: s21_grep_z.o parser.o
	$(CC) $(LDFLAGS) s21_grep_z.c ../common/parser.c -o s21_grep_z
	rm -rf *.o
test:
	bash ./tests.sh