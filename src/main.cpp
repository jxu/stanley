#include "common.hpp"
#include "board.hpp"

int main(void)
{
    Position p(START_FEN);
    printf("%d\n", p.board[0]);
    return 0;
}
