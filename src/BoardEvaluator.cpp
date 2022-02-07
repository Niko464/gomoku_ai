/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** BoardEvaluator
*/

#include "BoardEvaluator.hpp"
#include "Utils.hpp"
#include <iostream>
#include <algorithm>
BoardEvaluator::BoardEvaluator() : __patterns({
    {"011110", 20000},
    {"01111", 20000},
    {"10111", 20000},
    {"11011", 20000},
    {"11101", 20000},
    {"11110", 20000},
    {"011100", 20000},
    {"001110", 20000},
    {"01011", 20000},
    {"10110", 20000}
}) {}

BoardEvaluator::~BoardEvaluator() {}

int BoardEvaluator::evaluateBoard(Board &board)
{
    int score = 0;

    for (auto pattern : __patterns)
        score += this->_getScoreFromPattern(board, pattern.first, pattern.second);
    return (score);
}

int BoardEvaluator::_getScoreFromPattern(Board &board, std::string const &pattern, int value)
{
    std::string reverse = pattern;

    std::reverse(reverse.begin(), reverse.end());
    int score = 0;

    score += _verticalSearch(board, pattern, value, player_types::AI) - _verticalSearch(board, pattern, value, player_types::PLAYER);
    score += _lateralSearch(board, pattern, value, player_types::AI) - _lateralSearch(board, pattern, value, player_types::PLAYER);
    score += _diagonalSearch(board, pattern, value, player_types::AI) - _diagonalSearch(board, pattern, value, player_types::PLAYER);
    score += _verticalSearch(board, reverse, value, player_types::AI) - _verticalSearch(board, reverse, value, player_types::PLAYER);
    score += _lateralSearch(board, reverse, value, player_types::AI) - _lateralSearch(board, reverse, value, player_types::PLAYER);
    score += _diagonalSearch(board, reverse, value, player_types::AI) - _diagonalSearch(board, reverse, value, player_types::PLAYER);
    return (score);
}

int BoardEvaluator::_verticalSearch(Board &board, std::string const &pattern, int value, player_types player)
{
    int score = 0;
    eval_t Case;

    Case.testSizeX = 1;
    Case.testSizeY = pattern.length();
    Case.hasSpaces = (pattern.find_first_of(' ') != std::string::npos);
    for (int i = 0; i <= (Case.testSizeY - 1); i++)
        (pattern[i] == '1') ? Case.testCase.set(i * 20) : Case.spaceTestCase.set(i * 20);
    this->_findPattern(Case, board, [&](Board &myBoard, evaluatorSizes &params) {
        std::bitset<400> &aiBoard = myBoard.getPlayerBoard(player_types::AI);
        std::bitset<400> &playerBoard = myBoard.getPlayerBoard(player_types::PLAYER);

        if ((((player == player_types::AI ? aiBoard : playerBoard) & params.testCase) == params.testCase) &&
            (!params.hasSpaces || (aiBoard ^ params.spaceTestCase) == params.spaceTestCase && (playerBoard ^ params.spaceTestCase) == params.spaceTestCase)) {
            score += value;
        }
    });
    return (score);
}

int BoardEvaluator::_lateralSearch(Board &board, std::string const &pattern, int32_t value, player_types player)
{
    int score = 0;
    eval_t Case;

    Case.testSizeX = pattern.length();
    Case.testSizeY = 1;
    Case.hasSpaces = (pattern.find_first_of(' ') != std::string::npos);
    for (int i = 0; i <= (Case.testSizeX - 1); i++)
        (pattern[i] == '1') ? Case.testCase.set(i) : Case.spaceTestCase.set(i);
    this->_findPattern(Case, board, [&](Board &myBoard, evaluatorSizes &params) {
        std::bitset<400> &aiBoard = myBoard.getPlayerBoard(player_types::AI);
        std::bitset<400> &playerBoard = myBoard.getPlayerBoard(player_types::PLAYER);

        if ((((player == player_types::AI ? aiBoard : playerBoard) & params.testCase) == params.testCase) &&
            (!params.hasSpaces || (aiBoard ^ params.spaceTestCase) == params.spaceTestCase && (playerBoard ^ params.spaceTestCase) == params.spaceTestCase)) {
            score += value;
        }
    });
    return (score);
}

