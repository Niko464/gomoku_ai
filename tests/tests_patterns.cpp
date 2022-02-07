#include <criterion/criterion.h>
#include "Board.hpp"
#include "BoardEvaluator.hpp"
#include <iostream>

Test(ai, test)
{
    Board board;
    BoardEvaluator evaluator;

    board.makeMove(19, 19, player_types::AI);
    board.makeMove(18, 18, player_types::AI);
    board.makeMove(17, 17, player_types::AI);
    board.makeMove(16, 16, player_types::AI);
    board.makeMove(19, 19, player_types::AI);

    board.makeMove(17, 15, player_types::PLAYER);
    board.makeMove(16, 14, player_types::PLAYER);
    board.makeMove(16, 16, player_types::PLAYER);


    evaluatorSizes limits;

    limits.testSizeX = 4;
    limits.testSizeY = 4;
    limits.hasSpaces = false;
    limits.testCase.set(0);
    limits.testCase.set(20 + 1);
    limits.testCase.set(40 + 2);
    limits.testCase.set(60 + 3);
    evaluator._findPattern(limits, board, [](Board &myBoard, evaluatorSizes &params) {
        if ((myBoard.getPlayerBoard(player_types::AI) & params.testCase) == params.testCase) {
            std::cout << "Found pattern" << std::endl;
        }
    });
}

Test(ai, test2)
{
    Board board;
    BoardEvaluator evaluator;

    board.makeMove(19, 19, player_types::AI);
    board.makeMove(18, 18, player_types::AI);
    board.makeMove(17, 17, player_types::AI);
    board.makeMove(16, 16, player_types::AI);
    board.makeMove(19, 19, player_types::AI);

    board.makeMove(17, 15, player_types::PLAYER);
    board.makeMove(16, 14, player_types::PLAYER);
    board.makeMove(16, 16, player_types::PLAYER);


    evaluatorSizes limits;

    limits.testSizeX = 5;
    limits.testSizeY = 5;
    limits.hasSpaces = true;
    limits.testCase.set(20 + 1);
    limits.testCase.set(40 + 2);
    limits.testCase.set(60 + 3);
    limits.testCase.set(80 + 4);
    limits.spaceTestCase.set(0);
    evaluator._findPattern(limits, board, [](Board &myBoard, evaluatorSizes &params) {
        if ((myBoard.getPlayerBoard(player_types::AI) & params.testCase) == params.testCase) {
            std::cout << "Found pattern too" << std::endl;
        }
    });
}


/*
struct evaluatorSizes {
    int testSizeY;
    int testSizeX;
    bool hasSpaces;
    std::bitset<400> testCase;
    std::bitset<400> spaceTestCase;
};
*/