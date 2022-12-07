#include "../inc/maze.h"

/**
 * render_mini - Renders a minimap on the top right of the screen.
 *
 * @instance: Struct containing the SDL2 renderer and window.
 * @maze: Struct containing a pointer to the layout of the maze.
 * @status: Struct containing variables on camera position.
 */
void render_mini(SDL_Instance instance, map maze, player status)
{
	SDL_Rect rect;

	rect.x = WINDOW_WIDTH - 210;
	rect.y = 0;
	rect.w = 210;
	rect.h = 210;
	SDL_SetRenderDrawColor(instance.renderer, 0, 128, 0, 0);
	SDL_RenderFillRect(instance.renderer, &rect);
	render_mini_helper(instance, maze, status);
}

/**
 * render_mini_helper - Helps renders the walls and player on the minimap.
 *
 * @instance: Struct containing the SDL2 renderer and window.
 * @maze: Struct containing a pointer to the layout of the maze.
 * @status: Struct containing variables on camera position.
 */
void render_mini_helper(SDL_Instance instance, map maze, player status)
{
	SDL_Rect rect;
	int start_x;
	int end_x;
	int start_y;
	int end_y;
	int i = 0;
	int j = 0;

	rect.w = 14;
	rect.h = 14;
	rect.x = WINDOW_WIDTH - 210;
	rect.y = 0;

	find_x(&start_x, &end_x, maze, status);
	find_y(&start_y, &end_y, maze, status);

	SDL_SetRenderDrawColor(instance.renderer, 200, 200, 200, 0);
	for (i = start_y; i < end_y; i++)
	{
		rect.x = WINDOW_WIDTH - 210;
		for (j = start_x; j < end_x; j++)
		{
			if (maze.layout[i][j] > '0')
			{
				SDL_RenderFillRect(instance.renderer, &rect);
			}
			else if (i == (int) status.pos_x && j == (int) status.pos_y)
			{
				SDL_SetRenderDrawColor(instance.renderer, 255, 0, 0, 0);
				SDL_RenderFillRect(instance.renderer, &rect);
				SDL_SetRenderDrawColor(instance.renderer, 200, 200, 200, 0);
			}
			rect.x += 14;
		}
		rect.y += 14;
	}
}

/**
 * find_x - Find the starting and ending x-coordinate on the map to render
 * in the minimap.
 *
 * @start_x: Pointer to store the starting x-coordinate.
 * @end_x: Pointer to store the ending x-coordinate.
 * @maze: Struct containing a pointer to the layout of the maze.
 * @status: Struct containing variables on camera position.
 */
void find_x(int *start_x, int *end_x, map maze, player status)
{
	*start_x = (int) status.pos_y - 7;
	*end_x = 0;
	if (*start_x < 0)
	{
		*end_x = -(*start_x);
		*start_x = 0;
	}
	*end_x += (int) status.pos_y + 8;
	if (*end_x > (int) maze.width)
	{
		*end_x = (int) maze.width;
		*start_x = (int) maze.width - 15;
	}
}

/**
 * find_y - Find the starting and ending y-coordinate on the map to render
 * in the minimap.
 *
 * @start_y: Pointer to store the starting y-coordinate.
 * @end_y: Pointer to store the ending y-coordinate.
 * @maze: Struct containing a pointer to the layout of the maze.
 * @status: Struct containing variables on camera position.
 */
void find_y(int *start_y, int *end_y, map maze, player status)
{
	*start_y = (int) status.pos_x - 7;
	*end_y = 0;
	if (*start_y < 0)
	{
		*end_y = -(*start_y);
		*start_y = 0;
	}
	*end_y += (int) status.pos_x + 8;
	if (*end_y > (int) maze.height)
	{
		*end_y = (int) maze.height;
		*start_y = (int) maze.height - 15;
	}
}

