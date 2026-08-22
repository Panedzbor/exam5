#define ROWS 9
#define COLS 28

#include "bsq.h"

int main(int argc, char * argv[])
{
    char * filename;
    if (argc < 2)
        fscanf(stdin, "Input the filename: %s", filename);
    else
        filename = argv[1];
    t_map map;
    parser(filename, &map);
    
    for (int i = 0; i < ROWS; i++)
    {
        process_each_cell(i);   
    }
    return 0;
}

void parser(char * filename, t_map * map)
{
    FILE * file = fopen(filename, "r");
    if (!file)
        fprintf(stderr, "Error: File couldn't be opened\n");
    
    char *first_line = NULL;
    size_t len = 0;
    if (getline(&first_line, &len, file) == -1)
        fprintf(stderr, "Error: File couldn't be read\n");
    map->num_of_rows = first_line[0];
    map->empty = first_line[2];
    map->obstacle = first_line[4];
    map->full = first_line[6];
    free(first_line);

    map->map = (char **)calloc(map->num_of_rows, sizeof(char *));
    if (!map->map)
        fprintf(stderr, "Error: Allocation error\n");

    char * line = NULL;
    for (int i = 0; getline(&line, &len, file) != -1; i++)
        map->map[i] = line;

    fclose(file);
}

void process_each_cell(int row)
{
    for (int i = 0; map[row][i] != '\n'; i++)
    {
        find_squares(row, i);
    }
}

void find_squares(int row, int start_col)
{
    int len = 0;

    for (int i = start_col; map[row][i] != '\n'; i++)
    {
        if (!fillable(map[row][i]))
            break;
        len++;
        if (!check_down_rows(row + 1, start_col, len, 0))
            break;
        record_square(row, i, len);
    }
}

bool fillable(char field)
{
    if (field == EMPTY_CH)
        return true;
    return false;
}

bool check_down_rows(int row, int col, int len, int count)
{
    for (int i = col, j = 0; j < len; i++, j++)
    {
        if (row == ROWS || !fillable(map[row][i]))
            return false;
    }
    if (++count == len)
        return true;
    return check_down_rows(row + 1, col, len, count);
}