/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** GoProgram
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <vector>
#include <string>
#include "PlayerTypes.hpp"

namespace Utils {
    std::vector<std::string> splitStr(const std::string &s, const std::string &del);
    char getPlayerChar(player_types type);
    bool isInt(const std::string &str);
}

#endif