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
        int end = s.find(del);
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