.PHONY: all s21_matrix_oop.a test clang_format clang_check valgrind clean

CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++17
FLAG_GTEST = -lgtest -lgtest_main -pthread

SRC = s21_matrix_oop.cpp
HEADER = s21_matrix_oop.h
OBJECTS = s21_matrix_oop.o

LIB_NAME = s21_matrix_oop.a
TEST_SRC = tests.cpp
TEST_EXEC = test

all: $(LIB_NAME)

$(LIB_NAME): $(SRC) $(HEADER)
	$(CC) $(FLAGS) -c $(SRC)
	ar rcs $(LIB_NAME) $(OBJECTS)
	ranlib $(LIB_NAME)
	rm *.o

test: clean $(TEST_SRC) $(LIB_NAME)
	$(CC) $(FLAGS) $(TEST_SRC) $(LIB_NAME) -o $(TEST_EXEC) $(FLAG_GTEST)
	./$(TEST_EXEC)

clang_format:
	@echo "Running clang-format"
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.cpp *.h
	rm -f .clang-format

clang_check:
	@echo "Running clang-check"
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cpp *.h
	rm -f .clang-format

valgrind: clean $(TEST_SRC) $(LIB_NAME)
	$(CC) $(FLAGS) $(TEST_SRC) $(LIB_NAME) -o $(TEST_EXEC) $(FLAG_GTEST)
	valgrind --tool=memcheck --leak-check=yes ./$(TEST_EXEC)

clean:
	rm -rf *.o *.gcno *.a *.gcda $(TEST_EXEC)
