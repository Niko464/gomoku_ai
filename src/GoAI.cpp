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
#include <algorithm>

GoAI::GoAI() : _transpositionTable(time(NULL))
{

}

GoAI::~GoAI() {}

/*int recordScore = INT_MIN;
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
}*/

void GoAI::startThinking(Board &currentBoard, int timeoutTime)
{
    std::pair<int, int> globalBestMove(-1, -1);
    std::pair<int, int> currBestMove(-1, -1);

    this->_startingTime = std::chrono::system_clock::now();
    this->_shouldStopSearching = false;
    this->_timeoutTime = timeoutTime;
    //Iterative Deepening infinite loop
    for (int depth = 0; ; depth++) {
        if (depth > 0) {
            globalBestMove = currBestMove;
            std::cout << "MESSAGE depth " << depth << " done. I will move: x:" << globalBestMove.second << " y:" << globalBestMove.first << std::endl; 
        }
        this->minimax(currentBoard, depth, INT_MIN, INT_MAX, true);
        if (this->_shouldStopSearching)
            break;
    }
    std::cout << globalBestMove.second << "," << globalBestMove.first << std::endl;
}

int GoAI::minimax(Board &board, int depth, int alpha, int beta, bool isMaximiser)
{
    auto endingTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = endingTime - this->_startingTime;
    int score = -1;
    std::vector<std::pair<int, int>> moves;

    if (elapsed.count() * 1000 >= this->_timeoutTime - 500) {
        this->_shouldStopSearching = true;
        return alpha;
    }
    
    score = this->_evaluator.evaluateBoard(board);
    if (depth == 0 || score >= WIN_SCORE || score <= -WIN_SCORE)
        return score;
    moves = board.getValidMoves();
    if (moves.size() == 0)
        return score;
    if (isMaximiser) {
        //we're trying to maximize this
        int bestEvaluation = INT_MIN;
        for (auto &move : moves) {
            board.makeMove(move.first, move.second, player_types::AI);
            int evaluation = this->minimax(board, depth - 1, alpha, beta, false);
            board.unmakeMove(move.first, move.second, player_types::AI);
            bestEvaluation = std::max(evaluation, bestEvaluation);
            alpha = std::max(evaluation, alpha);
            //prune the next branches
            if (alpha >= beta)
                break;
        }
        return bestEvaluation;
    }
    // trying to minimize this
    int bestEvaluation = INT_MAX;
    for (auto &move : moves) {
        board.makeMove(move.first, move.second, player_types::PLAYER);
        int evaluation = this->minimax(board, depth - 1, alpha, beta, true);
        board.unmakeMove(move.first, move.second, player_types::PLAYER);
        bestEvaluation = std::min(evaluation, bestEvaluation);
        beta = std::min(evaluation, beta);
        if (alpha >= beta)
            break;
    }
    return bestEvaluation;
}