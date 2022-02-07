/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** GoAi
*/

#include "GoAI.hpp"
#include <iostream>
#include <thread>
//#include <bits/stdc++.h>
#include <algorithm>
#include "Utils.hpp"
#include <climits>

GoAI::GoAI() : _transpositionTable(time(NULL))
{

}

GoAI::~GoAI() {}

void GoAI::makeFirstMove(Board &currentBoard, int timeoutTime)
{
    currentBoard.makeMove(9, 9, player_types::AI);
    std::cout << "9,9" << std::endl;
}

void GoAI::startThinking(Board &currentBoard, int timeoutTime, bool debug)
{
    this->globalBestMove = {-1, -1};
    this->currBestMove = {-1, -1};
    this->_startingTime = std::chrono::system_clock::now();
    this->_shouldStopSearching = false;
    this->_timeoutTime = timeoutTime;
    //Iterative Deepening infinite loop
    //TODO: make the "2" "400"
    for (int depth = 1; depth <= 2; depth++) {
        this->_currentDepth = depth;
        this->minimax(currentBoard, depth, INT_MIN, INT_MAX, true, debug);
        if (this->_shouldStopSearching)
            break;
        globalBestMove = currBestMove;
        if (debug)
            std::cout << "MESSAGE Finished calculating depth " << depth << ". I will move: x:" << globalBestMove.x << " y:" << globalBestMove.y << std::endl; 
    }
    if (debug)
        std::cout << "MESSAGE my time is up, I am moving y" << globalBestMove.y << ",x" << globalBestMove.x << std::endl;
    std::cout << globalBestMove.y << "," << globalBestMove.x << std::endl;
    currentBoard.makeMove(globalBestMove.y, globalBestMove.x, player_types::AI);
}

//TODO: transposition table
int GoAI::minimax(Board &board, int depth, int alpha, int beta, bool isMaximiser, bool debug)
{
    auto endingTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = endingTime - this->_startingTime;
    std::vector<Vec2> moves;
    const int boardHash = this->_transpositionTable.computeHash(board);

    if (elapsed.count() * 1000 >= this->_timeoutTime - 100) {
        this->_shouldStopSearching = true;
        return (isMaximiser ? alpha : beta);
    }
    if (this->_transpositionTable.knowsHash(boardHash)) {
        TranspositionValue &storedInfo = this->_transpositionTable.getStoredValue(boardHash);
        if (storedInfo.depth >= depth) {
            
        }
    }
    if (isMaximiser && this->_evaluator.didPlayerWin(board, player_types::PLAYER)) {
        return -100000000 - (this->_currentDepth - depth);
    }
    if (!isMaximiser && this->_evaluator.didPlayerWin(board, player_types::AI)) {
        return 100000000 - (this->_currentDepth - depth);
    }
    if (depth == 0)
        return this->_evaluator.evaluateBoard(board);
    moves = board.getValidMoves(3);
    if (moves.size() == 0)
        return this->_evaluator.evaluateBoard(board);
    
    if (isMaximiser) {
        //we're trying to maximize this
        for (Vec2 &move : moves) {
            board.makeMove(move.y, move.x, player_types::AI);
            int evaluation = this->minimax(board, depth - 1, alpha, beta, false, debug);
            board.unmakeMove(move.y, move.x, player_types::AI);
            if (evaluation > alpha) {
                alpha = evaluation;
                if (depth == this->_currentDepth) {
                    if (debug)
                        std::cout << "MESSAGE updating currBestMove to y" << move.y << " x" << move.x << " " << evaluation << std::endl;
                    this->currBestMove = move;
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
        board.makeMove(move.y, move.x, player_types::PLAYER);
        int evaluation = this->minimax(board, depth - 1, alpha, beta, true, debug);
        board.unmakeMove(move.y, move.x, player_types::PLAYER);
        beta = std::min(evaluation, beta);
        if (alpha >= beta)
            break;
    }
    return beta;
}

/*int GoAI::returnEvaluatedBoard(Board &board, bool debug)
{
    int score = 0;
    const int boardHash = this->_transpositionTable.computeHash(board);

    if (debug) {
        std::cout << "MESSAGE [" << this->_currentDepth << "] Do i know the hash " << boardHash << "?" << std::endl;
        board.printToOutput();
    }
    if (this->_transpositionTable.knowsHash(boardHash)) {
        if (debug)
            std::cout << "MESSAGE I know this board Hash ! " << boardHash << std::endl;
        return this->_transpositionTable.getStoredValue(boardHash);
    }
    score = this->_evaluator.evaluateBoard(board);
    //board.printToOutput();
    //std::cout << "MESSAGE score for the last printed board: " << score << std::endl; 
    this->_transpositionTable.storeHash(boardHash, score);
    if (debug)
        std::cout << "MESSAGE storing hash " << boardHash << std::endl;
    return score;
}*/