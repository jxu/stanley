#include <assert.h>
#include "board.h"


void test_board(void) 
{
    assert(get_color(WKING) == WHITE);
    assert(get_color(BKNIGHT) == BLACK);

    assert(get_sq(1, 2) == 0x12);

    assert(is_sq(0x00));
    assert(is_sq(0x77));
    assert(!is_sq(0x80));
    assert(!is_sq(-1)); // casts to square

    assert(sq_col(0x54) == 4);
    assert(sq_row(0x54) == 5);

    assert(!is_coord_valid(""));
    assert(!is_coord_valid("a0"));
    assert(!is_coord_valid("i2"));
    assert(is_coord_valid("b2"));

    assert(sq_from_coord("a1") == 0x00);
    assert(sq_from_coord("h6") == 0x57);

    // Test FEN parsing
    position_from_fen(START_FEN);

    // Starting board, by increasing row
    PieceCode BOARD[8][8] =
    {{ WROOK, WKNIGHT, WBISHOP, WQUEEN, WKING, WBISHOP, WKNIGHT, WROOK},
     { [0 ... 7] = WPAWN },
     { [0 ... 7] = EMPTY },
     { [0 ... 7] = EMPTY },
     { [0 ... 7] = EMPTY },
     { [0 ... 7] = EMPTY },
     { [0 ... 7] = BPAWN },
     {BROOK,BKNIGHT,BBISHOP,BQUEEN,BKING,BBISHOP,BKNIGHT,BROOK},
    };

    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            PieceCode p = global_pos.board[get_sq(r,c)];
            assert(p == BOARD[r][c]);
        }
    }

    assert(global_pos.black_to_move == false);

    const uchar CASTLE_ALL = CASTLE_WK | CASTLE_WQ | CASTLE_BK | CASTLE_BQ;
    assert(global_pos.castle_flags == CASTLE_ALL);
    assert(global_pos.ep_target == NO_EP_TARGET);
    assert(global_pos.halfmove == 0);
    assert(global_pos.fullmove == 1);

    // Black to move position after 1. e4
    const char FEN1[] = 
        "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";
    
    position_from_fen(FEN1);
    
    BOARD[1][4] = EMPTY;
    BOARD[3][4] = WPAWN;

    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            assert(global_pos.board[get_sq(r,c)] == BOARD[r][c]);
        }
    }
    assert(global_pos.black_to_move == true);
    assert(global_pos.castle_flags == CASTLE_ALL);
    assert(global_pos.ep_target == sq_from_coord("e3"));
    assert(global_pos.halfmove == 0);
    assert(global_pos.fullmove == 1);

    printf("Test board passed\n");
}
