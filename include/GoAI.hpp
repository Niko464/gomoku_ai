/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** GoAI
*/

#ifndef GoAI_HPP_
#define GoAI_HPP_

#include "Board.hpp"
#include "TranspositionTable.hpp"
#include "BoardEvaluator.hpp"
#include <chrono>

class GoAI {
public:
    GoAI();
    ~GoAI();

    void startThinking(Board &currentBoard, int timeout);
    void makeFirstMove(Board &currentBoard, int timeout);
    int minimax(Board &board, int depth, int alpha, int beta, bool isMaximiser);
protected:
    TranspositionTable _transpositionTable;
    BoardEvaluator _evaluator;
private:
    std::chrono::system_clock::time_point _startingTime;
    bool _shouldStopSearching;
    int _timeoutTime;
    int _currentDepth;
    std::pair<int, int> globalBestMove;
    std::pair<int, int> currBestMove;

    int returnEvaluatedBoard(Board &board);
};

#endif 