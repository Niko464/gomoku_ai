#include <criterion/criterion.h>
#include "Board.hpp"
#include "BoardEvaluator.hpp"
#include <iostream>

Test(ai, test)
{
    Board board;
    BoardEvaluator evaluator;

    board.makeMove(0, 1, player_types::AI);
    board.makeMove(0, 2, player_types::AI);
    board.makeMove(0, 3, player_types::AI);
    board.makeMove(0, 4, player_types::AI);
    int score = evaluator.evaluateBoard(board);
    cr_assert_eq(score, 184000);
    return;
}

Test(ai, test2)
{
    Board board;
    BoardEvaluator evaluator;

    board.makeMove(0, 0, player_types::AI);
    board.makeMove(0, 1, player_types::AI);
    board.makeMove(0, 2, player_types::AI);
    board.makeMove(0, 3, player_types::AI);

    int score = evaluator.evaluateBoard(board);
    std::cout << score << std::endl;
    cr_assert_eq(score, 42000);
    return;
}

Test(ai, test3)
{
    Board board;
    BoardEvaluator evaluator;

    board.makeMove(1, 1, player_types::AI);
    board.makeMove(2, 2, player_types::AI);
    board.makeMove(3, 3, player_types::AI);
    board.makeMove(4, 4, player_types::AI);
    int score = evaluator.evaluateBoard(board);
    cr_assert_eq(score, 184000);
    return;
}


Test(ai, test4)
{
    Board board;
    BoardEvaluator evaluator;

    board.makeMove(5, 5, player_types::AI);
    board.makeMove(6, 5, player_types::AI);
    board.makeMove(7, 5, player_types::AI);
    board.makeMove(8, 5, player_types::AI);
    int score = evaluator.evaluateBoard(board);
    cr_assert_eq(score, 184000);
    return;
}

Test(ai, test5)
{
    Board board;
    BoardEvaluator evaluator;

    board.makeMove(5, 5, player_types::AI);
    board.makeMove(6, 5, player_types::AI);
    board.makeMove(7, 5, player_types::AI);
    board.makeMove(8, 5, player_types::AI);
    board.makeMove(9, 5, player_types::PLAYER);
    int score = evaluator.evaluateBoard(board);
    cr_assert_eq(score, 42000);
    return;
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