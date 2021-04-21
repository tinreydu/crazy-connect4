//
// Created by tinre on 4/20/2021.
//
#include "connect4_commandline.h"

using connect4::CommandLine;

int main() {
    CommandLine cl;
    while (true) {
        cl.Display();
        cl.Query();
    }
}
