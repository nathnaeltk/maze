#include "../inc/maze.h"
#include <math.h>

/**
 * render_maze - Renders the floor and walls of the maze.
 *
 * @instance: Struct containing the SDL2 renderer and window.
 * @maze: Struct containing a pointer to the layout of the maze.
 * @status: Struct containing variables on camera position.
 */
void render_maze(SDL_Instance instance, map maze, player status)
{
	SDL_Rect rect;

	rect.x = 0;
	rect.y = (WINDOW_HEIGHT >> 1) - (int)status.pos_z;
	rect.w = WINDOW_WIDTH;
	rect.h = (WINDOW_HEIGHT >> 1) + (int)status.pos_z;
	SDL_SetRenderDrawColor(instance.renderer, 0, 128, 0, 0);
	SDL_RenderFillRect(instance.renderer, &rect);

	render_walls(instance, maze, status);
}

/**
 * render_walls - Renders the walls by performing DDA and then drawing the
 * walls with vertical lines.
 *
 * @instance: Struct containing the SDL2 renderer and window.
 * @status: Struct containing variables on camera position.
 * @maze: Struct containing a pointer to the layout of the maze.
 * @status: Struct containing variables on camera position.
 */
void render_walls(SDL_Instance instance, map maze, player status)
{
	camera vars;
	double perp_wall_dist;
	double camera_x;
	char side;
	int x;

	for (x = 0; x < WINDOW_WIDTH; x++)
	{
		camera_x = x * 2 / (double)WINDOW_WIDTH - 1;
		vars.ray_dir_x = status.dir_x + status.camera_plane_x * camera_x;
		vars.ray_dir_y = status.dir_y + status.camera_plane_y * camera_x;

		vars.map_x = (int)status.pos_x;
		vars.map_y = (int)status.pos_y;

		calculate_step(status, &vars);
		side = do_DDA(maze, &vars);

		if (side == 0)
		{
			perp_wall_dist =
					(vars.map_x - status.pos_x + (1 - vars.step_x) / 2) / vars.ray_dir_x;
			SDL_SetRenderDrawColor(instance.renderer, 128, 128, 128, 0);
		}
		else
		{
			perp_wall_dist =
					(vars.map_y - status.pos_y + (1 - vars.step_y) / 2) / vars.ray_dir_y;
			SDL_SetRenderDrawColor(instance.renderer, 114, 114, 114, 0);
		}
		draw_line(instance, x, perp_wall_dist, status);
	}
}

/**
 * calculate_step - Determines what direction to step in as well as the length
 * of ray from current position to next.
 *
 * @status: Struct containing variables on camera position.
 * @vars: Contains various variables needed to find and render walls correctly.
 */
void calculate_step(player status, camera *vars)
{
	vars->delta_dist_x = fabs(1 / vars->ray_dir_x);
	vars->delta_dist_y = fabs(1 / vars->ray_dir_y);

	if (vars->ray_dir_x < 0)
	{
		vars->step_x = -1;
		vars->side_dist_x = (status.pos_x - vars->map_x) * vars->delta_dist_x;
	}
	else
	{
		vars->step_x = 1;
		vars->side_dist_x = (vars->map_x + 1.0 - status.pos_x) * vars->delta_dist_x;
	}
	if (vars->ray_dir_y < 0)
	{
		vars->step_y = -1;
		vars->side_dist_y = (status.pos_y - vars->map_y) * vars->delta_dist_y;
	}
	else
	{
		vars->step_y = 1;
		vars->side_dist_y = (vars->map_y + 1.0 - status.pos_y) * vars->delta_dist_y;
	}
}

/**
 * do_DDA - Performs "Digital Differential Analysis" to locate and render the
 * walls of a maze.
 *
 * @maze: Struct containing a pointer to the layout of the maze.
 * @vars: Contains various variables needed to find and render walls correctly.
 *
 * Return: Side of the wall is on (North & South) or (East * West).
 */
char do_DDA(map maze, camera *vars)
{
	char hit;
	char side;

	hit = 0;
	while (hit == 0)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += vars->delta_dist_x;
			vars->map_x += vars->step_x;
			side = 0;
		}
		else
		{
			vars->side_dist_y += vars->delta_dist_y;
			vars->map_y += vars->step_y;
			side = 1;
		}
		if (maze.layout[vars->map_x][vars->map_y] > '0')
			hit = 1;
	}

	return (side);
}

/**
 * draw_line - Draws a vertical line for a wall.
 *
 * @instance: Struct containing the SDL2 renderer and window.
 * @window_x: The x coordinate position on thw window where a wall exists.
 * @perp_wall_dist: The distance projected on the camera direction to
 * the wall.
 * @status: Struct containing variables on camera position.
 */
void draw_line(SDL_Instance instance, int window_x, double perp_wall_dist,
		player status)
{
	int line_height;
	int draw_start;
	int draw_end;

	line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2 - status.pos_z;
	draw_end = line_height / 2 + WINDOW_HEIGHT / 2 - status.pos_z;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;

	SDL_RenderDrawLine(instance.renderer, window_x, draw_start, window_x,
			draw_end);
}
