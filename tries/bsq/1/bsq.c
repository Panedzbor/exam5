#include "bsq.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_map
{
	char * fline;
	char ** map;
	int rownum;
	char empty;
	char full;
	char obstacle;
	int srow;
	int scol;
	int slen;
} t_map;

size_t ft_strlen(char * str)
{
	if (!str)
		return 0;
	int i = 0; // size_t
	while (str[i])
		i++;
	return i;
}

int lefttoint(char * str, int n)
{
	char temp[n];
	for (int i = 0; i < n; i++)
		temp[i] = str[i];
	int result = 0;
	for (int i = n - 1, mult = 1; i >= 0; i--, mult *= 10)
		result += (temp[i] - '0') * mult;
	return result;
}

char * strdupl(char * str)
{
	char * dupl = (char *)calloc(ft_strlen(str)+1,1);
	int i;
	for (i = 0; str[i]; i++)
		dupl[i] = str[i];
	dupl[i] = 0;
	return dupl;
}

void clear_mem(t_map * map)
{
	free(map->fline);
	if (map->map) // !
	{
		for (int i = 0; i < map->rownum; i++)
			free(map->map[i]);
	}
	free(map->map);
}

bool parser(char * filename, t_map * map)
{
	//open file
	FILE * file = fopen(filename, "r");
	
	//parse first line
	//read
	char * fline = NULL;
	size_t size = 0;
	getline(&fline, &size, file);
	map->fline = fline;
	//count rownum len
	int n = 0;
	while (fline[n] && fline[n] != ' ')
		n++;
	//check rownum if present and if numeric
	if (!n)
	{
		fprintf(stderr, "map error\n");
		fclose(file);
		return false;
	}
	for (int i = 0; i < n; i++)
	{
		if (!(fline[i] >= '0' && fline[i] <= '9'))
		{
			fprintf(stderr, "map error\n");
			fclose(file);
			return false;
		}
	}
	//check first line if long enough
	size_t flen = ft_strlen(fline);
	if (flen < (size_t)n + 7)
	{
		fprintf(stderr, "map error\n");
		fclose(file);
		return false;
	}
	//save first line
	map->rownum = lefttoint(fline, n);
	map->empty = fline[n+1];
	map->obstacle = fline[n+3];
	map->full = fline[n+5];
	//init struct rest
	map->srow = 0;
	map->scol = 0;
	map->slen = 0;
	//check if row num is not 0
	if (map->rownum == 0)
	{
		fprintf(stderr, "map error\n");
		fclose(file);
		return false;
	}
	//check first line for duplicates and non-printables
	if ((map->empty == map->obstacle || map->empty == map->full || map->full == map->obstacle) || 
	    !(map->empty > 31 && map->empty < 127 && map->obstacle > 31 && map->obstacle < 127 && map->full > 31 && map->full < 127))
	{
		fprintf(stderr, "map error\n");
		fclose(file);
		return false;
	}
	
	//parse rest
	//alloc map
	map->map = (char **)calloc(map->rownum, sizeof(char*));
	//read lines
	char * buf = 0;
	size_t prev_len = 0;
	size_t len = 0;
	for(n = 0; getline(&buf, &size, file) != -1; n++)
	{
		//check line num < rownum
		if (n == map->rownum)
		{
			fprintf(stderr, "map error\n");
			free(buf);
			fclose(file);
			return false;
		}
		//check line len == prev && isn't 1
		len = ft_strlen(buf);
		if (!(!prev_len || prev_len == len) || len == 1) // reject only newlines
		{
			fprintf(stderr, "map error\n");
			free(buf);
			fclose(file);
			return false;
		}
		//dupl line
		//save line
		map->map[n] = strdupl(buf);
		prev_len = len;
	}
	free(buf);
	
	//close file
	fclose(file);
	
	//check total read num = rownum + last line ends with \n
	if (n != map->rownum || map->map[map->rownum-1][len-1] != '\n')
	{
		fprintf(stderr, "map error\n");
		return false;
	}
	//check all chars are valid
	for (int i = 0; i < map->rownum; i++)
	{
		for (int j = 0; map->map[i][j]; j++)
		{
			if (!(map->map[i][j] == map->empty || map->map[i][j] == map->obstacle || ((size_t)j == len-1 && map->map[i][j] == '\n')))
			{
				fprintf(stderr, "map error\n");
				return false;
			}
		}
	}	
	return true;
}

bool check_down_row(int row, int col, int sqlen, t_map * map)
{
	//printf("checking down row %d %d\n", row, col);
	if (row == map->rownum)
		return false;
	for (int i = col; i < col + sqlen; i++)
	{
		if (map->map[row][i] == map->obstacle)
			return false;
	//	printf("row %d col %d OK\n", row, i);
	}
	return true;
}

void record_map(int row, int col, int sqlen, t_map * map)
{
	//printf("recording square %d %d %d\n", row, col, sqlen);
	if (sqlen <= map->slen)
		return;
	map->srow = row;
	map->scol = col;
	map->slen = sqlen;
}

void find_squares(int row, int col, t_map * map)
{
	//printf("find square for cell %d %d\n", row, col);
	//cycle each cell on the row starting at col until end
	for (int i = col, sqlen = 1; map->map[row][i] != '\n'; i++, sqlen++)
	{
		//printf("checking cells %d-%d\n", col, i);
		if (map->map[row][i] == map->obstacle)
			return;
	//	printf("cells ok\n");
		for (int j = 1; j < sqlen; j++)
		{
			if (!check_down_row(row + j, col, sqlen, map))
				return;
		}
		record_map(row, col, sqlen, map);
	}
	//check if cur cell is empty
	//increment sqlen each cycle starting at 1
	//for each cycle check down rows starting from row + 1 until row + sqlen
	//record
}

void find_solution(t_map * map)
{
	//cycle each cell
	//find squares
	for (int i = 0; i < map->rownum; i++)
	{
		for (int j = 0; map->map[i][j] != '\n'; j++)
			find_squares(i, j, map);
	}
}

void print_solution(t_map * map)
{
	for (int i = 0; i < map->rownum; i++)
	{
		for (int j = 0; map->map[i][j]; j++)
		{
			if ((i >= map->srow && i < map->srow + map->slen) && (j >= map->scol && j < map->scol + map->slen))
				fprintf(stdout, "%c", map->full);
			else
				fprintf(stdout, "%c", map->map[i][j]);
		}
	}
}

void run_program(char * filename)
{
	t_map map = {0};
	if(parser(filename, &map))
	{
		find_solution(&map);
		print_solution(&map);
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
		getline(&filename, &size, stdin);
		filename[ft_strlen(filename)-1] = '\0';
		run_program(filename);
		free(filename);
	}
	return 0;
}
