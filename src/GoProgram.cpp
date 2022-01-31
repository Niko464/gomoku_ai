/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** GoProgram
*/

#include "GoProgram.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>
#include <functional>

GoProgram::GoProgram()
{
    this->_shouldGetInput = true;
    this->_isWaitingForBoardParams = false;
    //this->_inputThread = std::thread(&GoProgram::startInputLoop, this);
}

GoProgram::~GoProgram()
{
    this->_shouldGetInput = false;
    //this->_inputThread.join();
}

//TODO: we should limit the getline command to a max length so that we can't crash because of a too long line
void GoProgram::startInputLoop()
{
    std::string entry;
    while (this->_shouldGetInput) {
        std::getline(std::cin, entry);
        this->parseEntry(entry);
    }
}

void GoProgram::parseEntry(std::string &entry)
{
    std::vector<std::pair<const char *, GoProgramPtrFn>> fnPtrs = {
        std::pair<const char *, GoProgramPtrFn>("START", &GoProgram::startCmd),
        std::pair<const char *, GoProgramPtrFn>("TURN", &GoProgram::turnCmd),
        std::pair<const char *, GoProgramPtrFn>("BEGIN", &GoProgram::beginCmd),
        std::pair<const char *, GoProgramPtrFn>("BOARD", &GoProgram::boardCmd),
        std::pair<const char *, GoProgramPtrFn>("INFO", &GoProgram::infoCmd),
        std::pair<const char *, GoProgramPtrFn>("END", &GoProgram::endCmd),
        std::pair<const char *, GoProgramPtrFn>("ABOUT", &GoProgram::aboutCmd)
    };
    std::vector<std::string> splitted = Utils::splitStr(entry, " ");
    bool foundCmd = false;

    if (splitted.size() == 0)
        return;
    for (size_t amtCmds = 0; amtCmds < fnPtrs.size(); amtCmds++) {
        if (splitted.at(0).compare(fnPtrs.at(amtCmds).first) == 0) {
            foundCmd = true;
            CALL_MEMBER_FN(*this, fnPtrs.at(amtCmds).second)(splitted);
            break;
        }
    }
    if (this->_isWaitingForBoardParams && foundCmd == false) {
        foundCmd = true;
        boardCmdArg(splitted);
    }
    if (foundCmd == false) {
        std::cout << "UNKNOWN - command not implemented" << std::endl;
        return;
    }
}

void GoProgram::startCmd(std::vector<std::string> &params)
{
    int size = -1;
    if (params.size() != 2 || !Utils::isInt(params[1])) {
        std::cout << "ERROR message - you sent the wrong parameters" << std::endl;
        return;
    }
    size = std::stoi(params[1]);
    if (size != 20) {
        std::cout << "ERROR message - I don't accept that size, I hate it" << std::endl;
        return;
    }
    this->_game.reset();
    std::cout << "OK" << std::endl;
}

void GoProgram::turnCmd(std::vector<std::string> &params)
{
    if (params.size() != 2) {
        std::cout << "ERROR message - you sent the wrong amount of parameters" << std::endl;
        return;
    }
    std::vector<std::string> splitted = Utils::splitStr(params[1], ",");
    if (!Utils::isInt(splitted[0]) || !Utils::isInt(splitted[1])) {
        std::cout << "ERROR message - those aren't ints as params" << std::endl;
        return;
    }
    if (this->_game.makeMove(player_types::PLAYER, std::stoi(splitted[1]), std::stoi(splitted[0])) == false) {
        std::cout << "ERROR message - you can't move here, I don't exactly know why but you can't." << std::endl;
        return;
    }
    this->_game.aiStartThinking();
}

void GoProgram::beginCmd(std::vector<std::string> &params)
{
    this->_game.aiStartThinking();
}

void GoProgram::boardCmd(std::vector<std::string> &params)
{
    this->_game.reset();
    this->_isWaitingForBoardParams = true;
}

void GoProgram::boardCmdArg(std::vector<std::string> &params)
{
    if (params.at(0).compare("DONE") == 0) {
        this->_isWaitingForBoardParams = false;
        this->_game.aiStartThinking();
        return;
    }
    std::vector<std::string> splitted = Utils::splitStr(params[0], ",");
    if (splitted.size() != 3) {
        std::cerr << "This shouldn't be possible, boardCmdArg doesn't have three args it has " << splitted.size() << std::endl;
        return;
    }
    if (!Utils::isInt(splitted[0]) || !Utils::isInt(splitted[1]) || !Utils::isInt(splitted[2])) {
        std::cerr << "boardCmdArgs aren't ints... " << splitted[0] << " " << splitted[1] << " " << splitted[2] << std::endl;
        return;
    }
    if (this->_game.makeMove(static_cast<player_types>(std::stoi(splitted[2]) - 1), std::stoi(splitted[1]), std::stoi(splitted[0])) == false) {
        std::cerr << "boardCmdArg, I wasn't able to make this move y: " << splitted[1] << " x: " << splitted[0] << std::endl;
        return; 
    }
}

void GoProgram::infoCmd(std::vector<std::string> &params)
{
    if (params.size() < 3) {
        std::cout << "ERROR - wrong amount of parameters for info command" << std::endl;
        return;
    }
    if (params[1].compare("timeout_turn") == 0) {
        if (!Utils::isInt(params[2])) {
            std::cout << "ERROR - timeout_turn didn't receive an int" << std::endl;
            return;
        }
        this->_game.setTimeOut(std::stoi(params[2]));
    }
}

void GoProgram::endCmd(std::vector<std::string> &params)
{
    this->_shouldGetInput = false;
}

void GoProgram::aboutCmd(std::vector<std::string> &params)
{
    std::cout << "name=\"slave\", version=\"0.1\", author=\"Niko&Kevin\", country=\"France\", negatives=\"none\"" << std::endl;
}