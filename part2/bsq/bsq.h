#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_map
{
    int num_of_rows;
    char empty;
    char obstacle;
    char full;
    char * fline;
    char ** map;
    int sq_row;
    int sq_col;
    int sq_len;
} t_map;

typedef struct s_len
{
    size_t prev_len;
    size_t len;
} t_len;

#endif
