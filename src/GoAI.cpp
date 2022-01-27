/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** GoAi
*/

#include "GoAI.hpp"
#include <iostream>

GoAI::GoAI() {}

GoAI::~GoAI() {}

void GoAI::startThinking(Board &currentBoard, int timeoutTime)
{
    std::cout << "1,1" << std::endl;
    int min = 0;
    int max = 19;
    int randY = min + (rand() % static_cast<int>(max - min + 1));
    int randX = min + (rand() % static_cast<int>(max - min + 1));

    std::cout << randX << "," << randY << std::endl;
}