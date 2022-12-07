#ifndef MAZE_UPDATE_H
#define MAZE_UPDATE_H

#include <SDL2/SDL.h>
#include "init.h"

void update_player(map maze, keys_state *keys, player *status);

void move_forwd(map maze, player *status);

void move_backwd(map maze, player *status);

void move_left(map maze, player *status);

void move_right(map maze, player *status);

void rotate_left(player *status);

void rotate_right(player *status);

#endif
