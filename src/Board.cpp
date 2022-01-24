/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Board
*/

#include "Board.hpp"
#include <iostream>

Board::Board(int size) :
    _size(size)
{
    this->_board.reserve(size);
    for (int y = 0; y < size; y++) {
        std::vector<int> newRow;
        newRow.reserve(size);
        for (int x = 0; x < size; x++)
            newRow.push_back(0);
        this->_board.push_back(newRow);
    }
}

Board::~Board() {}

void Board::printToOutput()
{
    for (int y = 0; y < this->_size; y++) {
        for (int x = 0; x < this->_size; x++)
            std::cout << this->_board[y][x] << " ";
        std::cout << "\n";
    }
}

