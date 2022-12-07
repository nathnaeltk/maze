#include "../inc/maze.h"

/**
 * main - Calls for the creation of a 3D maze using SDL. Several structs
 * containing variables such as initial x,y map position and camera position
 * is initialized. A loop is cycled to update the window according to keyboard
 * inputs and breaks when the user presses the 'esc' key.
 *
 * Return: EXIT_SUCCESS upon graceful end of execution. EXIT_FAILURE upon
 * failure to: create a SDL window or renderer, initialize map layout.
 */
int main(void)
{
	SDL_Instance instance;
	keys_state keys;
	map maze;
	player status;

	if (init_SDL(&instance) != SUCCESS)
		return (EXIT_FAILURE);
	if (get_map(&maze) != SUCCESS)
		return (EXIT_FAILURE);
	init_keys(&keys);
	init_player(&status, maze);


	while (poll_inputs(&keys) != 1)
	{
		SDL_SetRenderDrawColor(instance.renderer, 135, 206, 250, 0);
		SDL_RenderClear(instance.renderer);

		render_maze(instance, maze, status);
		if (keys.mini_map == 1)
			render_mini(instance, maze, status);
		SDL_RenderPresent(instance.renderer);

		update_player(maze, &keys, &status);
	}
	map_free(&maze);
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (EXIT_SUCCESS);
}
