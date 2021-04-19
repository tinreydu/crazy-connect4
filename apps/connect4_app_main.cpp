//
// Created by tinre on 4/19/2021.
//

#include "connect4_app.h"

using connect4::Connect4App;

void prepareSettings(Connect4App::Settings* settings) {
    settings->setResizable(false);
}

CINDER_APP(Connect4App, ci::app::RendererGl, prepareSettings)
