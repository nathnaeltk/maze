#include "../inc/update.h"

/**
 * update_player - Update the player's camera and position based on their
 * input.
 *
 * @maze: Struct containing a pointer to the layout of the maze.
 * @keys: Pointer to the struct containing status of keys.
 * @status: Pointer to the struct containing variables on camera position.
 */
void update_player(map maze, keys_state *keys, player *status)
{
	double old_time;
	double frame_time;

	old_time = status->time;
	status->time = SDL_GetTicks();
	frame_time = (status->time - old_time) / 1000.0;
	status->move_speed = frame_time * (keys->crouch ? 1.0 : keys->sprint ?
			9.0 : 4.0);
	status->rot_speed = frame_time * 3.0;
	status->pos_z = keys->crouch > 0 ? WINDOW_HEIGHT >> 2 : 0;

	if (keys->advance == 1)
		move_forwd(maze, status);
	if (keys->retreat)
		move_backwd(maze, status);
	if (keys->m_left == 1)
	{
		rotate_left(status);
		keys->m_left = 0;
	}
	if (keys->m_right == 1)
	{
		rotate_right(status);
		keys->m_right = 0;
	}
	if (keys->right == 1)
	{
		if (SDL_GetRelativeMouseMode() == 0)
			rotate_right(status);
		else
			move_right(maze, status);
	}
	if (keys->left == 1)
	{
		if (SDL_GetRelativeMouseMode() == 0)
			rotate_left(status);
		else
			move_left(maze, status);
	}
}
/**
 * move_forwd - Move the player forward if allowed (no wall).
 *
 * @maze: Struct containing a pointer to the layout of the maze.
 * @status: Pointer to the struct containing variables on camera position.
 */
void move_forwd(map maze, player *status)
{
	double dist_x;
	double dist_y;

	dist_x = status->dir_x * status->move_speed;
	dist_y = status->dir_y * status->move_speed;
	if (maze.layout[(int)(status->pos_x + dist_x)][(int)status->pos_y] == '0')
		status->pos_x += dist_x;
	if (maze.layout[(int)status->pos_x][(int)(status->pos_y + dist_y)] == '0')
		status->pos_y += dist_y;
}

/**
 * move_backwd - Move the player backwards if allowed (no wall).
 *
 * @maze: Struct containing a pointer to the layout of the maze.
 * @status: Pointer to the struct containing variables on camera position.
 */
void move_backwd(map maze, player *status)
{
	double dist_x;
	double dist_y;

	dist_x = status->dir_x * status->move_speed;
	dist_y = status->dir_y * status->move_speed;
	if (maze.layout[(int)(status->pos_x - dist_x)][(int)status->pos_y] == '0')
		status->pos_x -= dist_x;
	if (maze.layout[(int)status->pos_x][(int)(status->pos_y - dist_y)] == '0')
		status->pos_y -= dist_y;
}

/**
 * move_left - Move the player laterally left if allowed (no wall). Takes
 * the perpendicular of dir_x and dir_y to acquire lateral distance.
 *
 * @maze: Struct containing a pointer to the layout of the maze.
 * @status: Pointer to the struct containing variables on camera position.
 */
void move_left(map maze, player *status)
{
	double dist_x;
	double dist_y;

	dist_x = status->dir_y * status->move_speed;
	dist_y = status->dir_x * status->move_speed;
	if (maze.layout[(int)(status->pos_x - dist_x)][(int)status->pos_y] == '0')
		status->pos_x -= dist_x;
	if (maze.layout[(int)status->pos_x][(int)(status->pos_y + dist_y)] == '0')
		status->pos_y += dist_y;
}

/**
 * move_right - Move the player laterally right if allowed (no wall). Takes
 * the perpendicular of dir_x and dir_y to acquire lateral distance.
 *
 * @maze: Struct containing a pointer to the layout of the maze.
 * @status: Pointer to the struct containing variables on camera position.
 */
void move_right(map maze, player *status)
{
	double dist_x;
	double dist_y;

	dist_x = status->dir_y * status->move_speed;
	dist_y = status->dir_x * status->move_speed;
	if (maze.layout[(int)(status->pos_x + dist_x)][(int)status->pos_y] == '0')
		status->pos_x += dist_x;
	if (maze.layout[(int)status->pos_x][(int)(status->pos_y - dist_y)] == '0')
		status->pos_y -= dist_y;
}
