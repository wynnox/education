CC = gcc
STD_FLAGS = -Wall -Werror -Wextra -std=c11

all: functions.o main.o
	$(CC) $(STD_FLAGS) $^ -o task_3.out
	rm -f *.o

functions.o: functions.c
	$(CC) $(STD_FLAGS) -c $<

main.o: main.c
	$(CC) $(STD_FLAGS) -c $<

clean:
	rm -f *.out *.o

rebuild: clean all
