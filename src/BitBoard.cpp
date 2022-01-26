/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Board
*/

#include "BitBoard.hpp"
#include <iostream>

BitBoard::BitBoard()
{
    this->_bitboard.reserve(20);
    for (int y = 0; y < 20; y++) {
        this->_bitboard.push_back(std::bitset<20>());
    }
}

BitBoard::~BitBoard() {}

void BitBoard::printToOutput()
{
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++)
            std::cout << this->_bitboard[y][x] << " ";
        std::cout << "\n";
    }
}

void BitBoard::set_bit(int y, int x)
{
    this->_bitboard[y].set(x);
}

void BitBoard::unset_bit(int y, int x)
{
    this->_bitboard[y].reset(x);
}

bool BitBoard::get_bit(int y, int x)
{
    return this->_bitboard[y].test(x);
}

void BitBoard::reset()
{
    for (int y = 0; y < 20; y++)
        this->_bitboard[y].reset();
}

std::vector<std::bitset<20>> &BitBoard::getBitboard()
{
    return this->_bitboard;
}