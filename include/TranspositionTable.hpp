/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** TranspositionTable
*/

#ifndef TRANSPOSITIONTABLE_HPP_
#define TRANSPOSITIONTABLE_HPP_

#include <vector>
#include "Board.hpp"
#include <unordered_map>

struct TranspositionValue {
    int score;
};

class TranspositionTable {
public:
    TranspositionTable(unsigned int seed);
    ~TranspositionTable();

    int computeHash(Board &board);
    bool knowsHash(const int hash);
    //TODO: should this take a reference ?
    void storeHash(const int hash, const TranspositionValue value);

private:
    std::vector<std::pair<int, int>> _keys;
    std::unordered_map<int, TranspositionValue> _table; 
};

#endif /* !TRANSPOSITIONTABLE_HPP_ */
