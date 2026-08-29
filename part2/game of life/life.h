#ifndef LIFE_H
#define LIFE_H

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_game
{
    size_t h;
    size_t w;
    size_t i;
    char ** board;
} game;

#endif