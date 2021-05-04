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

        const int kWindowSizeX = 1920;
        const int kWindowSizeY = 1080;
        const int kMargin = 100;

    private:
        int current_col_;

        // 1 for standard game
        // 2 for wild game
        size_t game_type_;
        bool showing_menu_;
        GameBoard board_ = GameBoard(7, 6, 4, true, 0, kWindowSizeX, 0, kWindowSizeY);
    };
}


