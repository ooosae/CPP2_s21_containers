CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
# CFLAGS += -pedantic
TFLAGS = -lgtest -pthread
TST_SRCS = tests/*.cpp
EXE = test_exe

.PHONY: all clean test gcov_report format check leaks leaks_for_mac sanitize

all: clean test

test: $(EXE)
	./$? > $?.log

$(EXE): $(TST_SRCS)
	$(CC) $(CFLAGS) -o $@ $? $(TFLAGS)

gcov_report: CFLAGS += --coverage
gcov_report: clean test
	lcov -t "coverage" -o coverage.info -c -d . --no-external
	lcov -r coverage.info $(shell pwd)/$(TST_SRCS) -o coverage.info
	genhtml -o report coverage.info
	rm -f *.gc* *.info
	open ./report/index.html

clean:
	rm -rf report
	rm -f *.gc* *.info $(EXE) *.log

format:
	clang-format -style=google -i *.h **/*.cpp **/*.h containers/*/*.h

check:
	clang-format -style=google -n *.h **/*.cpp **/*.h containers/*/*.h
	cppcheck --enable=all --suppress=missingIncludeSystem --inline-suppr \
	--language=c++ --std=c++17 *.h **/*.cpp **/*.h containers/*/*.h

leaks: clean $(EXE)
	CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	--verbose --log-file=$(EXE)_valgrind.log ./$(EXE) > $(EXE).log

leaks_for_mac: clean $(EXE)
	leaks -atExit -- ./$(EXE) > $(EXE).log

sanitize: CFLAGS += -g -fsanitize=address
sanitize: clean test
