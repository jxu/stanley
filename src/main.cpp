#include "common.hpp"
#include "board.hpp"

int main(void)
{
    position_from_fen(START_FEN);
    printf("%d\n", global_pos.board[0]);
    return 0;
}
