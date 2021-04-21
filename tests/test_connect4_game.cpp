//
// Created by tinre on 4/19/2021.
//

#include <connect4_board.h>

#include <catch2/catch.hpp>

using connect4::GameBoard;

TEST_CASE("Constructor Tests") {
    SECTION("Normal Construction") {
        GameBoard test_board(7, 6, 4, true);
        REQUIRE(test_board.GetBoard().size() == 7);
        REQUIRE(test_board.GetBoard().at(5).size() == 6);
        REQUIRE(test_board.GetBoard().at(5).at(5) == ' ');
        REQUIRE(test_board.GetTokenCount() == 0);
    }

    SECTION("Win length longer than board size") {
        // code below derived from
        // https://github.com/catchorg/Catch2/blob/devel/docs/assertions.md
        REQUIRE_THROWS([&]() {
            GameBoard test_board(3, 3, 4, true);
        }());
    }
}

TEST_CASE("Dropping Piece Tests") {
    SECTION("Test player switches after dropping a piece") {
        GameBoard test_board(3, 3, 2, true);
        test_board.DropPiece(2);
        test_board.DropPiece(0);
        REQUIRE(test_board.GetBoard().at(2).at(0) == 'x');
        REQUIRE(test_board.GetBoard().at(0).at(0) == 'o');
        REQUIRE(test_board.IsPlayerOneTurn());
        REQUIRE(test_board.GetTokenCount() == 2);
    }

    SECTION("Test stacking pieces") {
        GameBoard test_board(3, 3, 2, true);
        test_board.DropPiece(2);
        test_board.DropPiece(2);
        REQUIRE(test_board.GetBoard().at(2).at(1) == 'o');
        REQUIRE(test_board.GetBoard().at(2).at(0) == 'x');
        REQUIRE(test_board.IsPlayerOneTurn());
        REQUIRE(test_board.GetTokenCount() == 2);
    }

    SECTION("Trying to put a piece out of bounds") {
        GameBoard test_board(3, 3, 2, true);
        REQUIRE_THROWS([&]() {
            test_board.DropPiece(3);
        }());
        REQUIRE(test_board.IsPlayerOneTurn());
        REQUIRE(test_board.GetTokenCount() == 0);
    }

    SECTION("Trying to put a piece to a negative column") {
        GameBoard test_board(3, 3, 2, true);
        REQUIRE_THROWS([&]() {
            test_board.DropPiece(-1);
        }());
        REQUIRE(test_board.IsPlayerOneTurn());
        REQUIRE(test_board.GetTokenCount() == 0);
    }

    SECTION("Trying to put a piece in a full column") {
        GameBoard test_board(3, 3, 2, true);
        test_board.DropPiece(2);
        test_board.DropPiece(2);
        test_board.DropPiece(2);
        REQUIRE_THROWS([&]() {
            test_board.DropPiece(2);
        }());
        REQUIRE_FALSE(test_board.IsPlayerOneTurn());
        REQUIRE(test_board.GetTokenCount() == 3);
    }
}

TEST_CASE("Horizontal Checker Test") {
    GameBoard test_board(4, 4, 3, true);
    test_board.DropPiece(0);
    test_board.DropPiece(0);
    test_board.DropPiece(1);
    test_board.DropPiece(1);
    test_board.DropPiece(2);
    SECTION("Horizontal win to the left") {
        REQUIRE(test_board.CheckHorizontalWin(2, 0, 'x'));
    }SECTION("Horizontal win in the middle") {
        REQUIRE(test_board.CheckHorizontalWin(1, 0, 'x'));
    }SECTION("Horizontal win to the right") {
        REQUIRE(test_board.CheckHorizontalWin(0, 0, 'x'));
    }
}

TEST_CASE("Vertical Checker Test") {
    GameBoard test_board(4, 4, 3, true);
    test_board.DropPiece(2);
    test_board.DropPiece(0);
    test_board.DropPiece(2);
    test_board.DropPiece(1);
    test_board.DropPiece(2);
    SECTION("Vertical win downwards") {
        REQUIRE(test_board.CheckVerticalWin(2, 2, 'x'));
    }SECTION("Vertical win in the middle") {
        REQUIRE(test_board.CheckVerticalWin(2, 1, 'x'));
    }SECTION("Vertical win upwards") {
        REQUIRE(test_board.CheckVerticalWin(2, 0, 'x'));
    }
}

