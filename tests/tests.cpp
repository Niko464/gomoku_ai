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

void printMoves(std::vector<std::pair<int, int>> &moves)
{
    for (int i = 0; i < moves.size(); i++) {
        std::cout << moves[i].first << "," << moves[i].second << std::endl;
    }
}

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

GTEST_TEST(BoardTests, validMoves)
{
    Board board;
    std::vector<std::pair<int, int>> moves;

    moves = board.getValidMoves(3);
    testing::internal::CaptureStdout();
    printMoves(moves);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "");


    board.makeMove(0, 0, player_types::AI);
    moves = board.getValidMoves(2);
    testing::internal::CaptureStdout();
    printMoves(moves);
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(moves.size(), 8);
    ASSERT_EQ(output, "0,1\n0,2\n1,0\n1,1\n1,2\n2,0\n2,1\n2,2\n");

    board.reset();

    board.makeMove(19, 19, player_types::PLAYER);
    moves = board.getValidMoves(3);
    testing::internal::CaptureStdout();
    printMoves(moves);
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(moves.size(), 15);
    ASSERT_EQ(output, "16,16\n16,17\n16,18\n16,19\n17,16\n17,17\n17,18\n17,19\n18,16\n18,17\n18,18\n18,19\n19,16\n19,17\n19,18\n");

    board.reset();

    board.makeMove(9, 9, player_types::AI);
    moves = board.getValidMoves(2);
    testing::internal::CaptureStdout();
    printMoves(moves);
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(moves.size(), 24);

    board.reset();

    board.makeMove(9, 9, player_types::AI);
    board.makeMove(9, 10, player_types::PLAYER);
    moves = board.getValidMoves(1);
    testing::internal::CaptureStdout();
    printMoves(moves);
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(moves.size(), 10);
    ASSERT_EQ(output, "8,8\n8,9\n8,10\n9,8\n10,8\n10,9\n10,10\n8,11\n9,11\n10,11\n");
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