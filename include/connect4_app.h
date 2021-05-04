//
// Created by tinre on 4/19/2021.
//
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "connect4_board.h"
//#include "Box2D/Box2D.h"

namespace connect4 {
    class Connect4App : public ci::app::App {
    public:
        Connect4App();

        /**
         * Draws the board and pieces
         */
        void draw() override;

        void update() override;

        /**
         * Handles keyboard input
         * @param event which key is pressed
         */
        void keyDown(ci::app::KeyEvent event) override;

        void drawBoard();

        void drawMenu() const;

        void initializeBoard();

        const int kWindowSizeX = 1920;
        const int kWindowSizeY = 1080;
        const int kMargin = 100;

    private:
        int current_col_;

        int length_ = 7;
        int height_ = 6;
        int win_length_ = 4;

        // 1 for standard game
        // 2 for wild game
        size_t game_type_;

        ci::Font large = ci::Font("arial", 70);
        ci::Font med = ci::Font("arial", 35);
        ci::Font small = ci::Font("arial", 18);

        bool showing_menu_;
        GameBoard board_;
    };
}


