CC = gcc -Wall -Werror -Wextra -std=c11
OS := $(shell uname -s)
VALGRIND_FLAGS  = 	--log-file="valgrind.txt" --tool=memcheck --leak-check=yes --track-origins=yes


ifeq ($(OS),Linux)
    Flags = -lcheck  -lm -lrt -lpthread -lsubunit
else
    Flags = -lcheck -lm -lpthread
endif


all: clean s21_decimal.a
 
s21_decimal.a:
	$(CC) -c *.c $(Flags)
	ar rcs s21_decimal.a *.o
	ranlib s21_decimal.a
	rm *.o

test: clean
	$(CC) --coverage *.c tests/*.c -o test $(Flags)
	./test

gcov_report: test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	xdg-open report/index.html

clang:
	clang-format -n *.c *.h tests/*.c tests/*.h

clean:
	rm -rf test s21_decimal.a *.gcno *.info *.gcda report *.dSYM

valgrind: clean test
	valgrind $(VALGRIND_FLAGS) ./test
	grep -n "ERROR SUMMARY" valgrind.txt