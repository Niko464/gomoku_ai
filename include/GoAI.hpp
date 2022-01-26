/*
** EPITECH PROJECT, 2022
** B-AIA-500-TLS-5-1-gomoku-kevin.gouyet
** File description:
** GoAI
*/

#ifndef GoAI_HPP_
#define GoAI_HPP_

#include "Board.hpp"

class GoAI {
public:
    GoAI();
    ~GoAI();

    void startThinking(Board &currentBoard, int timeout);
protected:

};

#endif 