#include "../inc/update.h"

/**
 * rotate_right - Rotate the camera right.
 *
 * @status: Pointer to the struct containing variables on camera position.
 */
void rotate_right(player *status)
{
	double old_dir_x;
	double old_plane_x;
	double sine_val;
	double cosine_val;

	sine_val = sin(-status->rot_speed);
	cosine_val = cos(-status->rot_speed);
	old_dir_x = status->dir_x;

	status->dir_x = status->dir_x * cosine_val - status->dir_y * sine_val;
	status->dir_y = old_dir_x * sine_val + status->dir_y * cosine_val;
	old_plane_x = status->camera_plane_x;
	status->camera_plane_x = status->camera_plane_x * cosine_val -
			status->camera_plane_y * sine_val;
	status->camera_plane_y = old_plane_x * sine_val + status->camera_plane_y *
			cosine_val;
}

/**
 * rotate_left - Rotate the camera left.
 *
 * @status: Pointer to the struct containing variables on camera position.
 */
void rotate_left(player *status)
{
	double old_dir_x;
	double old_plane_x;
	double sine_val;
	double cosine_val;

	sine_val = sin(status->rot_speed);
	cosine_val = cos(status->rot_speed);
	old_dir_x = status->dir_x;

	status->dir_x = status->dir_x * cosine_val - status->dir_y * sine_val;
	status->dir_y = old_dir_x * sine_val + status->dir_y * cosine_val;
	old_plane_x = status->camera_plane_x;
	status->camera_plane_x = status->camera_plane_x * cosine_val -
			status->camera_plane_y * sine_val;
	status->camera_plane_y = old_plane_x * sine_val + status->camera_plane_y *
			cosine_val;
}
