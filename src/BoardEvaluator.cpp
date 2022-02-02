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
    evaluatorSizes testCaseRight = {1, 5, false, 0, 0};
    testCaseRight.testCase.set(0);
    testCaseRight.testCase.set(1);
    testCaseRight.testCase.set(2);
    testCaseRight.testCase.set(3);
    testCaseRight.testCase.set(4);

    this->_findPattern(testCaseRight, board,
        [this](Board &myBoard, evaluatorSizes &params) {
            Utils::printBitBoard<400>(20, 20, params.testCase);
            std::cout << "\n" << std::endl;
        }
    );
}