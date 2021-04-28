//
// Created by tinre on 4/19/2021.
//
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "connect4_board.h"

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

        const int kWindowSizeX = 1920;
        const int kWindowSizeY = 1080;
        const int kMargin = 100;

    private:
        size_t current_col_;
        GameBoard board_ = GameBoard(7, 6, 4, true, 0, kWindowSizeX, 0, kWindowSizeY);
    };
}


