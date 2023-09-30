CC = gcc
STD_FLAGS = -Wall -Werror -Wextra -std=c11

all: flags.o main.o
	$(CC) $(STD_FLAGS) $^ -lm -o task_1.out

flags.o: flags.c
	$(CC) $(STD_FLAGS) -c $<

main.o: main.c
	$(CC) $(STD_FLAGS) -c $<

clean:
	rm -f *.out *.o

rebuild: clean all
