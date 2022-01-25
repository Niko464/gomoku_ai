/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "Board.hpp"

class Game {
public:
    Game();
    ~Game();

private:
    Board _board;
};

#endif /* !GAME_HPP_ */
