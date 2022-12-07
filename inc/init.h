#ifndef MAZE_INIT_H
#define MAZE_INIT_H

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1260
#define WINDOW_HEIGHT 720
#define MAZE_WIDTH 10
#define MAZE_HEIGHT 10
#define SUCCESS 0
#define FAILURE 1

/**
 * struct SDL_Instance - Contains pointer to SDL window and SDL renderer.
 *
 * @window: Pointer to SDL window.
 * @renderer: Pointer to SDL renderer.
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

/**
 * struct keys_state - Contains current status of various keys tied to motion.
 *
 * @advance: Status of up arrow key or 'W' key.
 * @retreat: Status of down arrow key or 'S' key.
 * @left: Status of left arrow key or 'A' key.
 * @right: Status of right arrow key or 'D' key.
 * @crouch: Status of crouch mode.
 * @sprint: Status of sprint mode.
 * @m_left: Status of mouse left movement.
 * @m_right: Status of mouse right movement.
 * @mini_map: Status of minimap.
 */
typedef struct keys_state
{
	char advance;
	char retreat;
	char left;
	char right;
	char crouch;
	char sprint;
	char m_left;
	char m_right;
	char mini_map;
} keys_state;

/**
 * struct player - Contains various information on the player's position and
 * camera.
 *
 * @pos_x: X-coordinate of the player's position.
 * @pos_y: Y-coordinate of the player's position.
 * @pos_z: Z-coordinate of the player's position.
 * @dir_x: Direction of the player on the x-axis.
 * @dir_y: Direction  of the player on the y-axis.
 * @camera_plane_x: The plane of the player's camera on the x-axis.
 * @camera_plane_y: The plane of the player's camera on the y-axis.
 * @time: Current time.
 * @move_speed: Speed to move at relative to time since the last frame.
 * @rot_speed: Speed to rotate the camera relative to the time since the last
 * frame.
 */
typedef struct player
{
	double pos_x;
	double pos_y;
	double pos_z;
	double dir_x;
	double dir_y;
	double camera_plane_x;
	double camera_plane_y;
	double time;
	double move_speed;
	double rot_speed;
} player;

/**
 * struct camera - Contains various variables needed to find and render walls
 * correctly.
 *
 * @ray_dir_x: Ray direction on x-axis.
 * @ray_dir_y: Ray direction on y-axis.
 * @side_dist_x: Length of ray from current position to next x-side.
 * @side_dist_y: Length of ray from current position to next y-side.
 * @delta_dist_x: Length of ray from one x to the next x.
 * @delta_dist_y: Length of ray from one y to the next y.
 * @map_x: x-position on the map.
 * @map_y: y-position on the map.
 * @step_x: Which x-direction to step in.
 * @step_y: Which y-direction to step in.
 */
typedef struct camera
{
	double ray_dir_x;
	double ray_dir_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	unsigned int map_x;
	unsigned int map_y;
	int step_x;
	int step_y;
} camera;

/**
 * struct map - Contains various variables or pointers that represent the maze
 * in a 2D array of chars.
 *
 * @layout: A double pointer to the layout of the maze.
 * @width: The width of the maze.
 * @height: The height of the maze.
 * @start_x: Starting x-position on the map upon loading in.
 * @start_y: Starting y-position on the map upon loading in.
 */
typedef struct map
{
	char **layout;
	unsigned int width;
	unsigned int height;
	unsigned int start_x;
	unsigned int start_y;
} map;

char init_SDL(SDL_Instance *instance);

void init_keys(keys_state *keys);

void init_player(player *status, map maze);

char get_map(map *maze);

char scan_layout(FILE *f, map *maze);

char map_malloc(map *maze);

void map_free(map *maze);

char get_default(map *maze);

#endif
