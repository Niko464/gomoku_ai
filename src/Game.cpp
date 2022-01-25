/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Game
*/

#include "Game.hpp"

Game::Game() {
    this->_board.makeMove(0, 0, player_types::AI);
    this->_board.makeMove(3, 2, player_types::PLAYER);
    this->_board.makeMove(5, 3, player_types::PLAYER);
    this->_board.unmakeMove(3, 2, player_types::PLAYER);
    this->_board.reset();
    this->_board.printToOutput();
}

Game::~Game() {}