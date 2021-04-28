//
// Created by tinre on 4/19/2021.
//

#include <stdexcept>
#include <iostream>
#include <cinder/Color.h>
#include <connect4_app.h>
#include "../include/connect4_board.h"

namespace connect4 {
    GameBoard::GameBoard(size_t length, size_t height, size_t win_length, bool player_one_turn) {
        if (win_length <= length || win_length <= height) {
            length_ = length;
            height_ = height;
            win_length_ = win_length;
            token_count_ = 0;
            winning_token_ = ' ';
            player_one_turn_ = player_one_turn;

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

    GameBoard::GameBoard(size_t length, size_t height, size_t win_length, bool player_one_turn, int min_x, int max_x,
                         int min_y, int max_y) {
        if (win_length <= length || win_length <= height) {
            length_ = length;
            height_ = height;
            win_length_ = win_length;
            token_count_ = 0;
            winning_token_ = ' ';
            player_one_turn_ = player_one_turn;

            std::vector<char> column;
            for (size_t x = 0; x < length; x++) {
                for (size_t y = 0; y < height; y++) {
                    column.push_back(' ');
                }
                board_.push_back(column);
                column.clear();
            }
            min_x_ = min_x;
            max_x_ = max_x;
            min_y_ = min_y;
            max_y_ = max_y;

            x_space_ = (max_x_ / 2) / length_;
            y_space_ = (max_y_ / 2) / height_;

            if (x_space_ < y_space_) {
                radius_ = (0.9 * x_space_) / 2;
            } else {
                radius_ = (0.9 * y_space_) / 2;
            }
        } else {
            throw "Invalid board size!";
        }

    }

    GameBoard::GameBoard() {
        length_ = 7;
        height_ = 6;
        win_length_ = 4;
        token_count_ = 0;
        winning_token_ = ' ';
        player_one_turn_ = true;

        std::vector<char> column;
        for (size_t x = 0; x < length_; x++) {
            for (size_t y = 0; y < height_; y++) {
                column.push_back(' ');
            }
            board_.push_back(column);
            column.clear();
        }
    }


    std::vector<std::vector<char>> GameBoard::GetBoard() const {
        return board_;
    }

    void GameBoard::DropPiece(size_t column, bool override) {
        if (winning_token_ == kEmptySpot) {
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
                token_count_++;

                // The minimum amount of tokens on the board to win is 2 * win length - 1
                // We don't start checking until after the minimum amount of tokens has been reached
                if (!override) {
                    if (token_count_ >= (2 * win_length_) - 1) {
                        winning_token_ = CheckWinningToken(column, y);
                    }
                }
            } catch (const std::out_of_range &e) {
                throw "Out of range!";
            }
        } else {
            std::cout << "Someone has already won!" << std::endl;
        }
    }

    bool GameBoard::IsPlayerOneTurn() const {
        return player_one_turn_;
    }

    size_t GameBoard::GetTokenCount() const {
        return token_count_;
    }

    char GameBoard::CheckWinningToken(size_t column, size_t row) const {
        if (CheckHorizontalWin(column, row, kPlayerOneToken) || CheckVerticalWin(column, row, kPlayerOneToken) ||
            CheckDiagonalWin(column, row, kPlayerOneToken, 0) || CheckDiagonalWin(column, row, kPlayerOneToken, 1)) {
            return kPlayerOneToken;
        } else if (CheckHorizontalWin(column, row, kPlayerTwoToken) || CheckVerticalWin(column, row, kPlayerTwoToken) ||
                   CheckDiagonalWin(column, row, kPlayerTwoToken, 0) ||
                   CheckDiagonalWin(column, row, kPlayerTwoToken, 1)) {
            return kPlayerTwoToken;
        } else {
            return kEmptySpot;
        }
    }

    bool GameBoard::CheckHorizontalWin(size_t column, size_t row, char token) const {
        size_t token_in_row = 0;
        for (size_t x = 0; x < length_; x++) {
            if (board_.at(x).at(row) == token) {
                token_in_row++;
                if (token_in_row == win_length_) {
                    return true;
                }
            } else {
                token_in_row = 0;
            }
        }
        return false;
    }

    bool GameBoard::CheckVerticalWin(size_t column, size_t row, char token) const {
        size_t token_in_row = 0;
        for (size_t y = 0; y < height_; y++) {
            if (board_.at(column).at(y) == token) {
                token_in_row++;
                if (token_in_row == win_length_) {
                    return true;
                }
            } else {
                token_in_row = 0;
            }
        }
        return false;
    }

    bool GameBoard::CheckDiagonalWin(size_t column, size_t row, char token, size_t direction) const {
        size_t token_in_row = 0;
        if (direction == 0) {
            while (column != 0 && row != 0) {
                column--;
                row--;
            }
            for (int i = 0; row + i < height_ && column + i < length_; i++) {
                if (board_.at(column + i).at(row + i) == token) {
                    token_in_row++;
                    if (token_in_row == win_length_) {
                        return true;
                    }
                } else {
                    token_in_row = 0;
                }
            }
        } else {
            while (column != 0 && row < height_ - 1) {
                column--;
                row++;
            }
            for (int i = 0; row - i >= 0 && column + i < length_; i++) {
                if (board_.at(column + i).at(row - i) == token) {
                    token_in_row++;
                    if (token_in_row == win_length_) {
                        return true;
                    }
                } else {
                    token_in_row = 0;
                }
            }
        }
        return false;
    }

    char GameBoard::GetWinner() const {
        return winning_token_;
    }

    size_t GameBoard::GetWinLength() const {
        return win_length_;
    }

    size_t GameBoard::GetLength() const {
        return length_;
    }

    size_t GameBoard::GetHeight() const {
        return height_;
    }

    void GameBoard::DrawBoard() const{
        ci::gl::color(ci::Color("blue"));
        // The Board will consist of the middle half of the screen. The sides are 1/4 of the window size each.
        ci::gl::drawSolidRect(ci::Rectf(glm::vec2(max_x_ / 4,max_y_ / 4), glm::vec2((3 * max_x_) / 4, (3 * max_y_) / 4)));

        int xCoord = (max_x_ / 4) + (x_space_ / 2);
        int yCoord = (max_y_ / 4) + (y_space_ / 2);
        for (size_t x = 0; x < length_; x++) {
            for (size_t y = 0; y < height_; y++) {
                ci::gl::color(ci::Color("black"));
                ci::gl::drawSolidCircle(glm::vec2(xCoord, yCoord), radius_);
                yCoord += y_space_;
            }
            yCoord = (max_y_ / 4) + (y_space_ / 2);
            xCoord += x_space_;
        }
    }
}

