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
    }

    SECTION("Test stacking pieces") {
        GameBoard test_board(3, 3, 2, true);
        test_board.DropPiece(2);
        test_board.DropPiece(2);
        REQUIRE(test_board.GetBoard().at(2).at(1) == 'o');
        REQUIRE(test_board.GetBoard().at(2).at(0) == 'x');
        REQUIRE(test_board.IsPlayerOneTurn());
    }

    SECTION("Trying to put a piece out of bounds") {
        GameBoard test_board(3, 3, 2, true);
        REQUIRE_THROWS([&]() {
            test_board.DropPiece(3);
        }());
        REQUIRE(test_board.IsPlayerOneTurn());
    }

    SECTION("Trying to put a piece to a negative column") {
        GameBoard test_board(3, 3, 2, true);
        REQUIRE_THROWS([&]() {
            test_board.DropPiece(-1);
        }());
        REQUIRE(test_board.IsPlayerOneTurn());
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
    }
}

