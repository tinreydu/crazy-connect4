//
// Created by tinre on 4/19/2021.
//

#include "../include/connect4_board.h"

namespace connect4 {
    GameBoard::GameBoard(size_t length, size_t height, size_t win_length) {
        if (win_length <= length || win_length <= height) {
            length_ = length;
            height_ = height;
            win_length_ = win_length;
            std::vector<char> column;
            for (size_t x = 0; x < length; x++) {
                for (size_t y = 0; y < height; y++) {
                    column.push_back(' ');
                }
                board_.push_back(column);
                column.clear();
            }
        } else {
            throw "Invalid board size!";
        }
    }

    std::vector<std::vector<char>> GameBoard::GetBoard() const{
        return board_;
    }
}

