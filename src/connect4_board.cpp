//
// Created by tinre on 4/19/2021.
//

#include <stdexcept>
#include <iostream>
#include "../include/connect4_board.h"

namespace connect4 {
    GameBoard::GameBoard(size_t length, size_t height, size_t win_length, bool player_one_turn) {
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
            player_one_turn_ = player_one_turn;
        } else {
            throw "Invalid board size!";
        }
    }

    std::vector<std::vector<char>> GameBoard::GetBoard() const{
        return board_;
    }

    void GameBoard::DropPiece(size_t column) {
        try {
            size_t y = 0;
            while (board_.at(column).at(y) != kEmptySpot) {
                y++;
            }
            if (player_one_turn_) {
                board_.at(column).at(y) = kPlayerOneToken;
            } else {
                board_.at(column).at(y) = kPlayerTwoToken;
            }
            player_one_turn_ = !player_one_turn_;
        } catch (const std::out_of_range& e) {
            throw "Out of range!";
        }
    }

    bool GameBoard::IsPlayerOneTurn() const {
        return player_one_turn_;
    }
}

