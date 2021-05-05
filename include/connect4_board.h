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
        /**
         * Creates a Connect 4 game board of size length by height and custom win length. Also allows players to decide what turn it is
         * @param length of board
         * @param height of board
         * @param win_length required tokens in a row to win
         * @param player_one_turn is it player one's turn?
         */
        GameBoard(int length, int height, int win_length, bool player_one_turn);

        /**
         * Creates a Connect 4 game board to be displayed. Same as above, but with window bounds
         * @param length of board
         * @param height of board
         * @param win_length required tokens in a row to win
         * @param player_one_turn is it player one's turn?
         * @param min_x
         * @param max_x
         * @param min_y
         * @param max_y
         * @param game_type 1 for standard, 2 for wild
         */
        GameBoard(int length, int height, int win_length, bool player_one_turn, int min_x, int max_x, int min_y,
                  int max_y, int game_type);

        /**
         * Creates a connect 4 game of size 7 x 6 with win length of 4
         */
        GameBoard();

        /**
         * Finds which token has won at given location
         * @param column horizontal coordinate
         * @param row vertical coordinate
         * @return if player 1 or 2 won. If neither, returns the empty space
         */
        char CheckWinningToken(int column, int row) const;

        /**
         * Check if there is a horizontal win at a given location
         * @param column x coordinate
         * @param row y coordinate
         * @param token which token is being checked for a win
         * @return if there is a win
         */
        bool CheckHorizontalWin(int column, int row, char token) const;

        /**
         * Check if there is a vertical win at a given location
         * @param column x coordinate
         * @param row y coordinate
         * @param token which token is being checked for a win
         * @return if there is a win
         */
        bool CheckVerticalWin(int column, int row, char token) const;

        /**
         * Check if there is a diagonal win in either direction at a given location
         * @param column x coordinate
         * @param row y coordinate
         * @param token which token is being checked for a win
         * @param direction 0 = downwards diagonal, 1 = upward diagonal
         * @return if there is a win
         */
        bool CheckDiagonalWin(int column, int row, char token, size_t direction) const;

        /**
         * Drops a piece at a certain column. Per connect 4 rules, the piece will fall to the lowest open spot in the column
         * If overridden, ignores if someone has already won
         * @param column
         * @param override if override on or off
         */
        void DropPiece(int column, bool override);

        /**
         * Returns the board
         * @return
         */
        std::vector<std::vector<char>> GetBoard() const;

        /**
         * Checks if it is player one's turn
         * @return
         */
        bool IsPlayerOneTurn() const;

        /**
         * Gets the number of tokens played
         * @return
         */
        size_t GetTokenCount() const;

        /**
         * Gets which token has won, if any
         * @return
         */
        char GetWinner() const;

        /**
         * Helper method that returns length of board
         * @return
         */
        int GetLength() const;

        /**
        * Helper method that returns height of board
        * @return
        */
        int GetHeight() const;

        /**
        * Helper method that returns win length of board
        * @return
        */
        int GetWinLength() const;

        /**
         * Draws the board and pieces
         */
        void DrawBoard() const;

        void Clear();

        int GetXSpace() const;

        int GetYSpace() const;

        void SwapColumns(int col1, int col2);

        void DeleteColumn(int col);

        int GetPlayer1TurnsUntilPowerup();

        int GetPlayer2TurnsUntilPowerup();


    private:
        bool player_one_turn_;
        int length_;
        int height_;
        int win_length_;
        int token_count_;

        int game_type_;
        int player1_turns_until_powerup_;
        int player2_turns_until_powerup_;

        std::vector<std::vector<char>> board_;

        char winning_token_;

        char kPlayerOneToken = 'x';
        char kPlayerTwoToken = 'o';
        char kEmptySpot = ' ';

        int kRechargeTime = 6;

        int min_x_;
        int min_y_;
        int max_x_;
        int max_y_;

        int radius_;
        int x_space_;
        int y_space_;
    };
}

#endif //CONNECT_4_CONNECT4_BOARD_H
