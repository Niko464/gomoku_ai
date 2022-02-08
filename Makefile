##
## EPITECH PROJECT, 2021
## Gomoku
## File description:
## Makefile
##

CC            =    g++
CXXFLAGS      = -Wall -Wextra -Iinclude

NAME        =    pbrain-gomoku-ai

FILES        = 		src/Board.cpp	\
    src/Game.cpp	\
    src/Utils.cpp	\
    src/TranspositionTable.cpp	\
    src/GoProgram.cpp	\
    src/BitBoard.cpp	\
    src/GoAI.cpp	\
    src/BoardEvaluator.cpp

SRC            =    src/main/main.cpp                \
                $(FILES)

TESTS_CRITERION =    $(FILES)                    \
                tests/tests_patterns.cpp

TESTS_GOOGLE	=	$(FILES)	\
					tests/tests.cpp


OBJ            =    $(SRC:.cpp=.o)

RM            =    rm -f

all: exec

exec: $(OBJ)
	@$(CC) $(CXXFLAGS) -o $(NAME) $(OBJ)

tests_run: fclean
	@$(CC) $(CXXFLAGS) -o unit_tests $(TESTS_CRITERION) --coverage -lcriterion
	@./unit_tests

google_tests_run:
	@g++ -o google_tests $(TESTS_GOOGLE) $(CFLAGS) $(CXXFLAGS) -pthread -lgtest
	@echo "✔️ Compiled Google tests"
	@./google_tests

all_tests: google_tests_run tests_run

clean:
	@$(RM) $(OBJ)
	@$(RM) *.gc*
	@$(RM) tests/*.o

fclean: clean
	rm -f $(NAME)
	rm -rf unit_tests
	rm -rf google_tests
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf src/*.o
	rm -rf *.gcda

re: fclean all