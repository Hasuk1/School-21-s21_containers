CC = g++
CPPFLAGS = -lgtest -lgtest_main -std=c++17 -pthread
CHECKFLAGS = -Wall -Werror -Wextra

all: clean test style

test: clean
	@$(CC) $(CHECKFLAGS) tests.cc -o $@ $(CPPFLAGS) && ./test

clean:
	@rm -rf *.o *.a test *.gcno *.gcda *.gcov report *.info tests_RB_tree.out *.filtered ../.DS_Store test .DS_Store

style:
	@cp ../materials/linters/.clang-format array/
	@cp array/.clang-format list/
	@cp list/.clang-format map/
	@cp map/.clang-format queue/
	@cp queue/.clang-format rb_tree/
	@cp rb_tree/.clang-format set/
	@cp set/.clang-format stack/
	@cp stack/.clang-format vector/
	@echo "===> Checking your code for Google Style <==="
	@clang-format -n -style=GOOGLE *.cc *.h array/* list/* map/* queue/* rb_tree/* set/* stack/* vector/*
	@rm array/.clang-format list/.clang-format map/.clang-format queue/.clang-format
	@rm rb_tree/.clang-format set/.clang-format stack/.clang-format vector/.clang-format

clang:
	@cp ../materials/linters/.clang-format array/
	@cp array/.clang-format list/
	@cp list/.clang-format map/
	@cp map/.clang-format queue/
	@cp queue/.clang-format rb_tree/
	@cp rb_tree/.clang-format set/
	@cp set/.clang-format stack/
	@cp stack/.clang-format vector/
	@echo "===> Formatting your code for Google Style <==="
	@clang-format -i -style=GOOGLE *.cc *.h array/* list/* map/* queue/* rb_tree/* set/* stack/* vector/*
	@rm array/.clang-format list/.clang-format map/.clang-format queue/.clang-format
	@rm rb_tree/.clang-format set/.clang-format stack/.clang-format vector/.clang-format

leaks: clean
	@$(CC) $(CHECKFLAGS) tests.cc -o test $(CPPFLAGS)
	@leaks -atExit -- ./test

valgrind:
	@$(CC) $(CHECKFLAGS) tests.cc -o test $(CPPFLAGS)
	@CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

docker: clean
	@docker build . -t set:1.1 -f ./Dockerfile
	@docker run --rm -it --name set_test set:1.1

.PHONY: all test style clang clean leaks valgrind docker
