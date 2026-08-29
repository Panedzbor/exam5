#include "life.h"

size_t ft_strlen(char * str)
{
    size_t i = 0;
    while (str && str[i])
        i++;
    return i;
}

char * read_input()
{
    char buf = 0;
    char * input = malloc(1);
    if (!input)
        return NULL;
    input[0] = 0;
    char * temp = NULL;
    while (read(0, &buf, 1) > 0)
    {
        size_t len = ft_strlen(input);
        temp = (char *)realloc(input, len + 2);
        if (!temp)
        {
            free(input);
            return NULL;
        }
        temp[len] = buf;
        temp[++len] = '\0';
        input = temp;
    }
    return input;
}

bool prepare_board(game * g)
{
    // alloc board
    g->board = (char **)calloc(g->h, sizeof(char *));
    if (!g->board)
        return 0;
    // alloc rows
    size_t i;
    for (i = 0; i < g->h; i++)
    {
        g->board[i] = (char *)calloc(g->w + 2, sizeof(char));
        if (!g->board[i])
        {
            for (size_t y = 0; y < i; y++)
                free(g->board[y]);
            free(g->board);
            return 0;
        }
        // init chars
        size_t j;
        for (j = 0; j < g->w; j++)
            g->board[i][j] = ' ';
        g->board[i][j] = '\n';
        g->board[i][++j] = 0;
    }
    return 1;
}

bool draw_input(game * g, char * input)
{
    int col = 0, row = 0, p = 0;

    for (size_t i = 0; input[i]; i++)
    {
        switch (input[i])
        {
            case 'w':
                row -= 1;
                break;
            case 's':
                row += 1;
                break;
            case 'a':
                col -= 1;
                break;
            case 'd':
                col += 1;
                break;
            case 'x':
                p = (p == 0) ? 1 : 0;
                break;
            case '\n':
                break;
            default:
                return 0;
        }

        if (col >= 0 && (size_t)col < g->w && row >= 0 && (size_t)row < g->h && p)
            g->board[row][col] = 'O';
    }
    return 1;
}

void run_game(game * g, game ng)
{
    for (size_t i = 0; i < g->i; i++)
    {
        for (size_t j = 0; j < g->h; j++)
        {
            for (size_t k = 0; k < g->w; k++)
            {
                int count = 0;
                if (j - 1 < g->h && g->board[j - 1][k] == 'O')
                    count++;
                if (j - 1 < g->h && k + 1 < g->w && g->board[j - 1][k + 1] == 'O')
                    count++;
                if (k + 1 < g->w && g->board[j][k + 1] == 'O')
                    count++;
                if (j + 1 < g->h && k + 1 < g->w && g->board[j + 1][k + 1] == 'O')
                    count++;
                if (j + 1 < g->h && g->board[j + 1][k] == 'O')
                    count++;
                if (j + 1 < g->h && k - 1 < g->w && g->board[j + 1][k - 1] == 'O')
                    count++;
                if (k - 1 < g->w && g->board[j][k - 1] == 'O')
                    count++;
                if (j - 1 < g->h && k - 1 < g->w && g->board[j - 1][k - 1] == 'O')
                    count++;
                if (g->board[j][k] == 'O' && (count < 2 || count > 3))
                    ng.board[j][k] = ' ';
                else if (g->board[j][k] == ' ' && count == 3)
                    ng.board[j][k] = 'O';
            }
        }
        // copy new board to old board
        for (size_t j = 0; j < g->h; j++)
        {
            for (size_t k = 0; k < g->w; k++)
                g->board[j][k] = ng.board[j][k];
        }
    }
}

void print_result(game g)
{
    for (size_t i = 0; i < g.h; i++)
    {
        for (size_t j = 0; j < g.w + 1; j++)
            putchar(g.board[i][j]);
    }
}

void free_game(game g)
{
    for (size_t i = 0; i < g.h; i++)
        free(g.board[i]);
    free(g.board);
}

int main(int argc, char * argv[])
{
    // check argc
    if (argc != 4)
    {
        putchar('E'), putchar('\n');
        return 1;
    }
    
    // read stdinput
    char * input = read_input();
    if (!input)
    {    
        putchar('E'), putchar('\n'); 
        return 1;
    }

    // create game struct
    game g = {0};
    int w, h, i;
    w = atoi(argv[1]), h = atoi(argv[2]), i = atoi(argv[3]);
    if (w < 0 || h < 0 || i < 0)
    {
        free(input);
        putchar('E'), putchar('\n'); 
        return 1;
    }
    g.w = w;
    g.h = h;
    g.i = i;

    // alloc and init the borad
    bool result = prepare_board(&g);
    if (!result)
    {    
        free(input);
        putchar('E'), putchar('\n'); 
        return 1;
    }

    // prepare board initial state
    result = draw_input(&g, input);
    if (!result)
    {    
        free(input);
        free_game(g);
        putchar('E'), putchar('\n'); 
        return 1;
    }

    // create a board copy
    game ng = {0};
    ng.w = g.w;
    ng.h = g.h;
    ng.i = g.i;
    result = prepare_board(&ng);
    if (!result)
    {    
        free(input);
        free_game(g);
        putchar('E'), putchar('\n'); 
        return 1;
    }
    result = draw_input(&ng, input);
    if (!result)
    {    
        free(input);
        free_game(g);
        free_game(ng);
        putchar('E'), putchar('\n'); 
        return 1;
    }

    run_game(&g, ng);

    print_result(g);

    free(input);
    free_game(g);
    free_game(ng);

    return 0;
}