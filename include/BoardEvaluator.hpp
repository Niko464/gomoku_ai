/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** BoardEvaluator
*/

#ifndef BOARDEVALUATOR_HPP_
#define BOARDEVALUATOR_HPP_

#include "Board.hpp"

class BoardEvaluator {
public:
    BoardEvaluator();
    ~BoardEvaluator();

    //TODO: check if this function should know who's turn it is
    //TODO: this needs to return a really high number if ai wins and vice versa
    int evaluateBoard(Board &board);

private:

};

#endif /* !BOARDEVALUATOR_HPP_ */
