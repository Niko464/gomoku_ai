/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Board
*/

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <vector>

class Board {
public:
    Board(int size);
    ~Board();

    //use makeMove(y, x, 0) to unmakemove
    void makeMove(int y, int x, int playerType);
    std::vector<std::vector<int>> &getBoard();

    void printToOutput();
private:
    int _size;
    std::vector<std::vector<int>> _board;
};

#endif /* !BOARD_HPP_ */
