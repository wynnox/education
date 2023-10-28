CC = gcc
STD_FLAGS = -Wall -Werror -Wextra -std=c11

all: functions.o oversprintf.o main.o
	$(CC) $(STD_FLAGS) $^ -o task_5.out
	rm -f *.o
	valgrind ./task_5.out > test.txt

functions.o: functions.c
	$(CC) $(STD_FLAGS) -c $<

oversprintf.o: oversprintf.c
	$(CC) $(STD_FLAGS) -c $<

main.o: main.c
	$(CC) $(STD_FLAGS) -c $<

clean:
	rm -f *.out *.o

rebuild: clean all
