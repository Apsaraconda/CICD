CC=gcc
CFLAGS=-c -Wall -Werror -Wextra -std=c11
LDFLAGS=-Wall -Werror -Wextra -std=c11
SOURCES=s21_cat.c ../common/parser.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main

all: s21_cat

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf *.o all *.o $(OBJECTS)
rebuild: clean all

s21_cat.o:
	$(CC) $(CFLAGS) s21_cat.c
parser.o:
	$(CC) $(CFLAGS) ../common/parser.c
s21_cat: s21_cat.o parser.o
	$(CC) $(LDFLAGS) s21_cat.c ../common/parser.c -o s21_cat
	rm -rf *.o
test:
	bash ./tests.sh