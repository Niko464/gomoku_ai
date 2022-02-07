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
#include <Vec2.hpp>

class Board {
public:
    Board();
    ~Board();

    bool canMakeMove(int y, int x);
    void makeMove(int y, int x, player_types playerType);
    void unmakeMove(int y, int x, player_types playerType);
    void reset();
    std::bitset<400> &getPlayerBoard(player_types playerType);
    std::vector<Vec2> getValidMoves(int radius);
    bool isSquareTakenBy(int y, int x, player_types playerType);
    void printToOutput();
    void _checkSurroundings(std::vector<Vec2> &coords, int x, int y, int radius);
private:
    BitBoard bitboards[2];
};

#endif /* !BOARD_HPP_ */
