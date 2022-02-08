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
    {"011110", 100000},

    {"10111", 45000},
    {"11011", 45000},
    {"11101", 45000},

    {"01111", 42000},
    {"11110", 42000},

    {"011100", 20000},
    {"001110", 20000},

    {"01011", 12000},
    {"10110", 12000},
    {"11010", 12000},
    {"01101", 12000}

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
    /*std::string reverse = pattern;

    std::reverse(reverse.begin(), reverse.end());*/
    int score = 0;

    score += _verticalSearch(board, pattern, value, player_types::AI) - _verticalSearch(board, pattern, value, player_types::PLAYER);
    score += _lateralSearch(board, pattern, value, player_types::AI) - _lateralSearch(board, pattern, value, player_types::PLAYER);
    score += _diagonalSearch(board, pattern, value, player_types::AI) - _diagonalSearch(board, pattern, value, player_types::PLAYER);
    /*score += _verticalSearch(board, reverse, value, player_types::AI) - _verticalSearch(board, reverse, value, player_types::PLAYER);
    score += _lateralSearch(board, reverse, value, player_types::AI) - _lateralSearch(board, reverse, value, player_types::PLAYER);
    score += _diagonalSearch(board, reverse, value, player_types::AI) - _diagonalSearch(board, reverse, value, player_types::PLAYER);*/
    return (score);
}

int BoardEvaluator::_verticalSearch(Board &board, std::string const &pattern, int value, player_types player)
{
    int score = 0;
    eval_t Case;

    Case.testSizeX = 1;
    Case.testSizeY = pattern.length();
    Case.hasSpaces = (pattern.find_first_of('0') != std::string::npos);
    for (int i = 0; i <= (Case.testSizeY - 1); i++)
        (pattern[i] == '1') ? Case.testCase.set(i * 20) : Case.spaceTestCase.set(i * 20);
    this->_findPattern(Case, board, [&](Board &myBoard, evaluatorSizes &params) {
        std::bitset<400> &aiBoard = myBoard.getPlayerBoard(player_types::AI);
        std::bitset<400> &playerBoard = myBoard.getPlayerBoard(player_types::PLAYER);

       if ((((player == player_types::AI ? aiBoard : playerBoard) & params.testCase) == params.testCase) &&
            (!params.hasSpaces || (~aiBoard & params.spaceTestCase) == params.spaceTestCase) && (~playerBoard & params.spaceTestCase) == params.spaceTestCase) {
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
    Case.hasSpaces = (pattern.find_first_of('0') != std::string::npos);
    for (int i = 0; i <= (Case.testSizeX - 1); i++)
        (pattern[i] == '1') ? Case.testCase.set(i) : Case.spaceTestCase.set(i);
    this->_findPattern(Case, board, [&](Board &myBoard, evaluatorSizes &params) {
        std::bitset<400> &aiBoard = myBoard.getPlayerBoard(player_types::AI);
        std::bitset<400> &playerBoard = myBoard.getPlayerBoard(player_types::PLAYER);
        if ((((player == player_types::AI ? aiBoard : playerBoard) & params.testCase) == params.testCase) &&
            (!params.hasSpaces || (~aiBoard & params.spaceTestCase) == params.spaceTestCase) && (~playerBoard & params.spaceTestCase) == params.spaceTestCase) {
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
    Case.hasSpaces = (pattern.find_first_of('0') != std::string::npos);

    std::function<void(Board &, evaluatorSizes &)> cb = [&](Board &myBoard, evaluatorSizes &params) {
        std::bitset<400> &aiBoard = myBoard.getPlayerBoard(player_types::AI);
        std::bitset<400> &playerBoard = myBoard.getPlayerBoard(player_types::PLAYER);

        if ((((player == player_types::AI ? aiBoard : playerBoard) & params.testCase) == params.testCase) &&
            (!params.hasSpaces || (~aiBoard & params.spaceTestCase) == params.spaceTestCase) && (~playerBoard & params.spaceTestCase) == params.spaceTestCase) {
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
    return (this->_getScoreFromPattern(board, "11111", 1) == (playerTypes == player_types::AI ? 1 : -1));
}