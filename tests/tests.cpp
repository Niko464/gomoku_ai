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

GTEST_TEST(BoardEvaluatorTests, findPattern)
{
    Board board;
    BoardEvaluator evaluator;
    int foundCases = 0;

    /*evaluatorSizes testCaseRight = {6, 6, true};

    testCaseRight.testCase.set(20 + 1);
    testCaseRight.testCase.set(40 + 2);
    testCaseRight.testCase.set(60 + 3);
    testCaseRight.testCase.set(80 + 4);

    testCaseRight.spaceTestCase.set(0);
    testCaseRight.spaceTestCase.set(100 + 5);*/

    /*evaluatorSizes testCaseRight = {6, 6, true};

    testCaseRight.spaceTestCase.set(5);
    testCaseRight.testCase.set(20 + 4);
    testCaseRight.testCase.set(40 + 3);
    testCaseRight.testCase.set(60 + 2);
    testCaseRight.testCase.set(80 + 1);

    
    testCaseRight.spaceTestCase.set(100);*/

    evaluatorSizes testCaseRight = {6, 1, true};

    testCaseRight.spaceTestCase.set(0);
    testCaseRight.testCase.set(20);
    testCaseRight.testCase.set(40);
    testCaseRight.testCase.set(60);
    testCaseRight.testCase.set(80);
    testCaseRight.spaceTestCase.set(100);

    evaluator._findPattern(testCaseRight, board,
        [&](Board &myBoard, evaluatorSizes &params) {


            Utils::printBitBoard<400>(20, 20, params.testCase);
            std::cout << "\n" << std::endl;

            std::bitset<400> aiBoard = myBoard.getPlayerBoard(player_types::AI);
            std::bitset<400> playerBoard = myBoard.getPlayerBoard(player_types::PLAYER);

            if ((aiBoard & params.testCase) == params.testCase &&
                (aiBoard ^ params.spaceTestCase) == params.spaceTestCase &&
                (playerBoard ^ params.spaceTestCase) == params.spaceTestCase) {
                foundCases++;
            }
            
        }
    );
    ASSERT_EQ(foundCases, 0)
}

int main(int ac, char **av)
{
    ::testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}