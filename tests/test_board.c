#include "board.h"
#include "unity.h"

void test_board(void) 
{
    TEST_ASSERT(is_black(-KING));
    TEST_ASSERT(!is_black(KNIGHT));

    TEST_ASSERT(get_sq(1, 2) == 0x12);

    TEST_ASSERT(is_sq(0x00));
    TEST_ASSERT(is_sq(0x77));
    TEST_ASSERT(!is_sq(0x80));
    TEST_ASSERT(!is_sq(-1)); // casts to square

    TEST_ASSERT(sq_col(0x54) == 4);
    TEST_ASSERT(sq_row(0x54) == 5);

    TEST_ASSERT(!is_coord_valid(""));
    TEST_ASSERT(!is_coord_valid("a0"));
    TEST_ASSERT(!is_coord_valid("i2"));
    TEST_ASSERT(is_coord_valid("b2"));

    TEST_ASSERT(sq_from_coord("a1") == 0x00);
    TEST_ASSERT(sq_from_coord("h6") == 0x57);

    // Test FEN parsing
    position_from_fen(START_FEN);

    // Starting board, by increasing row
    piece BOARD[8][8] =
    {{ ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK},
     { [0 ... 7] = PAWN },
     { [0 ... 7] = EMPTY },
     { [0 ... 7] = EMPTY },
     { [0 ... 7] = EMPTY },
     { [0 ... 7] = EMPTY },
     { [0 ... 7] = -PAWN },
     {-ROOK,-KNIGHT,-BISHOP,-QUEEN,-KING,-BISHOP,-KNIGHT,-ROOK},
    };

    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            piece p = global_pos.board[get_sq(r,c)];
            TEST_ASSERT(p == BOARD[r][c]);
        }
    }

    TEST_ASSERT(global_pos.black_to_move == false);

    const uchar CASTLE_ALL = CASTLE_WK | CASTLE_WQ | CASTLE_BK | CASTLE_BQ;
    TEST_ASSERT(global_pos.castle_flags == CASTLE_ALL);
    TEST_ASSERT(global_pos.ep_target == NO_EP_TARGET);
    TEST_ASSERT(global_pos.halfmove == 0);
    TEST_ASSERT(global_pos.fullmove == 1);

    // Black to move position after 1. e4
    const char FEN1[] = 
        "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";
    
    position_from_fen(FEN1);
    
    BOARD[1][4] = EMPTY;
    BOARD[3][4] = PAWN;

    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            TEST_ASSERT(global_pos.board[get_sq(r,c)] == BOARD[r][c]);
        }
    }
    TEST_ASSERT(global_pos.black_to_move == true);
    TEST_ASSERT(global_pos.castle_flags == CASTLE_ALL);
    TEST_ASSERT(global_pos.ep_target == sq_from_coord("e3"));
    TEST_ASSERT(global_pos.halfmove == 0);
    TEST_ASSERT(global_pos.fullmove == 1);

    printf("Test board passed\n");
}
