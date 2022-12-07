#include <stdio.h>
#include <stdlib.h>
#include "../inc/init.h"

/**
 * get_map - Reads from a txt file containing the layout of a maze. If the
 * file does not exist or contains invalid format, a default map will be used.
 *
 * @maze: Struct containing a pointer to the layout of the maze.
 *
 * Return: 0 for SUCCESS if the maze's layout is retrieved. Otherwise 1 for
 * FAILURE.
 */
char get_map(map *maze)
{
	FILE *f;
	unsigned int i;
	unsigned int j;

	f = fopen("maze_layout.txt", "r");
	if (f == NULL)
	{
		fprintf(stderr, "Unable to read maze_layout.txt\n");
		return (get_default(maze));
	}
	if (scan_layout(f, maze) == FAILURE)
		return (get_default(maze));

	if (map_malloc(maze) != SUCCESS)
		return (FAILURE);
	for (i = 0; i < maze->height; i++)
	{
		for (j = 0; j < maze->width; j++)
		{
			if (fscanf(f, "%c", &(maze->layout[i][j])) != 1)
			{
				fprintf(stderr, "Missing block in maze_layout.txt\n");
				map_free(maze);
				fclose(f);
				return (get_default(maze));
			}
			if (maze->layout[i][j] == ' ' || maze->layout[i][j] == '\n')
				j--;
		}
	}
	fclose(f);

	return (SUCCESS);
}

/**
 * scan_layout - Scans from the file for width, height, starting x-position,
 * starting y-position of the maze.
 *
 * @f: Pointer to the filestream reading from maze_layout.txt.
 * @maze: Pointer to struct containing a pointer to the layout of the maze.
 *
 * Return: 0 for SUCCESS if the maze has valid width, height, starting
 * x-position, starting y-position. Otherwise 1 for FAILURE.
 */
char scan_layout(FILE *f, map *maze)
{
	if (fscanf(f, "%u %u", &(maze->height), &(maze->width)) != 2)
	{
		fprintf(stderr, "Missing maze height and/or width values.\n");
		fclose(f);
		return (FAILURE);
	}
	if ((int)maze->height < 1 || (int)maze->width < 1)
	{
		fprintf(stderr, "Invalid maze height and/or width values.\n");
		fclose(f);
		return (FAILURE);
	}
	if (fscanf(f, "%u %u", &(maze->start_x), &(maze->start_y)) != 2)
	{
		fprintf(stderr, "Missing maze starting x and/or starting y values.\n");
		fclose(f);
		return (FAILURE);
	}
	if ((int)maze->start_x < 1 || (int)maze->start_y < 1)
	{
		fprintf(stderr, "Invalid maze starting x and/or starting y values.\n");
		fclose(f);
		return (FAILURE);
	}

	return (SUCCESS);
}

/**
 * map_malloc - Allocates the necessary amount of memory for the 2D array.
 *
 * @maze: Pointer to struct containing a pointer to the layout of the maze.
 *
 * Return: 0 for SUCCESS if the right amount of memory could be allocated.
 * Otherwise 1 for FAILURE.
 */
char map_malloc(map *maze)
{
	unsigned int x;

	maze->layout = malloc(sizeof(char *) * maze->height);
	if (maze->layout == NULL)
	{
		fprintf(stderr, "Unable to allocate space for the maze.\n");
		return (FAILURE);
	}

	for (x = 0; x < maze->height; x++)
	{
		maze->layout[x] = malloc(sizeof(char) * maze->width);
		if (maze->layout[x] == NULL)
		{
			fprintf(stderr, "Unable to allocate space for the maze.\n");
			map_free(maze);
			return (FAILURE);
		}
	}

	return (SUCCESS);
}

/**
 * map_free - Frees up the memory allocated to the maze.
 *
 * @maze: Pointer to struct containing a pointer to the layout of the maze.
 */
void map_free(map *maze)
{
	unsigned int x;

	for (x = 0; x < maze->height; x++)
	{
		if (maze->layout[x] != NULL)
			free(maze->layout[x]);
	}
	if (maze->layout != NULL)
		free(maze->layout);
}
/**
 * get_default - Loads a default maze layout.
 *
 * @maze: Pointer to struct containing a pointer to the layout of the maze.
 *
 * Return: 0 for SUCCESS if the maze's layout is loaded. Otherwise 1 for
 * FAILURE.
 */
char get_default(map *maze)
{
	maze->height = MAZE_HEIGHT;
	maze->width = MAZE_WIDTH;
	maze->start_x = 4;
	maze->start_y = 7;
	printf("Getting default maze.\n");
	if (map_malloc(maze) != 0)
		return (FAILURE);

	memcpy(maze->layout[0], ((char[MAZE_WIDTH])
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}),
	sizeof(char) * MAZE_WIDTH);
	memcpy(maze->layout[1], ((char[MAZE_WIDTH])
	{'1', '1', '0', '0', '0', '0', '0', '0', '0', '1'}),
	sizeof(char) * MAZE_WIDTH);
	memcpy(maze->layout[2], ((char[MAZE_WIDTH])
	{'1', '0', '1', '0', '0', '0', '0', '0', '0', '1'}),
	sizeof(char) * MAZE_WIDTH);
	memcpy(maze->layout[3], ((char[MAZE_WIDTH])
	{'1', '0', '0', '1', '0', '0', '0', '0', '0', '1'}),
	sizeof(char) * MAZE_WIDTH);
	memcpy(maze->layout[4], ((char[MAZE_WIDTH])
	{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1'}),
	sizeof(char) * MAZE_WIDTH);
	memcpy(maze->layout[5], ((char[MAZE_WIDTH])
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'}),
	sizeof(char) * MAZE_WIDTH);
	memcpy(maze->layout[6], ((char[MAZE_WIDTH])
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '1'}),
	sizeof(char) * MAZE_WIDTH);
	memcpy(maze->layout[7], ((char[MAZE_WIDTH])
	{'1', '0', '0', '0', '0', '0', '0', '1', '0', '1'}),
	sizeof(char) * MAZE_WIDTH);
	memcpy(maze->layout[8], ((char[MAZE_WIDTH])
	{'1', '0', '0', '0', '0', '0', '0', '0', '1', '1'}),
	sizeof(char) * MAZE_WIDTH);
	memcpy(maze->layout[9], ((char[MAZE_WIDTH])
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}),
	sizeof(char) * MAZE_WIDTH);

	return (SUCCESS);
}
