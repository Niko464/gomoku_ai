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
#include "Vec2.hpp"

enum TranspositionType {
    EXACT,
    UPPER,
    LOWER
};

struct TranspositionValue {
    int value;
    int depth;
    Vec2 bestMove;
    TranspositionType type;
};

//TODO: think if the computeHash needs the player turn ????
class TranspositionTable {
public:
    TranspositionTable(unsigned int seed);
    ~TranspositionTable();

    int computeHash(Board &board);
    bool knowsHash(const int hash);
    void storeHash(const int hash, const TranspositionValue &value);
    TranspositionValue &getStoredValue(const int hash);

private:
    //std::vector<int> _turnKeys;
    std::vector<std::pair<int, int>> _keys;
    std::unordered_map<int, TranspositionValue> _table; 
};

#endif /* !TRANSPOSITIONTABLE_HPP_ */
