/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Utils
*/

#include "Utils.hpp"

#include <iostream>
std::vector<std::string> Utils::splitStr(const std::string &s, const std::string &del)
{
    std::vector<std::string> to_return;

    int start = 0;
    size_t end = s.find(del);
    int count = 0;
    while (end != std::string::npos) {
        to_return.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
        count++;
        if (count == 5)
            break;
    }
    to_return.push_back(s.substr(start, end - start));

    return to_return;
}

char Utils::getPlayerChar(player_types type)
{
    if (type == player_types::AI)
        return 'O';
    return 'X';
}

bool Utils::isInt(const std::string &str)
{
    for (size_t i = 0; i < str.length(); i++) {
        if (!std::isdigit(str[i]) && !(i == 0 && str[i] == '-'))
            return false;
    }
    return true;
}

void Utils::printMoves(std::vector<Vec2> &moves)
{
    for (size_t i = 0; i < moves.size(); i++) {
        std::cout << moves[i].y << "," << moves[i].x << std::endl;
    }
}