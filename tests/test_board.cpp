#include "doctest.h"
#include "board.hpp"

TEST_CASE("board")
{
    CHECK(get_color(WKING) == WHITE);
    CHECK(get_color(BKNIGHT) == BLACK);

    CHECK(get_sq(1, 2) == 0x12);

    CHECK(get_type(WKING) == KING);
    CHECK(get_type(BKNIGHT) == KNIGHT);

    CHECK(is_sq(0x00));
    CHECK(is_sq(0x77));
    CHECK(!is_sq(0x80));
    CHECK(!is_sq(-1)); // casts to square

    CHECK(sq_col(0x54) == 4);
    CHECK(sq_row(0x54) == 5);

    CHECK(!is_coord_valid(""));
    CHECK(!is_coord_valid("a0"));
    CHECK(!is_coord_valid("i2"));
    CHECK(is_coord_valid("b2"));

    CHECK(sq_from_coord("a1") == 0x00);
    CHECK(sq_from_coord("h6") == 0x57);

    CHECK(write_sq(0x34) == "e4");
}

TEST_CASE("FEN parsing")
{
    Position P(START_FEN);

    // Starting board, by increasing row
    std::array<PieceCode, 8> EMPTY_ROW;
    EMPTY_ROW.fill(EMPTY);
    std::array<std::array<PieceCode, 8>, 8> BOARD = {
    {{ WROOK, WKNIGHT, WBISHOP, WQUEEN, WKING, WBISHOP, WKNIGHT, WROOK},
     { WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, },
     EMPTY_ROW,
     EMPTY_ROW,
     EMPTY_ROW,
     EMPTY_ROW,
     { BPAWN, BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,},
     {BROOK,BKNIGHT,BBISHOP,BQUEEN,BKING,BBISHOP,BKNIGHT,BROOK},
    }};

    std::array<std::array<PieceCode, 8>, 8> test_board;

    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            test_board[r][c] = P.board[get_sq(r,c)];
        }
    }
    CHECK(test_board == BOARD);

    CHECK(P.black_to_move == false);

    const auto CASTLE_ALL = CASTLE_WK | CASTLE_WQ | CASTLE_BK | CASTLE_BQ;
    CHECK(P.castle_flags == CASTLE_ALL);
    CHECK(P.ep_target == NO_EP_TARGET);
    CHECK(P.halfmove == 0);
    CHECK(P.fullmove == 1);

    // Black to move position after 1. e4
    const char FEN1[] = 
        "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";
    
    P = Position(FEN1);
    
    BOARD[1][4] = EMPTY;
    BOARD[3][4] = WPAWN;

    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            test_board[r][c] = P.board[get_sq(r,c)];
        }
    }

    CHECK(test_board == BOARD);
    CHECK(P.black_to_move == true);
    CHECK(P.castle_flags == CASTLE_ALL);
    CHECK(P.ep_target == sq_from_coord("e3"));
    CHECK(P.halfmove == 0);
    CHECK(P.fullmove == 1);
}
