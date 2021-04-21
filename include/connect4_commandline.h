//
// Created by tinre on 4/20/2021.
//

#ifndef CONNECT_4_CONNECT4_COMMANDLINE_H
#define CONNECT_4_CONNECT4_COMMANDLINE_H

#include "connect4_board.h"

namespace connect4 {
    class CommandLine {
    public:
        void Display() const;
        void Query();
    private:
        GameBoard board = GameBoard(7, 6, 4, true);
    };
}


#endif //CONNECT_4_CONNECT4_COMMANDLINE_H
