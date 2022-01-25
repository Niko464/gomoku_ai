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

    bool _isWaitingForBoardParams;
    void parseEntry(std::string &name);
    void startCmd(std::vector<std::string> &params);
    void turnCmd(std::vector<std::string> &params);
    void beginCmd(std::vector<std::string> &params);
    void boardCmd(std::vector<std::string> &params);
    void boardCmdArg(std::vector<std::string> &params);
    void infoCmd(std::vector<std::string> &params);
    void endCmd(std::vector<std::string> &params);
    void aboutCmd(std::vector<std::string> &params);
};

typedef void (Program::*ProgramPtrFn)(std::vector<std::string> &);
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

#endif /* !PROGRAM_HPP_ */
