/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "Board.hpp"
#include "GoAI.hpp"

class Game {
public:
    Game();
    ~Game();

    void reset();
    bool makeMove(player_types playerType, int y, int x);
    void aiStartThinking();
    void setTimeOut(int timeoutMs);

private:
    Board _board;
    GoAI _ai;
    int _timeout;
};

#endif /* !GAME_HPP_ */
