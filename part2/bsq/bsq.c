#include "bsq.h"

size_t ft_strlen(char * str)
{
    if (!str)
        return 0;
    size_t i = 0;
    while (str[i])
        i++;
    return i;
}

int strtoint(char * str, int n)
{
    char temp[n];
    for (int i = 0; i < n; i++)
        temp[i] = str[i];
    int num = 0;
    int mult = 1;
    for (int i = n - 1; i >= 0; i--, mult *= 10)
        num += (temp[i] - '0') * mult;
    return num;
}

char * strdupl(char * src)
{
    size_t len = ft_strlen(src);
    if (!len)
        return NULL;
    char * cpy = (char *)calloc(len + 1, sizeof(char));
    if (!cpy)
        return NULL;
    size_t i;
    for (i = 0; i < len; i++)
        cpy[i] = src[i];
    cpy[i] = '\0';
    return cpy;
}

bool check_map(int stage, t_map * map, t_len l, char * str)
{
    bool result = true;

    switch (stage)
    {
        case 0: // check if row num is present and has non numerics
            if (!l.len1)
                result = false;
            for (size_t i = 0; i < l.len1; i++)
            {
                if (!(str[i] >= '0' && str[i] <= '9'))
                    result = false;
            }
            break;
        case 1: // check first line on missing chars
            if (l.len2 < l.len1 + 7)
                result = false;
            break;
        case 2: // check if row num isnt 0
            if (!map->num_of_rows)
                result = false;
            break;
        case 3: // check for duplicates and non-printables
            if (map->empty == map->full || map->empty == map->obstacle || map->obstacle == map->full)
                result = false;
            else if (!(map->empty > 31 && map->empty < 127 && map->full > 31 && map->full < 127 && map->obstacle > 31 && map->obstacle < 127))
                result = false;
            break;
        case 4: // check if current row num > map-declared
            if (l.len1 >= (size_t)map->num_of_rows)
                result = false;
            break;
        case 5: // check line lengths
            if (l.len2 == 1)
                result = false;
            else if (!l.len1)
                result = true;
            else if (l.len2 != l.len1)
                result = false;
            break;
        case 6: // check if real row num == map-declared // check if last line ends with a line break
            if ((size_t)map->num_of_rows != l.len2 || map->map[map->num_of_rows - 1][l.len1 - 1] != '\n')
                result = false;
            break;
        case 7: // check all chars
            for (int i = 0; i < map->num_of_rows && result; i++)
            {
                for (int j = 0; map->map[i][j]; j++)
                {
                    char mch = map->map[i][j];
                    if (mch != map->empty && mch != map->obstacle && !((size_t)j == l.len1 - 1 && mch == '\n'))
                    {
                        result = false;
                        break;
                    }
                }
            }
            break;
    }

    if (!result)
        fprintf(stderr, "map error\n");
    return result;
}

