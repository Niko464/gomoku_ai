/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Board
*/

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "BitBoard.hpp"
#include "PlayerTypes.hpp"
#include <vector>

class Board {
public:
    Board();
    ~Board();

    bool canMakeMove(int y, int x);
    void makeMove(int y, int x, player_types playerType);
    void unmakeMove(int y, int x, player_types playerType);
    void reset();
    std::bitset<400> &getPlayerBoard(player_types playerType);

    void printToOutput();

    std::vector<std::pair<int, int>> getValidMoves();
private:
    BitBoard bitboards[2];
};

#endif /* !BOARD_HPP_ */
