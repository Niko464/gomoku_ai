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

//TODO: remove
//#define __DEBUG__

GoAI::GoAI() : _transpositionTable(time(NULL))
{
    this->_resetStats();
}

GoAI::~GoAI() {}

void GoAI::makeFirstMove(Board &currentBoard, int timeoutTime)
{
    currentBoard.makeMove(8, 8, player_types::AI);
    std::cout << "9,9" << std::endl;
}

void GoAI::_resetStats()
{
    this->_stats.alphaBetaCuts = 0;
    this->_stats.endNodes = 0;
    this->_stats.totalNodes = 0;
    this->_stats.transpositionsCreated = 0;
    this->_stats.transpositionsUsed = 0;
    this->_stats.transpositionsUsefull = 0;
}

void GoAI::printStats()
{
    std::cout << "MESSAGE TotalNodes: " << this->_stats.totalNodes << std::endl;
    std::cout << "MESSAGE EndNodes: " << this->_stats.endNodes << std::endl;
    std::cout << "MESSAGE Alpha Beta Cuts: " << this->_stats.alphaBetaCuts << " (this is not the amount of branches cut)" << std::endl;
    std::cout << "MESSAGE transpositions Used: " << this->_stats.transpositionsUsed << std::endl;
    std::cout << "MESSAGE transpositions Added: " << this->_stats.transpositionsCreated << std::endl;
    std::cout << "MESSAGE transpositions Usefull: " << this->_stats.transpositionsUsefull << " (should be the same as used)" << std::endl;
}

void GoAI::startThinking(Board &currentBoard, int timeoutTime, bool debug, int maxDepth)
{
    this->globalBestMove = {-1, -1};
    this->currBestMove = {-1, -1};
    this->_startingTime = std::chrono::system_clock::now();
    this->_shouldStopSearching = false;
    this->_timeoutTime = timeoutTime;

    this->_resetStats();
    for (int depth = 1; depth <= maxDepth; depth++) {
        this->_currentDepth = depth;
        this->minimax(currentBoard, depth, INT_MIN, INT_MAX, true, debug);
        if (this->_shouldStopSearching)
            break;
        globalBestMove = currBestMove;
        if (debug) {
            std::cout << "MESSAGE Finished calculating depth " << depth << ". I will move: x:" << globalBestMove.x << " y:" << globalBestMove.y << std::endl; 
            this->printStats();
        }
    }
    std::cout << globalBestMove.x + 1 << "," << globalBestMove.y + 1 << std::endl;
    currentBoard.makeMove(globalBestMove.y, globalBestMove.x, player_types::AI);
}

