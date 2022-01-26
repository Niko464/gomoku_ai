/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** BITBOARD
*/

#ifndef BITBOARD_HPP_
#define BITBOARD_HPP_

#include <vector>
#include <bitset>

class BitBoard {
public:
    BitBoard();
    ~BitBoard();

    //use makeMove(y, x, 0) to unmakemove
    void set_bit(int y, int x);
    void unset_bit(int y, int x);
    bool get_bit(int y, int x);
    void reset();

    std::vector<std::bitset<20>> &getBitboard();

    void printToOutput();
private:
    std::vector<std::bitset<20>> _bitboard;
};

#endif /* !BITBOARD_HPP_ */