TEST_CASE("Upward Diagonal Checker Test") {
    GameBoard test_board(4, 4, 3, true);
    test_board.DropPiece(0);
    test_board.DropPiece(1);
    test_board.DropPiece(1);
    test_board.DropPiece(2);
    test_board.DropPiece(3);
    test_board.DropPiece(2);
    test_board.DropPiece(3);
    test_board.DropPiece(3);
    test_board.DropPiece(2);

    test_board.DropPiece(0);
    test_board.DropPiece(0);
    test_board.DropPiece(1);
    test_board.DropPiece(0);
    test_board.DropPiece(2);

    /*
     * x| |o|
     * x|o|x|o
     * o|x|o|x
     * x|o|o|x
     */

    SECTION("Centered Upward Diagonal win up and to the right") {
        REQUIRE(test_board.CheckDiagonalWin(0, 0, 'x', 0));
    }SECTION("Centered Upward Diagonal in the middle") {
        REQUIRE(test_board.CheckDiagonalWin(1, 1, 'x', 0));
    }SECTION("Centered Upward Diagonal win down and to the left") {
        REQUIRE(test_board.CheckDiagonalWin(2, 2, 'x', 0));
    }

    SECTION("Offset down Upward Diagonal win up and to the right") {
        REQUIRE(test_board.CheckDiagonalWin(1, 0, 'o', 0));
    }SECTION("Offset down Upward Diagonal in the middle") {
        REQUIRE(test_board.CheckDiagonalWin(2, 1, 'o', 0));
    }SECTION("Offset down Upward Diagonal win down and to the left") {
        REQUIRE(test_board.CheckDiagonalWin(3, 2, 'o', 0));
    }

    SECTION("Offset up Upward Diagonal win up and to the right") {
        REQUIRE(test_board.CheckDiagonalWin(0, 1, 'o', 0));
    }SECTION("Offset up Upward Diagonal in the middle") {
        REQUIRE(test_board.CheckDiagonalWin(1, 2, 'o', 0));
    }SECTION("Offset up Upward Diagonal win down and to the left") {
        REQUIRE(test_board.CheckDiagonalWin(2, 3, 'o', 0));
    }

    SECTION("Edge Cases") {
        REQUIRE_FALSE(test_board.CheckDiagonalWin(3, 3, 'o', 0));
        REQUIRE_FALSE(test_board.CheckDiagonalWin(0, 3, 'x', 0));
        REQUIRE_FALSE(test_board.CheckDiagonalWin(3, 0, 'x', 0));
    }
}

TEST_CASE("Downward Diagonal Checker Test") {
    GameBoard test_board(4, 4, 3, true);
    test_board.DropPiece(3);
    test_board.DropPiece(2);
    test_board.DropPiece(2);
    test_board.DropPiece(1);
    test_board.DropPiece(0);
    test_board.DropPiece(1);
    test_board.DropPiece(1);
    test_board.DropPiece(3);
    test_board.DropPiece(0);
    test_board.DropPiece(2);
    test_board.DropPiece(3);
    test_board.DropPiece(0);
    test_board.DropPiece(3);
    test_board.DropPiece(1);

    /*
    *  |o| |x
    * o|x|o|x
    * x|o|x|o
    * x|o|o|x
    */

    SECTION("Centered Downward Diagonal win up and to the left") {
        REQUIRE(test_board.CheckDiagonalWin(3, 0, 'x', 1));
    }SECTION("Centered Downward Diagonal in the middle") {
        REQUIRE(test_board.CheckDiagonalWin(2, 1, 'x', 1));
    }SECTION("Centered Downward Diagonal win down and to the right") {
        REQUIRE(test_board.CheckDiagonalWin(1, 2, 'x', 1));
    }

    SECTION("Offset down Downward Diagonal win up and to the left") {
        REQUIRE(test_board.CheckDiagonalWin(2, 0, 'o', 1));
    }SECTION("Offset down Downward Diagonal in the middle") {
        REQUIRE(test_board.CheckDiagonalWin(1, 1, 'o', 1));
    }SECTION("Offset down Downward Diagonal win down and to the right") {
        REQUIRE(test_board.CheckDiagonalWin(0, 2, 'o', 1));
    }

    SECTION("Offset up Downward Diagonal win up and to the left") {
        REQUIRE(test_board.CheckDiagonalWin(3, 1, 'o', 1));
    }SECTION("Offset up Downward Diagonal in the middle") {
        REQUIRE(test_board.CheckDiagonalWin(2, 2, 'o', 1));
    }SECTION("Offset up Downward Diagonal win down and to the right") {
        REQUIRE(test_board.CheckDiagonalWin(1, 3, 'o', 1));
    }

    SECTION("Edge Cases") {
        REQUIRE_FALSE(test_board.CheckDiagonalWin(3, 3, 'x', 1));
        REQUIRE_FALSE(test_board.CheckDiagonalWin(0, 3, 'o', 1));
        REQUIRE_FALSE(test_board.CheckDiagonalWin(3, 0, 'o', 1));
    }
}


