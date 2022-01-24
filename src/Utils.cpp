/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** Utils
*/

#include "Utils.hpp"

#include <iostream>
std::vector<std::string> Utils::splitStr(std::string s, std::string del)
{
    std::cout << "splitStr > " << s << std::endl;
    std::vector<std::string> to_return;

    int start = 0;
    int end = s.find(del);
    int count = 0;
    std::cout << "end: " << end << std::endl;
    while (end != std::string::npos) {
        std::cout << end << std::endl;
        std::cout << s.substr(start, end - start) << std::endl;
        start = end + del.size();
        end = s.find(del, start);
        std::cout << "end " << end << " start " << start << " find " << s.find(del, start) << std::endl;
        count++;
        if (count == 5)
            break;
    }
    std::cout << s.substr(start, end - start);

    std::cout << "&" << std::endl;
    return to_return;
}