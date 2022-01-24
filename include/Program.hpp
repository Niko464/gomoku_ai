/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Program
*/

#ifndef PROGRAM_HPP_
#define PROGRAM_HPP_

#include <thread>
#include "Game.hpp"

//this should contain threads if necessary for input && calculations

class Program {
public:
    Program();
    ~Program();

    void startInputLoop();

private:
    bool _shouldGetInput;
    //std::thread _inputThread;
    Game _game;

    void parseEntry(std::string &name);
};

#endif /* !PROGRAM_HPP_ */
