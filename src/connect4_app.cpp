//
// Created by tinre on 4/19/2021.
//

#include "../include/connect4_app.h"

namespace connect4 {
    Connect4App::Connect4App() {
        ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
        current_col_ = board_.GetLength() / 2;
    }

    void Connect4App::draw() {
        ci::Color background_color("white");
        ci::gl::clear(background_color);
        try {
            board_.DrawBoard();
        } catch (std::exception &e) {
            std::cout << e.what();
        }
    }

    void Connect4App::update() {
    }

    void Connect4App::keyDown(ci::app::KeyEvent event) {
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_RIGHT:
                current_col_++;
                break;

            case ci::app::KeyEvent::KEY_LEFT:
                current_col_--;
                break;

            case ci::app::KeyEvent::KEY_RETURN:
                try {
                    board_.DropPiece(current_col_, false);
                } catch (const std::exception &e) {
                    std::cout << e.what();
                }
        }
    }


}
