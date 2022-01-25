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
#include <functional>

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
    std::vector<std::pair<const char *, ProgramPtrFn>> fnPtrs = {
        std::pair<const char *, ProgramPtrFn>("START", &Program::startCmd),
        std::pair<const char *, ProgramPtrFn>("TURN", &Program::turnCmd),
        std::pair<const char *, ProgramPtrFn>("BEGIN", &Program::beginCmd),
        std::pair<const char *, ProgramPtrFn>("BOARD", &Program::boardCmd),
        std::pair<const char *, ProgramPtrFn>("INFO", &Program::infoCmd),
        std::pair<const char *, ProgramPtrFn>("END", &Program::endCmd),
        std::pair<const char *, ProgramPtrFn>("ABOUT", &Program::aboutCmd)
    };
    std::vector<std::string> splitted = Utils::splitStr(entry, " ");

    if (splitted.size() == 0)
        return;
    for (int amtCmds = 0; amtCmds < fnPtrs.size(); amtCmds++) {
        if (splitted.at(0).compare(fnPtrs.at(amtCmds).first) == 0) {
            CALL_MEMBER_FN(*this, fnPtrs.at(amtCmds).second)(splitted);
            break;
        }
    }
    std::cout << "finished parsing lol" << std::endl;
}

void Program::startCmd(std::vector<std::string> &parmas) {}
void Program::turnCmd(std::vector<std::string> &parmas) {}
void Program::beginCmd(std::vector<std::string> &parmas) {}
void Program::boardCmd(std::vector<std::string> &parmas) {}
void Program::infoCmd(std::vector<std::string> &parmas) {}
void Program::endCmd(std::vector<std::string> &parmas) {}
void Program::aboutCmd(std::vector<std::string> &parmas) {}