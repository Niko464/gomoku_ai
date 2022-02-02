/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** BoardEvaluator
*/

#include "BoardEvaluator.hpp"
#include "Utils.hpp"
#include <iostream>

BoardEvaluator::BoardEvaluator() {}

BoardEvaluator::~BoardEvaluator() {}

int BoardEvaluator::evaluateBoard(Board &board)
{
    return 0;
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