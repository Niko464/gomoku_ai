/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Program
*/

#include "Program.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>

Program::Program()
{
    this->_shouldGetInput = true;
    //this->_inputThread = std::thread(&Program::startInputLoop, this);
}

Program::~Program()
{
    this->_shouldGetInput = false;
    //this->_inputThread.join();
}

void Program::startInputLoop()
{
    std::string entry;
    while (this->_shouldGetInput) {
        std::getline(std::cin, entry);
        this->parseEntry(entry);
    }
}

void Program::parseEntry(std::string &entry)
{
    std::vector<std::string> splitted = Utils::splitStr(entry);

    for (int i = 0; i < splitted.size(); i++)
        std::cout << "AAA " << splitted[i] << std::endl;
    std::cout << "finished parsing lol" << std::endl;
}