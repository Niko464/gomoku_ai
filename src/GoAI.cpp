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
    int min = 0;
    int max = 19;
    bool canPlace = false;
    int randY = -1;
    int randX = -1;

    while (!canPlace) {
        randY = min + (rand() % static_cast<int>(max - min + 1));
        randX = min + (rand() % static_cast<int>(max - min + 1));
        canPlace = currentBoard.canMakeMove(randY, randX);
    }
    currentBoard.makeMove(randY, randX, player_types::AI);
    std::cout << randX << "," << randY << std::endl;
}