/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Board
*/

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <vector>
#include "BitBoard.hpp"
#include "PlayerTypes.hpp"

class Board {
public:
    Board();
    ~Board();

    void makeMove(int y, int x, player_types playerType);
    void unmakeMove(int y, int x, player_types playerType);
    void reset();
    std::vector<std::bitset<20>> &getPlayerBoard(int playerType);

    void printToOutput();
private:
    BitBoard bitboards[2];
};

#endif /* !BOARD_HPP_ */
