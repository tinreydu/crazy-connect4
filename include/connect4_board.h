//
// Created by tinre on 4/19/2021.
//

#ifndef CONNECT_4_CONNECT4_BOARD_H
#define CONNECT_4_CONNECT4_BOARD_H

#include <cstddef>
#include <vector>

namespace connect4 {
    class GameBoard {
    public:
        GameBoard(size_t length, size_t height, size_t win_length);
        char CheckWinningToken();
        void DropPiece(size_t column);
        std::vector<std::vector<char>> GetBoard() const;

    private:
        size_t length_;
        size_t height_;
        size_t win_length_;
        std::vector<std::vector<char>> board_;
        const char kPlayerOneToken = 'x';
        const char kPlayerTwoToken = 'o';
        const char kEmptySpot = ' ';
    };
}

#endif //CONNECT_4_CONNECT4_BOARD_H
