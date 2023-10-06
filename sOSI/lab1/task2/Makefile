CC = gcc
STD_FLAGS = -Wall -Werror -Wextra -std=c11

all: functions.o main.o
	$(CC) $(STD_FLAGS) $^ -o shell.out
	./shell.out file/user_data.txt file/command.txt


functions.o: functions.c

	$(CC) $(STD_FLAGS) -c $<

main.o: main.c
	$(CC) $(STD_FLAGS) -c $<

clean:
	rm -f *.out *.o

rebuild: clean all