WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose --show-leak-kinds=all

SRCS = tree.c main.c
OBJS = $(SRCS:%.c=%.o)

hw17: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o hw17

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testall: test1 test2 test3 test4 test5

test1: hw17
	./hw17 inputs16/input1 inputs/test1 output1
	diff output1 expected/expected1

test2: hw17
	./hw17 inputs16/input2 inputs/test2 output2
	diff output2 expected/expected2

test3: hw17
	./hw17 inputs16/input3 inputs/test3 output3
	diff output3 expected/expected3

test4: hw17
	./hw17 inputs16/input4 inputs/test4 output4
	diff output4 expected/expected4

test5: hw17
	./hw17 inputs16/input5 inputs/test5 output5
	diff output5 expected/expected5

testmemory: hw17
	$(VAL) ./hw17 inputs16/input1 inputs/test1 output1

clean: # remove all machine generated files
	rm -f hw17 *.o output? *~