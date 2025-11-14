#include <assert.h>
#include "board.h"


void test_board(void) 
{
    assert(is_black(-KING));
    assert(!is_black(KNIGHT));

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
    // TODO: cleanup formatting
    const piece START_BOARD[8][8] =
    {{   ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK},
     {   PAWN,PAWN,PAWN,PAWN,PAWN,PAWN,PAWN,PAWN},
     {  EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
     {  EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
     {  EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
     {  EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
     {  -PAWN,-PAWN,-PAWN,-PAWN,-PAWN,-PAWN,-PAWN,-PAWN},
     {  -ROOK,-KNIGHT,-BISHOP,-QUEEN,-KING,-BISHOP,-KNIGHT,-ROOK},
    };

    for (int r = 0; r < 1; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            piece p = global_pos.board[get_sq(r,c)];
            assert(p == START_BOARD[r][c]);
        }
    }

    assert(global_pos.black_to_move == false);
    // TODO: castling
    //assert(global_pos.ep_target == 0xFF);
    //assert(global_pos.halfmove == 0);
    //assert(global_pos.fullmove == 1);


    printf("Test board passed\n");
}
