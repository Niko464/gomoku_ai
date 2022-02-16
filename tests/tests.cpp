/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "TranspositionTable.hpp"
#include "Board.hpp"
#include "BoardEvaluator.hpp"
#include "Utils.hpp"
#include "GoAI.hpp"
#include <chrono>

/*GTEST_TEST(aiSpeed, Speed)
{
    GoAI ai;
    Board board;
    std::string output = "";
    int depth = 3;

    board.makeMove(7, 7, player_types::PLAYER);

    auto start = std::chrono::system_clock::now();
    testing::internal::CaptureStdout();
    ai.startThinking(board, 500000, false, depth);
    output = testing::internal::GetCapturedStdout();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << output << std::endl;
    ai.printStats();
    std::cout << "MESSAGE Time it took for " << depth << " depths: " << elapsed.count() << "s" << std::endl;
}*/

Test(BoardTests, canMakeMoveAndUnmake)
{
    Board board;

    cr_assert_eq(board.canMakeMove(0, 0), true);
    board.makeMove(0, 0, player_types::AI);
    cr_assert_eq(board.canMakeMove(0, 0), false);
    board.unmakeMove(0, 0, player_types::AI);
    cr_assert_eq(board.canMakeMove(0, 0), true);
}


Test(BoardTests, Reset)
{
    Board board;

    board.makeMove(5, 5, player_types::PLAYER);
    board.reset();
    cr_assert_eq(board.canMakeMove(5, 5), true);
}


Test(BoardTests, isSquareTaken)
{
    Board board;

    board.makeMove(5, 5, player_types::PLAYER);
    cr_assert_eq(board.isSquareTakenBy(0, 0, player_types::AI), false);
    cr_assert_eq(board.isSquareTakenBy(5, 5, player_types::AI), false);
    cr_assert_eq(board.isSquareTakenBy(5, 5, player_types::PLAYER), true);
}


Test(BoardTests, validMoves)
{
    cr_redirect_stdout();
    Board board;
    std::vector<Vec2> moves;

    std::cout << std::endl;
    moves = board.getValidMoves(3);

    //testing::internal::CaptureStdout();
    Utils::printMoves(moves);
    //std::string output = testing::internal::GetCapturedStdout();
    //cr_assert_stdout_eq_str("\n");

    board.makeMove(0, 0, player_types::AI);
    moves = board.getValidMoves(2);
   // testing::internal::CaptureStdout();
    Utils::printMoves(moves);
    cr_assert_eq(moves.size(), 8);
    cr_assert_stdout_eq_str("\n0,1\n0,2\n1,0\n1,1\n1,2\n2,0\n2,1\n2,2\n");
/*
    board.reset();

    board.makeMove(19, 19, player_types::PLAYER);
    moves = board.getValidMoves(3);
    testing::internal::CaptureStdout();
    Utils::printMoves(moves);
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(moves.size(), 15);
    ASSERT_EQ(output, "16,16\n16,17\n16,18\n16,19\n17,16\n17,17\n17,18\n17,19\n18,16\n18,17\n18,18\n18,19\n19,16\n19,17\n19,18\n");

    board.reset();

    board.makeMove(9, 9, player_types::AI);
    moves = board.getValidMoves(2);
    testing::internal::CaptureStdout();
    Utils::printMoves(moves);
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(moves.size(), 24);

    board.reset();

    board.makeMove(9, 9, player_types::AI);
    board.makeMove(9, 10, player_types::PLAYER);
    moves = board.getValidMoves(1);
    testing::internal::CaptureStdout();
    Utils::printMoves(moves);
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(moves.size(), 10);
    ASSERT_EQ(output, "8,8\n8,9\n8,10\n9,8\n10,8\n10,9\n10,10\n8,11\n9,11\n10,11\n");
    */
}



