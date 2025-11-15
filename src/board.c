/* Piece and board definitions.

    0x88 board
    https://www.chessprogramming.org/0x88

    128-byte array stores the board. Half of the board are normal squares.
    the other half of the board is garbage, for boundary checking
    the (0-indexed) row and col are indexed in binary as 0rrr0fff
    Note that square a1 is 0x00

      a  b  c  d  e  f  g  h < file
    8 70 71 72 73 74 75 76 77|78 79 7A 7B 7C 7D 7E 7F
    7 60 61 62 63 64 65 66 67|68 69 6A 6B 6C 6D 6E 6F
    6 50 51 52 53 54 55 56 57|58 59 5A 5B 5C 5D 5E 5F
    5 40 41 42 43 44 45 46 47|48 49 4A 4B 4C 4D 4E 4F
    4 30 31 32 33 34 35 36 37|38 39 3A 3B 3C 3D 3E 3F
    3 20 21 22 23 24 25 26 27|28 29 2A 2B 2C 2D 2E 2F
    2 10 11 12 13 14 15 16 17|18 19 1A 1B 1C 1D 1E 1F
    1 00 01 02 03 04 05 06 07|08 09 0A 0B 0C 0D 0E 0F
    ^ rank

    A square is represented by an index into a 128 entry 0x88 board
    Uses an int instead of object for efficiency

    Square Coordinates are file-rank combo like h8

*/

#include "common.h"
#include "board.h"

// global position
Position global_pos;

void position_from_fen(const char* fen)
{   
    // clear board
    for (int i = 0; i < BOARD_SIZE; ++i)
        global_pos.board[i] = EMPTY;

    // read entire FEN as six fields 
    // https://www.chessprogramming.org/Forsyth-Edwards_Notation
    char place_buf[128];
    char side;
    char castling[5]; // at most "KQkq\0"
    char ep_target[3]; // at most "e3\0"
    int  halfmove;
    int  fullmove;

    // https://en.cppreference.com/w/c/io/fscanf.html
    // scanning %s into buffer always writes NUL
    int ret = sscanf(fen, "%s %c %s %s %d %d", 
            place_buf, &side, castling, ep_target, &halfmove, &fullmove);

    if (ret != 6)
    {
        ERROR("only read %d FEN fields\n", ret);
    }

    // piece placement reads place ranks 8 through 1
    char* s = place_buf;  // current char pointer
    for (int row = 7; row >= 0; --row)
    {
        int col = 0;

        while (col < 8)
        {
            // read character: digit or letter
            char c = *s++;

            // digit of empty squares to skip
            if ('1' <= c && c <= '8')
                col += c - '0';
            
            else // piece given by letter
            {
                piece p = EMPTY;
                bool black = islower(c);
                c = toupper(c);

                switch (c)
                {
                    case 'P': p = PAWN; break;
                    case 'N': p = KNIGHT; break;
                    case 'B': p = BISHOP; break;
                    case 'R': p = ROOK; break;
                    case 'Q': p = QUEEN; break;
                    case 'K': p = KING; break;
                        
                    default:
                        ERROR("unrecognized piece %c\n", c);
                }

                int ind = get_sq(row, col);

                // write piece to board, including color
                global_pos.board[ind] = black ? -p: p;

                ++col; // move to next square
            }
        }
        
        assert(col == 8);

        // expect / separator (if not first rank)
        if (row > 0)
        {
            assert(*s == '/');
            ++s;
        }
    }

    // read remaining info
    // side to move: w or b

    if (side == 'w')
        global_pos.black_to_move = false;
    else if (side == 'b')
        global_pos.black_to_move = true;
    else
        ERROR("bad side to move\n");

    // castling rights (default none)
    // - or letters in KQkq
    global_pos.castle_flags = 0;

    if (castling[0] != '-')
    {
        for (int i = 0; i < 4; ++i)
        {
            switch(castling[i])
            {
                case 'K': global_pos.castle_flags |= CASTLE_WK; break; 
                case 'Q': global_pos.castle_flags |= CASTLE_WQ; break;
                case 'k': global_pos.castle_flags |= CASTLE_BK; break;
                case 'q': global_pos.castle_flags |= CASTLE_BQ; break;
                default: ERROR("bad castling flag");
            }
        }
    }

    // ep target
    if (ep_target[0] == '-')
    {
        global_pos.ep_target = NO_EP_TARGET;
    } 
    else
    {
        global_pos.ep_target = sq_from_coord(ep_target);
        int row = sq_row(global_pos.ep_target);
        assert(row == 2 || row == 5); // only 3rd and 6th ranks
    }

    global_pos.halfmove = halfmove;
    global_pos.fullmove = fullmove;

}


