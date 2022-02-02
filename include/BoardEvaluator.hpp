/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** BoardEvaluator
*/

#ifndef BOARDEVALUATOR_HPP_
#define BOARDEVALUATOR_HPP_

#include "Board.hpp"
#include <functional>

struct evaluatorSizes {
    int testSizeY;
    int testSizeX;
    bool hasSpaces;
    std::bitset<400> testCase;
    std::bitset<400> spaceTestCase;
};

class BoardEvaluator {
public:
    BoardEvaluator();
    ~BoardEvaluator();
    //TODO: check if this function should know who's turn it is
    //TODO: this needs to return a really high number if ai wins and vice versa
    int evaluateBoard(Board &board);
    bool didPlayerWin(Board &board, player_types playerType);

    void _findPattern(
        evaluatorSizes &params,
        Board &board,
        std::function<void(Board &, evaluatorSizes &)> callback
    );

private:
};

#endif /* !BOARDEVALUATOR_HPP_ */
