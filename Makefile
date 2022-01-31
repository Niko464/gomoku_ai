##
## EPITECH PROJECT, 2022
## Gomoku
## File description:
## Makefile
##

CFLAGS += -Iinclude -Wall -Wextra
BINARY_NAME = pbrain-gomoku-ai


all: cmake

cmake:
	mkdir build && cd ./build && cmake .. && ((make && mv pbrain-gomoku-ai ..) || echo 'Windows system detected')

google_tests_run:
	@g++ -o unit_tests src/*.cpp tests/tests.cpp $(CFLAGS) -pthread -lgtest
	@echo "✔️ Compiled tests"
	@./unit_tests

clean:
	rm -rf build

fclean: clean
	rm -f $(BINARY_NAME)
	rm -rf unit_tests
	rm -rf *.gcno
	rm -rf *.gcda

re: fclean all

.PHONY: all clean fclean re tests_run