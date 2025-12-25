

#include "common.hpp"
#include "board.hpp"
#include <cstdio>
#include <sstream>
#include <exception>

Position::Position(const std::string& fen)
{  
    std::istringstream is(fen); // read like std::cin

    // read entire FEN as six fields 
    // https://www.chessprogramming.org/Forsyth-Edwards_Notation
    std::string place_buf;
    char side;
    std::string castling;
    std::string ep_target_str;

    is >> place_buf;
    // clear board
    board.fill(EMPTY);


    // piece placement reads place ranks 8 through 1
    int i = 0;
    for (int row = 7; row >= 0; --row)
    {
        int col = 0;

        while (col < 8)
        {
            // read character: digit or letter
            char c = place_buf[i++];

            // digit of empty squares to skip
            if ('1' <= c && c <= '8')
                col += c - '0';
            
            else // piece given by letter
            {
                PieceCode p = EMPTY;
                bool black = islower(c); // lowercase letter = black
                c = toupper(c); // consider uppercase for below

                switch (c)
                {
                    case 'P': p = WPAWN; break;
                    case 'N': p = WKNIGHT; break;
                    case 'B': p = WBISHOP; break;
                    case 'R': p = WROOK; break;
                    case 'Q': p = WQUEEN; break;
                    case 'K': p = WKING; break;
                        
                    default:
                        throw std::invalid_argument("unrecognized piece");
                }

                int ind = get_sq(row, col);

                // write piece to board, including color
                board[ind] = black ? PieceCode(p + BCODE): p;

                ++col; // move to next square
            }
        }
        
        assert(col == 8);

        // expect / separator (if not first rank)
        if (row > 0)
        {
            assert(place_buf[i] == '/');
            ++i;
        }
    }

    // read remaining info
    // side to move: w or b
    is >> side;

    if (side == 'w')
        black_to_move = false;
    else if (side == 'b')
        black_to_move = true;
    else
        throw std::domain_error("bad side to move\n");

    // castling rights (default none)
    // - or letters in KQkq
    is >> castling;
    castle_flags = 0;

    if (castling[0] != '-')
    {
        for (int i = 0; i < 4; ++i)
        {
            switch(castling[i])
            {
                case 'K': castle_flags |= CASTLE_WK; break; 
                case 'Q': castle_flags |= CASTLE_WQ; break;
                case 'k': castle_flags |= CASTLE_BK; break;
                case 'q': castle_flags |= CASTLE_BQ; break;
                default: throw std::domain_error("bad castling flag");
            }
        }
    }

    // ep target
    is >> ep_target_str;
    if (ep_target_str[0] == '-')
    {
        ep_target = NO_EP_TARGET;
    } 
    else
    {
        ep_target = sq_from_coord(ep_target_str);
        int row = sq_row(ep_target);
        assert(row == 2 || row == 5); // only 3rd and 6th ranks
    }

    is >> halfmove >> fullmove;
}

