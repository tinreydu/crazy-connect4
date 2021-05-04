//
// Created by tinre on 4/19/2021.
//

#include "../include/connect4_app.h"

namespace connect4 {
    Connect4App::Connect4App() {
        ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
        current_col_ = board_.GetLength() / 2;
        showing_menu_ = true;
    }

    void Connect4App::draw() {
        if (!showing_menu_) {
            drawBoard();
        } else {
            ci::gl::clear();
            drawMenu();
        }
    }

    void Connect4App::update() {
    }

    void Connect4App::drawBoard() {
        ci::Color background_color("white");
        ci::gl::clear(background_color);
        try {
            board_.DrawBoard();
        } catch (std::exception &e) {
            std::cout << e.what();
        }
    }

    void Connect4App::drawMenu() const {
        ci::Color background_color("white");
        ci::gl::clear(background_color);

        ci::gl::drawStringCentered("Press 1 for a Standard Game", glm::vec2(kWindowSizeX / 2, kWindowSizeY / 4), ci::Color("black"));
        ci::gl::drawStringCentered("Press 2 for a Wild Game", glm::vec2(kWindowSizeX / 2, 3 * (kWindowSizeY / 8)), ci::Color("black"));
    }

    void Connect4App::keyDown(ci::app::KeyEvent event) {
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_RIGHT:
                if (current_col_ + 1 < board_.GetLength()) {
                current_col_++;
                }
                break;

            case ci::app::KeyEvent::KEY_LEFT:
                if (current_col_ - 1 >= 0) {
                    current_col_--;
                }
                break;

            case ci::app::KeyEvent::KEY_RETURN:
                try {
                    board_.DropPiece(current_col_, false);
                } catch (const std::exception &e) {
                    std::cout << "Error!" << std::endl;
                }
                break;

            case ci::app::KeyEvent::KEY_ESCAPE:
                if (!showing_menu_) {
                    showing_menu_ = true;
                }
                break;

            case ci::app::KeyEvent::KEY_1:
                if (showing_menu_) {
                    showing_menu_ = false;
                    game_type_ = 1;
                }
        }
    }


}
