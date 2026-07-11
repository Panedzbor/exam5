#define ROWS 9
#define COLS 28

#include "bsq.h"

void line_algo(int start)
{
    for (int i = start; i < COLS; i++)
    {
        fill_itself();
        line_algo(start + 1);
    }
}

void row_algo(int start)
{
    for (int i = start; i < ROWS; i++)
    {
        line_algo(0);
    }
}
