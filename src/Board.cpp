/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Board
*/

#include "Board.hpp"
#include "Utils.hpp"
#include <iostream>

Board::Board() {}

Board::~Board() {}

void Board::printToOutput()
{
    std::cout << "AI Bitboard" << std::endl;
    this->bitboards[0].printToOutput();
    std::cout << "Player Bitboard" << std::endl;
    this->bitboards[1].printToOutput();

    std::cout << "Final Board" << std::endl;
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            int entityType = -1;
            for (int bitboardIndex = 0; bitboardIndex < 2; bitboardIndex++) {
                if (this->bitboards[bitboardIndex].get_bit(y, x)) {
                    entityType = bitboardIndex;
                    break;
                }
            }
            std::cout << " " << (entityType != -1 ? Utils::getPlayerChar(static_cast<player_types>(entityType)) : '.');
        }
        std::cout << "\n";
    }
}

void Board::makeMove(int y, int x, player_types type)
{
    this->bitboards[type].set_bit(y, x);
}

void Board::unmakeMove(int y, int x, player_types type)
{
    this->bitboards[type].unset_bit(y, x);
}

void Board::reset()
{
    this->bitboards[0].reset();
    this->bitboards[1].reset();
}