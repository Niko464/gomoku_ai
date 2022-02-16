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
#include "Vec2.hpp"
#include <chrono>

struct ai_stats {
    int transpositionsUsed;
    int transpositionsCreated;
    int transpositionsUsefull;
    int endNodes;
    int alphaBetaCuts;
    int totalNodes;
};

class GoAI {
public:
    GoAI();
    ~GoAI();

    void startThinking(Board &currentBoard, int timeout, bool debug, int maxDepth = 400);
    void makeFirstMove(Board &currentBoard, int timeout);
    int minimax(Board &board, int depth, int alpha, int beta, bool isMaximiser, bool debug);
    int negamax(Board &board, int depth, int alpha, int beta, bool isMaximiser, bool debug);
    std::vector<Vec2> &sortMoves(std::vector<Vec2> &moves, Vec2 &bestMove);
    void printStats();

protected:
    TranspositionTable _transpositionTable;
    BoardEvaluator _evaluator;
private:
    std::chrono::system_clock::time_point _startingTime;
    bool _shouldStopSearching;
    int _timeoutTime;
    int _currentDepth;
    ai_stats _stats;
    Vec2 globalBestMove;
    Vec2 currBestMove;

    Vec2 getRandomValidMove(Board &currentBoard);
    void _resetStats();
};

#endif 