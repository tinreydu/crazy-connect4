//
// Created by tinre on 4/19/2021.
//

#include "../include/connect4_app.h"

namespace connect4 {
    Connect4App::Connect4App() {
        ci::app::setWindowSize(kWindowSize, kWindowSize);
    }

    void Connect4App::draw() {
        ci::Color background_color("black");
        ci::gl::clear(background_color);

        board_.Display();
    }

    void Connect4App::update() {
        return;
    }
}
