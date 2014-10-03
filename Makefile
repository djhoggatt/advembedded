CC=gcc
CFLAGS= --coverage -O2 -ffloat-store -Wall -Wextra -Werror -std=c99
DEPS = decide.h
SRC = decide.c
SRCt = decide.c test.c

all: decide

decide: $(SRC)
	$(CC) -c $(CFLAGS) $(SRC)

test: $(SRCt)	
	$(CC) $(CFLAGS) $(SRCt) -o test -lm
	
.just_in_case: clean

clean:
	rm -f *.o decide test