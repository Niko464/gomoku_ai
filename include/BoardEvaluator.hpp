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
#include <unordered_map>

struct evaluatorSizes {
    int testSizeY;
    int testSizeX;
    bool hasSpaces;
    std::bitset<400> testCase;
    std::bitset<400> spaceTestCase;
};

typedef evaluatorSizes eval_t;

class BoardEvaluator {
public:
    BoardEvaluator();
    ~BoardEvaluator();

    int evaluateBoard(Board &board);
    bool didPlayerWin(Board &board, player_types playerType);

    void _findPattern(
        evaluatorSizes &params,
        Board &board,
        std::function<void(Board &, evaluatorSizes &)> callback
    );

private:
    int _lateralSearch(Board &board, std::string const &pattern, int value, player_types player);
    int _verticalSearch(Board &board, std::string const &pattern, int value, player_types player);
    int _diagonalSearch(Board &board, std::string const &pattern, int value, player_types player);
    int _getScoreFromPattern(Board &board, std::string const &pattern, int value);
    std::unordered_map<std::string, int> __patterns;
};

#endif /* !BOARDEVALUATOR_HPP_ */
