/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** TranspositionTable
*/

#include "TranspositionTable.hpp"
#include <cstdlib>

TranspositionTable::TranspositionTable(unsigned int seed)
{
    srand(seed);
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            int randIA = rand();
            int randPlayer = rand();
            this->_keys.push_back(std::make_pair(randIA, randPlayer));
        }
    }
    /*this->_turnKeys.push_back(rand());
    this->_turnKeys.push_back(rand());*/
}

TranspositionTable::~TranspositionTable() {}

int TranspositionTable::computeHash(Board &board)
{
    int hash = 0;

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            if (board.isSquareTakenBy(y, x, player_types::AI))
                hash ^= this->_keys[(y * 20) + x].first;
            else if (board.isSquareTakenBy(y, x, player_types::PLAYER))
                hash ^= this->_keys[(y * 20) + x].second;
        }
    }
    return hash;
}

bool TranspositionTable::knowsHash(const int hash)
{
    return !(this->_table.find(hash) == this->_table.end());
}

void TranspositionTable::storeHash(const int hash, TranspositionValue value)
{
    this->_table.insert(std::make_pair(hash, value));
}

TranspositionValue &TranspositionTable::getStoredValue(const int hash)
{
    return this->_table.at(hash);
}