//TODO: transposition table
int GoAI::minimax(Board &board, int depth, int alpha, int beta, bool isMaximiser, bool debug)
{
    auto endingTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = endingTime - this->_startingTime;
    std::vector<Vec2> moves;
    const int boardHash = this->_transpositionTable.computeHash(board);

    if (elapsed.count() * 1000 >= this->_timeoutTime - 200) {
        this->_shouldStopSearching = true;
        #ifdef __DEBUG__
        if (debug)
            std::cout << "MESSAGE returning here 5 alpha: " << alpha << " " << beta << std::endl;
        #endif
        return (isMaximiser ? INT_MIN : INT_MAX);
    }
    /*if (this->_transpositionTable.knowsHash(boardHash)) {
        TranspositionValue &storedInfo = this->_transpositionTable.getStoredValue(boardHash);
        if (storedInfo.depth >= depth) {
            
        }
    }*/
    this->_stats.totalNodes += 1;
    if (isMaximiser && this->_evaluator.didPlayerWin(board, player_types::PLAYER)) {
        #ifdef __DEBUG__
        if (debug)
            std::cout << "MESSAGE returning here" << std::endl;
        #endif
        this->_stats.endNodes += 1;
        return -1000000000 - (this->_currentDepth - depth);
    }
    if (!isMaximiser && this->_evaluator.didPlayerWin(board, player_types::AI)) {
        #ifdef __DEBUG__
        if (debug)
            std::cout << "MESSAGE returning here 2" << std::endl;
        #endif
        this->_stats.endNodes += 1;
        return 1000000000 - (this->_currentDepth - depth);
    }
    if (depth == 0) {
        int to_return = this->_evaluator.evaluateBoard(board);
        //std::cout << "returning here 3 " << to_return << std::endl;
        this->_stats.endNodes += 1;
        return to_return;
    }
    moves = board.getValidMoves(3);
    if (moves.size() == 0) {
        #ifdef __DEBUG__
        if (debug)
            std::cout << "MESSAGE returning here 4" << std::endl;
        #endif
        this->_stats.endNodes += 1;
        return this->_evaluator.evaluateBoard(board);
    }
    if (this->_currentDepth == depth) {
        #ifdef __DEBUG__
        if (debug)
            std::cout << "MESSAGE sorting moves according to this move: " << this->globalBestMove.y << " " << this->globalBestMove.x << std::endl;
        #endif
        moves = this->sortMoves(moves, this->globalBestMove);
    }
    #ifdef __DEBUG__
    if (debug) {
        std::cout << "MESSAGE \nMESSAGE \nMESSAGE \nMESSAGE " << std::endl;
        std::cout << "MESSAGE Checking positions for the following board :       maximiser: " << isMaximiser << " depth: " << this->_currentDepth - depth + 1 << std::endl;
        board.printToOutput();
        std::cout << "MESSAGE \nMESSAGE \nMESSAGE \nMESSAGE " << std::endl;
    }
    #endif
    if (isMaximiser) {
        for (Vec2 &move : moves) {
            board.makeMove(move.y, move.x, player_types::AI);
            #ifdef __DEBUG__
            if (debug)
                std::cout << "MESSAGE ai move y:" << move.y << " " << move.x << std::endl;
            #endif
            int evaluation = this->minimax(board, depth - 1, alpha, beta, false, debug);
            board.unmakeMove(move.y, move.x, player_types::AI);
            if (evaluation > alpha) {
                alpha = evaluation;
                #ifdef __DEBUG__
                if (debug) {
                    std::cout << "MESSAGE alpha: " << alpha << " beta: " << beta << " move: y:" << move.y << " " << move.x << std::endl;
                    board.makeMove(move.y, move.x, player_types::AI);
                    board.printToOutput();
                    board.unmakeMove(move.y, move.x, player_types::AI);
                    std::cout << "MESSAGE end alpha" << std::endl;
                }
                #endif
                if (depth == this->_currentDepth) {
                    #ifdef __DEBUG__
                    if (debug) {
                        std::cout << "MESSAGE updating currBestMove to y" << move.y << " x" << move.x << " " << evaluation << std::endl;
                        board.makeMove(move.y, move.x, player_types::AI);
                        board.printToOutput();
                        board.unmakeMove(move.y, move.x, player_types::AI);
                        std::cout << "MESSAGE end update currBestMove" << std::endl;
                    }
                    #endif
                    this->currBestMove = move;
                }
            }
            if (this->_shouldStopSearching)
                break;
            //prune the next branches
            if (alpha >= beta) {
                #ifdef __DEBUG__
                if (debug)
                    std::cout << "MESSAGE alpha cut" << std::endl;
                #endif
                this->_stats.alphaBetaCuts += 1;
                break;
            }
        }
        return alpha;
    }
    for (Vec2 &move : moves) {
        board.makeMove(move.y, move.x, player_types::PLAYER);
        #ifdef __DEBUG__
        if (debug)
            std::cout << "MESSAGE player move y:" << move.y << " " << move.x << std::endl;
        #endif
        int evaluation = this->minimax(board, depth - 1, alpha, beta, true, debug);
        board.unmakeMove(move.y, move.x, player_types::PLAYER);
        beta = std::min(evaluation, beta);
        if (this->_shouldStopSearching)
            break;
        if (alpha >= beta) {
            #ifdef __DEBUG__
            if (debug)
                std::cout << "MESSAGE beta cut" << std::endl;
            #endif
            this->_stats.alphaBetaCuts += 1;
            break;
        }
    }
    return beta;
}

/*int GoAI::negamax(Board &board, int depth, int alpha, int beta, bool isMaximiser, bool debug)
{
    int originalAlpha = alpha;
    const int boardHash = this->_transpositionTable.computeHash(board);

    if (this->_transpositionTable.knowsHash(boardHash) && this->_transpositionTable.getStoredValue(boardHash).depth >= depth) {
        TranspositionValue &storedInfo = this->_transpositionTable.getStoredValue(boardHash);
    
        this->_stats.transpositionsUsed += 1;
        if (storedInfo.type == EXACT) {
            this->_stats.transpositionsUsefull += 1;
            return storedInfo.value;
        } else if (storedInfo.type == LOWER) {
            this->_stats.transpositionsUsefull += 1;
            alpha = std::max(alpha, storedInfo.value);
        } else if (storedInfo.type == UPPER) {
            this->_stats.transpositionsUsefull += 1;
            beta = std::min(beta, storedInfo.value);
        }
        if (alpha >= beta) {
            return storedInfo.
        }
    }
}*/

//TODO: finis the sortMoves func
std::vector<Vec2> &GoAI::sortMoves(std::vector<Vec2> &moves, Vec2 &bestMove)
{
    return moves;
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