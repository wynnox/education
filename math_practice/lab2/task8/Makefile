CC = gcc
STD_FLAGS = -Wall -Werror -Wextra

all: functions.o main.o
	$(CC) $(STD_FLAGS) $^ -o task_8.out
	rm -f *.o
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./task_8.out > test.txt

functions.o: functions.c
	$(CC) $(STD_FLAGS) -c $<

main.o: main.c
	$(CC) $(STD_FLAGS) -c $<

clean:
	rm -f *.out *.o

rebuild: clean all
