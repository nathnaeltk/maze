#ifndef MAZE_INPUT_H
#define MAZE_INPUT_H

#include <SDL2/SDL.h>
#include "init.h"

char poll_inputs(keys_state *keys);

void handle_mouse(SDL_Event event, keys_state *keys);

char handle_keydown(SDL_Event event, keys_state *keys);

void handle_keyup(SDL_Event event, keys_state *keys);

#endif
