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
#include <bitset>
#include <iostream>

namespace Utils {
    std::vector<std::string> splitStr(const std::string &s, const std::string &del);
    char getPlayerChar(player_types type);
    bool isInt(const std::string &str);

    template <int boardSize>
    void printBitBoard(int sizeY, int sizeX, std::bitset<boardSize> &bitboard)
    {
        for (int y = 0; y < sizeY; y++) {
            for (int x = 0; x < sizeX; x++) {
                std::cout << " " << (bitboard.test(y * sizeX + x) ? 'K' : '.');
            }
            std::cout << "\n";
        }
    }
}

#endif