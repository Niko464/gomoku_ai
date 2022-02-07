/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Board
*/

#include "Board.hpp"
#include "Utils.hpp"
#include <iostream>
#include <algorithm>

Board::Board() {}

Board::~Board() {}

void Board::printToOutput()
{
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            int entityType = -1;
            for (int bitboardIndex = 0; bitboardIndex < 2; bitboardIndex++) {
                if (this->bitboards[bitboardIndex].get_bit(y, x)) {
                    entityType = bitboardIndex;
                    break;
                }
            }
            if (x == 0)
                std::cout << "MESSAGE";
            std::cout << " " << (entityType != -1 ? Utils::getPlayerChar(static_cast<player_types>(entityType)) : '.');
        }
        std::cout << std::endl;
    }
}

bool Board::canMakeMove(int y, int x)
{
    return !(this->bitboards[0].get_bit(y, x) || this->bitboards[1].get_bit(y, x));
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

std::bitset<400> &Board::getPlayerBoard(player_types playerType)
{
    return this->bitboards[playerType].getBitboard();
}

void Board::_checkSurroundings(std::vector<Vec2> &coords, int x, int y, int radius)
{
    int i_min, j_min, i_max, j_max = 0;

    if (y - radius >= 0)
        i_min = y - radius;
    else
        i_min = 0;
    if (x - radius >= 0)
        j_min = x - radius;
    else
        j_min = 0;
    
    
    if (y + radius <= 19)
        i_max = y + radius;
    else
        i_max = 19;
    if (x + radius <= 19)
        j_max = x + radius;
    else
        j_max = 19;

    for (int i = i_min; i <= i_max; i++) {
        for (int j = j_min; j <= j_max; j++) {
            if (this->canMakeMove(i, j) && std::find_if(coords.begin(), coords.end(),
                [i, j](Vec2 &coords) {
                    return (i == coords.y && j == coords.x);
                }) == coords.end()) {
                Vec2 toPush;
                toPush.y = i;
                toPush.x = j;
                coords.push_back(toPush);
                }
        }
    }
}

std::vector<Vec2> Board::getValidMoves(int radius)
{
    std::vector<Vec2> to_return;

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            if (!this->canMakeMove(y, x)) {
                this->_checkSurroundings(to_return, x, y, radius);
            }
        }       
    }
    return to_return;
}

bool Board::isSquareTakenBy(int y, int x, player_types playerType)
{
    return this->bitboards[playerType].get_bit(y, x);
}