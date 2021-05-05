//
// Created by tinre on 4/19/2021.
//
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "connect4_board.h"

#include "cinder/audio/Voice.h"
#include "cinder/audio/Source.h"

namespace connect4 {
    class Connect4App : public ci::app::App {
    public:
        Connect4App();

        /**
         * Draws the board and pieces
         */
        void draw() override;

        void setup() override;

        /**
         * Handles keyboard input
         * @param event which key is pressed
         */
        void keyDown(ci::app::KeyEvent event) override;

        /**
         * Draws the playing board after the menu
         */
        void drawBoard();

        /**
         * Draws the menu with instructions
         */
        void drawMenu() const;

        /**
         * Creates a connect 4 board with the user selected dimensions
         */
        void initializeBoard();


        const int kWindowSizeX = 1920;
        const int kWindowSizeY = 1080;

        // cinder::audio::VoiceRef mVoice;

    private:
        int current_col_;
        int player1_next_powerup_;
        int player2_next_powerup_;

        bool player1_using_swap_;
        bool player1_using_delete_;
        bool player1_using_blocker_;

        bool player2_using_swap_;
        bool player2_using_delete_;
        bool player2_using_blocker_;

        int swap_col_1;

        int length_ = 7;
        int height_ = 6;
        int win_length_ = 4;

        // 1 for standard game
        // 2 for wild game
        // 3 for timed game
        size_t game_type_;

        char kPlayerOneToken = 'x';
        char kPlayerTwoToken = 'o';
        char kEmptySpot = ' ';

        int player1_timer_;
        int player2_timer_;
        bool timer_started_;

        ci::Font large = ci::Font("arial", 70);
        ci::Font med = ci::Font("arial", 35);
        ci::Font small = ci::Font("arial", 18);

        bool showing_menu_;

        GameBoard board_;
    };
}


