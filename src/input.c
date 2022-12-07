#include "../inc/input.h"
#include <stdio.h>

/**
 * poll_inputs - Handle keyboard inputs.
 *
 * @keys: Pointer to the struct containing status of keys.
 *
 * Return: 0 to continue rendering, otherwise 1 to close the window.
 */
char poll_inputs(keys_state *keys)
{
	SDL_Event event;


	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_MOUSEMOTION:
				if (SDL_GetRelativeMouseMode() == 1)
					handle_mouse(event, keys);
				break;
			case SDL_KEYDOWN:
				if (handle_keydown(event, keys) == 1)
					return (1);
				break;
			case SDL_KEYUP:
				handle_keyup(event, keys);
				break;
			case SDL_QUIT:
				return (1);
			default:
				break;
		}
	}
	return (0);
}

/**
 * handle_mouse - Handle horizontal mouse motion.
 *
 * @event: SDL event
 * @keys: Pointer to the struct containing status of keys.
 */
void handle_mouse(SDL_Event event, keys_state *keys)
{
	if (event.motion.xrel > 0)
		keys->m_right = 1;
	if (event.motion.xrel < 0)
		keys->m_left = 1;
}

/**
 * handle_keydown - Handle key down events.
 *
 * @event: SDL event
 * @keys: Pointer to the struct containing status of keys.
 *
 * Return: 0 to continue rendering, otherwise 1 to close the window.
 */
char handle_keydown(SDL_Event event, keys_state *keys)
{
	switch (event.key.keysym.sym)
	{
		case SDLK_w:
		case SDLK_UP:
			keys->advance = 1;
			break;
		case SDLK_s:
		case SDLK_DOWN:
			keys->retreat = 1;
			break;
		case SDLK_a:
		case SDLK_LEFT:
			keys->left = 1;
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			keys->right = 1;
			break;
		case SDLK_LCTRL:
			SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
			break;
		case SDLK_z:
			keys->crouch = !keys->crouch;
			break;
		case SDLK_LSHIFT:
			keys->sprint = 1;
			break;
		case SDLK_TAB:
			keys->mini_map = !keys->mini_map;
			break;
		case SDLK_ESCAPE:
			return (1);
		default:
			break;
	}
	return (0);
}

/**
 * handle_keyup - Handle key down events.
 *
 * @event: SDL event
 * @keys: Pointer to the struct containing status of keys.
 *
 * Return: 0 to continue rendering, otherwise 1 to close the window.
 */
void handle_keyup(SDL_Event event, keys_state *keys)
{
	switch (event.key.keysym.sym)
	{
		case SDLK_w:
		case SDLK_UP:
			keys->advance = 0;
			break;
		case SDLK_s:
		case SDLK_DOWN:
			keys->retreat = 0;
			break;
		case SDLK_a:
		case SDLK_LEFT:
			keys->left = 0;
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			keys->right = 0;
			break;
		case SDLK_LSHIFT:
			keys->sprint = 0;
			break;
		default:
			break;
	}
}
