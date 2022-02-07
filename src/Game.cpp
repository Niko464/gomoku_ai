/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Game
*/

#include "Game.hpp"

Game::Game()
{
    this->_timeout = 5000;
}

Game::~Game() {}

void Game::reset()
{
    this->_board.reset();
}

bool Game::makeMove(player_types playerType, int y, int x)
{
    if (!this->_board.canMakeMove(y, x))
        return false;
    this->_board.makeMove(y, x, playerType);
    return true;
}

void Game::aiStartThinking()
{
    this->_ai.startThinking(this->_board, this->_timeout);
}

void Game::aiMakeFirstMove()
{
    this->_ai.makeFirstMove(this->_board, this->_timeout);
}

void Game::setTimeOut(int timeoutMs)
{
    this->_timeout = timeoutMs;
}