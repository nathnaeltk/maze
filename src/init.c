#include "../inc/init.h"
#include <stdio.h>

/**
 * init_SDL - Initializes the window and renderer variables stored in
 * `instance`.
 *
 * @instance: Pointer to the struct containing SDL window and SDL renderer
 * variables.
 *
 * Return: 0 on successful initialization otherwise 1.
 */
char init_SDL(SDL_Instance *instance)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (FAILURE);
	}
	instance->window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_CENTERED,
					    SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (FAILURE);
	}

	instance->renderer = SDL_CreateRenderer(instance->window, -1,
						SDL_RENDERER_ACCELERATED |
						SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * init_keys - Set status of all key motions to off.
 *
 * @keys: Pointer to the struct containing status of keys.
 */
void init_keys(keys_state *keys)
{
	keys->advance = 0;
	keys->retreat = 0;
	keys->left = 0;
	keys->right = 0;
	keys->m_left = 0;
	keys->m_right = 0;
	keys->crouch = 0;
	keys->sprint = 0;
	keys->mini_map = 0;
}

/**
 * init_player - Set the initial position and camera of the player.
 *
 * @status: Pointer to the struct containing position and camera values.
 * @maze: Struct containing the starting positions of the maze.
 */
void init_player(player *status, map maze)
{
	status->pos_x = maze.start_x;
	status->pos_y = maze.start_y;
	status->pos_z = 0;
	status->dir_x = -1;
	status->dir_y = 0;
	status->camera_plane_x = 0;
	status->camera_plane_y = 0.66;
	status->time = 0;
}