bool parser(char * filename, t_map * map)
{
    // open file
    FILE * file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error: File couldn't be opened\n");
        return false;
    }

    // parse first line
    char *first_line = NULL;
    size_t len = 0;
    if (getline(&first_line, &len, file) == -1)
    {
        fprintf(stderr, "Error: File couldn't be read\n");
        fclose(file);
        return false;
    }
    // count how long is row num
    size_t flen = ft_strlen(first_line);
    size_t n = 0;
    while (first_line[n] && first_line[n] != ' ')
        n++;
    // check if row num is present and has non numerics // check first line on missing chars
    if (!check_map(0, map, (t_len){n, 0}, first_line) || !check_map(1, map, (t_len){n, flen}, 0))
    {
        free(first_line);
        fclose(file);
        return false;
    }
    // save first line values to struct
    map->fline = first_line;
    map->num_of_rows = strtoint(first_line, n);
    map->empty = first_line[n + 1];
    map->obstacle = first_line[n + 3];
    map->full = first_line[n + 5];
    // init other struct values
    map->sq_col = 0;
    map->sq_row = 0;
    map->sq_len = 0;

    // check if num of rows isn't 0
    if (!check_map(2, map, (t_len){0}, 0))
    {
        fclose(file);
        return false;
    }
    // check for duplicates and non-printables
    if (!check_map(3, map, (t_len){0}, 0))
    {
        fclose(file);
        return false;
    }

    // alloc mem for map
    map->map = (char **)calloc(map->num_of_rows, sizeof(char *));
    if (!map->map)
    {
        fprintf(stderr, "Error: Allocation error\n");
        fclose(file);
        return false;
    }

    // save map lines to struct
    char * buf = NULL;
    size_t prev_len = 0;
    int i;
    for (i = 0; getline(&buf, &len, file) != -1; i++)
    {
        char * line = strdupl(buf);
        size_t linelen = ft_strlen(line);
        // check if current row num > map-declared // check line lengths
        if (!check_map(4, map, (t_len){i, 0}, 0) || !check_map(5, map, (t_len){prev_len, linelen}, 0))
        {
            fclose(file);
            free(buf);
            free(line);
            return false;
        }
        map->map[i] = line;
        prev_len = linelen;
    }
    free(buf);

    // check if real row num == map-declared + last line ends with a line break // check all chars
    if (!check_map(6, map, (t_len){prev_len, i}, 0) || !check_map(7, map, (t_len){prev_len, 0}, 0))
    {
        fclose(file);
        return false;
    }

    // close file
    fclose(file);
    return true;
}

bool fillable(char field, char empty)
{
    if (field == empty)
        return true;
    return false;
}

bool check_down_row(int row, int col, int sq_len, t_map * map)
{
    if (row == map->num_of_rows)
        return false;
    for (int i = col; i < col + sq_len; i++)
    {
        if (!fillable(map->map[row][i], map->empty))
            return false;
    }
    return true;
}

void record_square(int row, int start_col, int sq_len, t_map * map)
{
    if (sq_len <= map->sq_len)
        return;
    map->sq_row = row;
    map->sq_col = start_col;
    map->sq_len = sq_len;
}

void find_squares(int row, int start_col, t_map * map)
{
    for (int i = start_col, sq_len = 1; map->map[row][i] != '\n'; i++, sq_len++)
    {
        if (!fillable(map->map[row][i], map->empty))
            return;
        for (int j = 1; j < sq_len; j++)
        {
            if (!check_down_row(row + j, start_col, sq_len, map))
                return;
        }
        record_square(row, start_col, sq_len, map);
    }
}

void cycle_each_cell(t_map * map)
{
    for (int i = 0; i < map->num_of_rows; i++)
    {
        for (int j = 0; map->map[i][j] != '\n'; j++)
            find_squares(i, j, map);
    }
}

bool cell_is_within_square(int row, int col, t_map map)
{
    if (row >= map.sq_row && row < map.sq_row + map.sq_len && col >= map.sq_col && col < map.sq_col + map.sq_len)
        return true;
    return false;
}

void print_solution(t_map map)
{
    for (int i = 0; i < map.num_of_rows; i++)
    {
        for (int j = 0; map.map[i][j]; j++)
        {
            char str[2] = {'\0', '\0'};
            if (cell_is_within_square(i, j, map))
                str[0] = map.full;
            else
                str[0] = map.map[i][j];
            fprintf(stdout, "%s", str);
        }
    }
}

void clear_mem(t_map * map)
{
    free(map->fline);
    for (int i = 0; i < map->num_of_rows && map->map; i++)
        free(map->map[i]);
    free(map->map);
}

void run_program(char *filename)
{
    t_map map = {0};
    if (parser(filename, &map))
    {
        cycle_each_cell(&map);
        print_solution(map);
    }
    clear_mem(&map);
}

int main(int argc, char * argv[])
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
            run_program(argv[i]);
    }
    else
    {
        char * filename = NULL;
        size_t size = 0;
        fprintf(stdout, "Input filename:\n");
        if (getline(&filename, &size, stdin) != -1)
        {
            filename[ft_strlen(filename) - 1] = '\0';
            run_program(filename);
            free(filename);
        }
        else
            fprintf(stderr, "Could not read from stdin\n");
    }
    return 0;
}
