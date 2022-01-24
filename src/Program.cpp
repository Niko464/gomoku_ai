/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Program
*/

#include "Program.hpp"
#include <iostream>
#include <string>

Program::Program() : _shouldGetInput(true)
{
}

Program::~Program()
{
    this->_shouldGetInput = false;
    this->_inputThread.join();
}

void Program::startInputLoop()
{
    std::string cmd;
    while (this->_shouldGetInput) {
        std::getline(std::cin, cmd);
        std::cout << cmd;
    }
}