#include "common.h"
#include "board.h"

int main(void)
{
    position_from_fen(START_FEN);
    printf("%d\n", global_pos.board[0]);
    return 0;
}
