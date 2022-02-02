/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** tests
*/

#include "gtest/gtest.h"
#include "TranspositionTable.hpp"
#include "Board.hpp"
#include "BoardEvaluator.hpp"
#include "Utils.hpp"

GTEST_TEST(BoardTests, canMakeMoveAndUnmake)
{
    Board board;

    ASSERT_EQ(board.canMakeMove(0, 0), true);
    board.makeMove(0, 0, player_types::AI);
    ASSERT_EQ(board.canMakeMove(0, 0), false);
    board.unmakeMove(0, 0, player_types::AI);
    ASSERT_EQ(board.canMakeMove(0, 0), true);
}

GTEST_TEST(BoardTests, Reset)
{
    Board board;

    board.makeMove(5, 5, player_types::PLAYER);
    board.reset();
    ASSERT_EQ(board.canMakeMove(5, 5), true);
}

GTEST_TEST(BoardTests, isSquareTaken)
{
    Board board;

    board.makeMove(5, 5, player_types::PLAYER);
    ASSERT_EQ(board.isSquareTakenBy(0, 0, player_types::AI), false);
    ASSERT_EQ(board.isSquareTakenBy(5, 5, player_types::AI), false);
    ASSERT_EQ(board.isSquareTakenBy(5, 5, player_types::PLAYER), true);

    
}

GTEST_TEST (TranspositionTableTests, one)
{
    unsigned int seed = 0;
    TranspositionTable table(seed);
    Board board;
    int hashOne = table.computeHash(board);

    ASSERT_EQ(table.knowsHash(hashOne), false);
    ASSERT_EQ(hashOne, 0);

    board.makeMove(0, 0, player_types::AI);
    int hashTwo = table.computeHash(board);

    ASSERT_EQ(hashTwo, 1804289383);

    board.unmakeMove(0, 0, player_types::AI);
    board.makeMove(0, 1, player_types::AI);
    int hashThree = table.computeHash(board);

    ASSERT_EQ(hashThree, 1681692777);

    board.makeMove(0, 0, player_types::AI);
    int hashFour = table.computeHash(board);

    ASSERT_EQ(hashFour, 1804289383 ^ 1681692777);
}

GTEST_TEST(BoardEvaluatorTests, didPlayerWin_Right)
{
    Board board;
    BoardEvaluator evaluator;
    
    board.makeMove(3, 3, player_types::AI);
    board.makeMove(3, 4, player_types::AI);
    board.makeMove(3, 5, player_types::AI);
    board.makeMove(3, 6, player_types::AI);
    board.makeMove(3, 7, player_types::AI);
    board.makeMove(14, 13, player_types::AI);

    board.makeMove(0, 3, player_types::PLAYER);
    board.makeMove(18, 13, player_types::PLAYER);

    ASSERT_EQ(evaluator.didPlayerWin(board, player_types::PLAYER), false);
    ASSERT_EQ(evaluator.didPlayerWin(board, player_types::AI), true);

    board.reset();

    board.makeMove(8, 8, player_types::PLAYER);
    board.makeMove(9, 9, player_types::PLAYER);
    board.makeMove(10, 10, player_types::PLAYER);
    board.makeMove(11, 11, player_types::PLAYER);
    ASSERT_EQ(evaluator.didPlayerWin(board, player_types::PLAYER), false);
    board.makeMove(12, 12, player_types::PLAYER);
    ASSERT_EQ(evaluator.didPlayerWin(board, player_types::PLAYER), true);

}


int main(int ac, char **av)
{
    ::testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}