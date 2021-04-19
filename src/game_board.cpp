//
// Created by tinre on 4/19/2021.
//

#include "../include/game_board.h"

namespace connect4 {
    GameBoard::GameBoard(size_t length, size_t height, size_t win_length) {
        length_ = length;
        height_ = height;
        win_length_ = win_length;
        for (size_t x = 0; x < length; x++) {
            for (size_t y = 0; y < height; y++) {
                
            }
        }

    }
}

