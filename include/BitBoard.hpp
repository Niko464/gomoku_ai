/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** BITBOARD
*/

#ifndef BITBOARD_HPP_
#define BITBOARD_HPP_

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

    std::bitset<400> &getBitboard();

    void printToOutput();
private:
    std::bitset<400> _bitboard;
};

#endif /* !BITBOARD_HPP_ */