int BoardEvaluator::_diagonalSearch(Board &board, std::string const &pattern, int32_t value, player_types player)
{
    int score = 0;
    eval_t Case;
    Case.testSizeX = Case.testSizeY = pattern.length();
    Case.hasSpaces = (pattern.find_first_of(' ') != std::string::npos);

    std::function<void(Board &, evaluatorSizes &)> cb = [&](Board &myBoard, evaluatorSizes &params) {
        std::bitset<400> &aiBoard = myBoard.getPlayerBoard(player_types::AI);
        std::bitset<400> &playerBoard = myBoard.getPlayerBoard(player_types::PLAYER);

        if ((((player == player_types::AI ? aiBoard : playerBoard) & params.testCase) == params.testCase) &&
            (!params.hasSpaces || (aiBoard ^ params.spaceTestCase) == params.spaceTestCase && (playerBoard ^ params.spaceTestCase) == params.spaceTestCase)) {
            score += value;
        }
    };
    for (int i = 0; i <= (Case.testSizeX - 1); i++) {
        if (pattern[i] == '1')
            Case.testCase.set(i + (i * 20));
        else
            Case.spaceTestCase.set(i + (i * 20));
    }
    this->_findPattern(Case, board, cb);
    Case.testCase.reset();
    Case.testCase.reset();
    for (int i = 0; i <= (Case.testSizeX - 1); i++) {
        if (pattern[i] == '1')
            Case.testCase.set((Case.testSizeX - i - 1) + (i * 20));
        else
            Case.spaceTestCase.set((Case.testSizeX - i - 1) + (i * 20));
    }
    this->_findPattern(Case, board, cb);
    return (score);
}

void BoardEvaluator::_findPattern(
    evaluatorSizes &params,
    Board &board,
    std::function<void(Board &, evaluatorSizes &)> callback)
{
    for (int y = 0; y <= 20 - params.testSizeY; y++) {
        for (int x = 0; x <= 20 - params.testSizeX; x++) {

            callback(board, params);

            params.testCase <<= 1;
            if (params.hasSpaces)
                params.spaceTestCase <<= 1;
        }
        params.testCase <<= params.testSizeX - 1;
        if (params.hasSpaces)
            params.spaceTestCase <<= params.testSizeX - 1;
    }
}

bool BoardEvaluator::didPlayerWin(Board &board, player_types playerTypes)
{
    bool to_return = false;

    evaluatorSizes testcase = {1, 5, false};

    testcase.testCase.set(0);
    testcase.testCase.set(1);
    testcase.testCase.set(2);
    testcase.testCase.set(3);
    testcase.testCase.set(4);

    std::function<void(Board &, evaluatorSizes &)> func = [&](Board &myBoard, evaluatorSizes &params) {
        std::bitset<400> &aiBoard = myBoard.getPlayerBoard(player_types::AI);
        std::bitset<400> &playerBoard = myBoard.getPlayerBoard(player_types::PLAYER);

        if ((((playerTypes == player_types::AI ? aiBoard : playerBoard) & params.testCase) == params.testCase) &&
            (!params.hasSpaces || (aiBoard ^ params.spaceTestCase) == params.spaceTestCase && (playerBoard ^ params.spaceTestCase) == params.spaceTestCase)) {
            to_return = true;
        }
        
    };

    this->_findPattern(testcase, board, func);
    testcase.testCase.reset();
    testcase.testSizeX = 5;
    testcase.testSizeY = 5;
    testcase.testCase.set(0);
    testcase.testCase.set(21);
    testcase.testCase.set(42);
    testcase.testCase.set(63);
    testcase.testCase.set(84);
    this->_findPattern(testcase, board, func);
    testcase.testCase.reset();
    testcase.testCase.set(4);
    testcase.testCase.set(23);
    testcase.testCase.set(42);
    testcase.testCase.set(61);
    testcase.testCase.set(80);
    this->_findPattern(testcase, board, func);
    testcase.testCase.reset();
    testcase.testSizeX = 1;
    testcase.testSizeY = 5;
    testcase.testCase.set(0);
    testcase.testCase.set(20);
    testcase.testCase.set(40);
    testcase.testCase.set(60);
    testcase.testCase.set(80);
    this->_findPattern(testcase, board, func);
    return to_return;
}