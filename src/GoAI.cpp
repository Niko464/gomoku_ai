/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** GoAi
*/

#include "GoAI.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <bits/stdc++.h>

GoAI::GoAI() : _transpositionTable(time(NULL))
{

}

GoAI::~GoAI() {}

void GoAI::startThinking(Board &currentBoard, int timeoutTime)
{
    /*int min = 0;
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
    std::cout << randX << "," << randY << std::endl;*/

    auto startingTime = std::chrono::system_clock::now();
    std::pair<int, int> currBestMove(-1, -1);
    int recordScore = INT_MIN;
    auto currentPossibleMoves = currentBoard.getValidMoves();
    int timePerIterativeSearch = ((timeoutTime - 1000) / currentPossibleMoves.size());

    for (auto &move : currentPossibleMoves) {
        int currScore = INT_MIN;

        currentBoard.makeMove(move.first, move.second, player_types::AI);
        currScore = this->startDeepeningSearch(currentBoard, timePerIterativeSearch);
        currentBoard.unmakeMove(move.first, move.second, player_types::AI);

        //TODO if doesn't work, WIN_SCORE might be too low
        if (currScore >= WIN_SCORE) {
            std::cout << move.second << "," << move.first << std::endl;
            return;
        }
        if (currScore > recordScore) {
            recordScore = currScore;
            currBestMove = move;
        }
    }

    std::cout << currBestMove.second << "," << currBestMove.first << std::endl;
}

int GoAI::startDeepeningSearch(Board &board, int timeForSearch)
{

}