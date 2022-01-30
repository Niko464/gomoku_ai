##
## EPITECH PROJECT, 2022
## Gomoku
## File description:
## Makefile
##


BINARY_NAME = pbrain-gomoku-ai


all: cmake

cmake:
	mkdir build && cd ./build && cmake .. && ((make && mv pbrain-gomoku-ai ..) || echo 'Windows system detected')

tests_run:
	@echo 'No tests specified'

clean:
	rm -rf build

fclean: clean
	rm -f $(BINARY_NAME)

re: fclean all

.PHONY: all clean fclean re tests_run