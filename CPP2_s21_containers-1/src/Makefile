.PHONY: all test gcov_report gcov_report2 clang_format clang_check valgrind cpp_check clean rebuild

FLAG        = -Wall -Wextra --std=c++17 -Werror -lm
FLAG_LIB    = -lgtest_main -lgtest -pthread -lm
FLAG_GCOV   = --coverage


all: test clang_check valgrind cpp_check


test: clean
	@echo "┏=========================================┓"
	@echo "┃             Running Tests               ┃"
	@echo "┗=========================================┛"
	g++ $(FLAG) tests/*_test.cpp -o test $(FLAG_LIB)
	./test
	rm -f test


gcov_report2: clean
	mkdir -p report
	g++ $(FLAG_GCOV) $(FLAG_LIB) $(FLAG) tests/*_test.cpp -o test
	./test
	lcov -t "test" -o test.info --no-external -c -d . --ignore-errors mismatch
	genhtml -o report/ test.info
	open ./report/index.html

gcov_report: clean
# Компиляция тестов с флагами для покрытия
	g++ $(FLAG_GCOV) $(FLAG_LIB) $(FLAG) tests/*_test.cpp -o test
# Запуск тестов
	./test
# Сбор информации о покрытии кода, исключая файлы gtest
	lcov -t "gcov_report" -o coverage.info -c -d . \
		--exclude '*gtest/*' \
		--exclude '*usr/include/*'
# Генерация HTML-отчёта из coverage.info
	genhtml -o report coverage.info
	@echo "Coverage report generated in ./report/index.html"
# Очистка временных файлов покрытия
	rm -f *.gcda *.gcno *.info test

# Формируем список всех файлов с нужными расширениями
SRC_FILES := $(shell find . -type f \( -name "*.c" -o -name "*.h" -o -name "*.tpp" \))

# Проверка clang-format
clang_format:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i $(SRC_FILES)
	rm -f .clang-format

clang_check:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n $(SRC_FILES)
	rm -f .clang-format

# Проверка valgrind
valgrind: clean
	@echo "┏=========================================┓"
	@echo "┃       Running Valgrind your code        ┃"
	@echo "┗=========================================┛"
	g++ $(FLAG) tests/*_test.cpp -o test $(FLAG_LIB)
	valgrind --tool=memcheck --leak-check=yes ./test
	rm -rf test

# Проверка cppcheck
cpp_check:
	@echo "┏=========================================┓"
	@echo "┃       Running cppcheck your code        ┃"
	@echo "┗=========================================┛"
	cppcheck --std=c++17 --language=c++ $(SRC_FILES)

clean:
	@echo "Deleting unnecessary files..."
	rm -rf report test .clang-format *.gcda *.gcno *.info test


rebuild: clean all

# --coverage: Включает сбор данных для отчётов покрытия кода (gcov).
# -lgtest_main: Линкует библиотеку Google Test с готовым определением функции main.
# -lgtest: Линкует основную библиотеку Google Test, содержащую функциональность для тестирования.
# -pthread: Использует многопоточность (требуется Google Test).
# -lm: Подключает стандартную математическую библиотеку.
# -Wall -Wextra: Включает дополнительные предупреждения.
# --std=c++17: Указывает стандарт языка C++17.
# -Werror: Превращает все предупреждения в ошибки.
# tests/*_test.cpp: Указывает на все тестовые файлы в директории tests, соответствующие маске *_test.cpp.
# -o test: Указывает выходной файл для собранного тестового исполняемого файла.