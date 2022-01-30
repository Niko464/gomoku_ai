/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Board
*/

#include "BitBoard.hpp"
#include <iostream>

BitBoard::BitBoard() {}

BitBoard::~BitBoard() {}

void BitBoard::printToOutput()
{
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++)
            std::cout << this->_bitboard[(y * 20) + x] << " ";
        std::cout << "\n";
    }
}

void BitBoard::set_bit(int y, int x)
{
    this->_bitboard.set((y * 20) + x);
}

void BitBoard::unset_bit(int y, int x)
{
    this->_bitboard.reset((y * 20) + x);
}

bool BitBoard::get_bit(int y, int x)
{
    return this->_bitboard.test((y * 20) + x);
}

void BitBoard::reset()
{
    this->_bitboard.reset();
}

std::bitset<400> &BitBoard::getBitboard()
{
    return this->_bitboard;
}