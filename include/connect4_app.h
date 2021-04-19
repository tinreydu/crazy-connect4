//
// Created by tinre on 4/19/2021.
//
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace connect4 {
class Connect4App : public ci::app::App {
public:
    Connect4App();

    void draw() override;
    void update() override;

    const int kWindowSize = 875;
    const int kMargin = 100;

    };
}