Test(TranspositionTableTests, one)
{
    unsigned int seed = 0;
    TranspositionTable table(seed);
    Board board;
    int hashOne = table.computeHash(board);

    cr_assert_eq(table.knowsHash(hashOne), false);
    cr_assert_eq(hashOne, 0);

    board.makeMove(0, 0, player_types::AI);
    int hashTwo = table.computeHash(board);

    cr_assert_eq(hashTwo, 1804289383);

    board.unmakeMove(0, 0, player_types::AI);
    board.makeMove(0, 1, player_types::AI);
    int hashThree = table.computeHash(board);

    cr_assert_eq(hashThree, 1681692777);

    board.makeMove(0, 0, player_types::AI);
    int hashFour = table.computeHash(board);

    cr_assert_eq(hashFour, 1804289383 ^ 1681692777);
}




Test(BoardEvaluatorTests, didPlayerWin_Right)
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

    cr_assert_eq(evaluator.didPlayerWin(board, player_types::PLAYER), false);
    cr_assert_eq(evaluator.didPlayerWin(board, player_types::AI), true);

    board.reset();

    board.makeMove(8, 8, player_types::PLAYER);
    board.makeMove(9, 9, player_types::PLAYER);
    board.makeMove(10, 10, player_types::PLAYER);
    board.makeMove(11, 11, player_types::PLAYER);
    cr_assert_eq(evaluator.didPlayerWin(board, player_types::PLAYER), false);
    board.makeMove(12, 12, player_types::PLAYER);
    cr_assert_eq(evaluator.didPlayerWin(board, player_types::PLAYER), true);

}



Test(globalIntelligence, testOne)
{
    GoAI ai;
    Board board;
    std::string output;


    cr_redirect_stdout();
    board.makeMove(9, 4, player_types::PLAYER);
    board.makeMove(9, 5, player_types::PLAYER);
    board.makeMove(9, 6, player_types::PLAYER);
    board.makeMove(9, 7, player_types::PLAYER);

    ai.startThinking(board, 1000, false);
    board.reset();

    board.makeMove(0, 0, player_types::AI);
    board.makeMove(1, 1, player_types::AI);
    board.makeMove(2, 2, player_types::AI);
    board.makeMove(3, 3, player_types::AI);
    ai.startThinking(board, 1000, false);

    cr_assert_stdout_eq_str("3,9\n4,4\n");
}



Test(globalIntelligence, basicDefenseDiagonal)
{
    GoAI ai;
    Board board;
    cr_redirect_stdout();

    board.makeMove(6, 6, player_types::PLAYER);
    board.makeMove(7, 7, player_types::PLAYER);
    board.makeMove(8, 8, player_types::PLAYER);

    ai.startThinking(board, 3000, false);
    cr_assert_stdout_eq_str("5,5\n");
}

/*

GTEST_TEST(globalIntelligence, shouldDefendDiagonal)
{
    GoAI ai;
    Board board;
    std::string output = "";

    board.makeMove(2, 2, player_types::AI);
    board.makeMove(2, 5, player_types::AI);

    board.makeMove(7, 7, player_types::PLAYER);
    board.makeMove(8, 8, player_types::PLAYER);
    board.makeMove(9, 9, player_types::PLAYER);

    testing::internal::CaptureStdout();
    ai.startThinking(board, 5000, false);
    output = testing::internal::GetCapturedStdout();
    //std::cout << "output: " << output << std::endl;
    ASSERT_NE(output, "4,2\n");
    ASSERT_NE(output, "3,2\n");
}
*/


Test(globalIntelligence, shouldPreferToDefendThanAttack)
{
    GoAI ai;
    Board board;
    std::string output = "";

    cr_redirect_stdout();
    board.makeMove(1, 0, player_types::AI);
    board.makeMove(1, 1, player_types::PLAYER);
    board.makeMove(1, 2, player_types::PLAYER);
    board.makeMove(1, 3, player_types::PLAYER);
    board.makeMove(1, 4, player_types::PLAYER);

    board.makeMove(2, 0, player_types::PLAYER);
    board.makeMove(2, 1, player_types::AI);
    board.makeMove(2, 2, player_types::AI);
    board.makeMove(2, 4, player_types::AI);

 //   board.printToOutput();

  //  testing::internal::CaptureStdout();
    ai.startThinking(board, 5000, false);
    //output = testing::internal::GetCapturedStdout();
    cr_assert_stdout_eq_str("5,1\n");
}

/*
int main(int ac, char **av)
{
    ::testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}
*/