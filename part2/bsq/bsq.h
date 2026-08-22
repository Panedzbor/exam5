#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_map
{
    int num_of_rows;
    char empty;
    char obstacle;
    char full;
    char ** map;
} t_map;

#endif
