/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** GoAi
*/

#include "GoAI.hpp"
#include <iostream>
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
    this->globalBestMove = {-1, -1};
    this->currBestMove = {-1, -1};
    this->_startingTime = std::chrono::system_clock::now();
    this->_shouldStopSearching = false;
    this->_timeoutTime = timeoutTime;
    //Iterative Deepening infinite loop
    for (int depth = 0; ; depth++) {
        if (depth > 0) {
            globalBestMove = currBestMove;
            std::cout << "MESSAGE depth " << depth << " done. I will move: x:" << globalBestMove.second << " y:" << globalBestMove.first << std::endl; 
        }
        this->_currentDepth = depth;
        this->minimax(currentBoard, depth, INT_MIN, INT_MAX, true);
        if (this->_shouldStopSearching)
            break;
    }
    std::cout << "MESSAGE my time is up, I am moving " << globalBestMove.second << "," << globalBestMove.first << std::endl;
    std::cout << globalBestMove.second << "," << globalBestMove.first << std::endl;
}

//TODO: use the transposition table
//TODO: clear the transposition table from time to time
int GoAI::minimax(Board &board, int depth, int alpha, int beta, bool isMaximiser)
{
    auto endingTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = endingTime - this->_startingTime;
    std::vector<std::pair<int, int>> moves;

    if (elapsed.count() * 1000 >= this->_timeoutTime - 500) {
        this->_shouldStopSearching = true;
        return (isMaximiser ? alpha : beta);
    }
    if (depth == 0)
        return this->returnEvaluatedBoard(board);
    if (isMaximiser && this->_evaluator.didPlayerWin(board, player_types::AI))
        return 10000000 - (this->_currentDepth - depth);
    if (!isMaximiser && this->_evaluator.didPlayerWin(board, player_types::PLAYER))
        return -10000000 - (this->_currentDepth - depth);
    moves = board.getValidMoves();
    if (moves.size() == 0)
        return this->returnEvaluatedBoard(board);
    if (isMaximiser) {
        //we're trying to maximize this
        for (auto &move : moves) {
            board.makeMove(move.first, move.second, player_types::AI);
            int evaluation = this->minimax(board, depth - 1, alpha, beta, false);
            board.unmakeMove(move.first, move.second, player_types::AI);
            if (evaluation > alpha) {
                alpha = evaluation;
                if (depth == this->_currentDepth) {
                    this->currBestMove = {move.first, move.second};
                }
            }
            //prune the next branches
            if (alpha >= beta)
                break;
        }
        return alpha;
    }
    // trying to minimize this
    for (auto &move : moves) {
        board.makeMove(move.first, move.second, player_types::PLAYER);
        int evaluation = this->minimax(board, depth - 1, alpha, beta, true);
        board.unmakeMove(move.first, move.second, player_types::PLAYER);
        beta = std::min(evaluation, beta);
        if (alpha >= beta)
            break;
    }
    return beta;
}

int GoAI::returnEvaluatedBoard(Board &board)
{
    int score = 0;
    const int boardHash = this->_transpositionTable.computeHash(board);

    if (this->_transpositionTable.knowsHash(boardHash)) {
        std::cout << "MESSAGE " << "I know this board Hash ! " << boardHash << std::endl;
        return this->_transpositionTable.getStoredValue(boardHash).score;
    }
    score = this->_evaluator.evaluateBoard(board);
    this->_transpositionTable.storeHash(boardHash, (TranspositionValue) {score});
    return score;
}