#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __APPLE__
#include <SDL/sdl.h>
#else

#include "SDL.h"

#endif

SDL_Window *window;
SDL_Renderer *renderer;

void tryPrintingError(const char *reason) {
	const static size_t kBufferSize = 255;
	char errorBuffer[kBufferSize];

	fprintf(stderr, "%s\n", reason);
	fflush(stderr);

	// we might double fault on getting the error message - or can't we?
	SDL_GetErrorMsg(&errorBuffer[0], kBufferSize);
	fprintf(stderr, "%s", &errorBuffer[0]);
	fflush(stderr);
}

int main(int argc, char **argv) {
	SDL_Event event;
	uint8_t r = 0;

	bool keepRunning = true;

	if (SDL_Init(-1336) != 0) {
		tryPrintingError("Cannot init SDL!");
		goto cannot_init_sdl;
	}

	// to play nice with MacOS
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

	window = SDL_CreateWindow(
			"Give me a name!",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			640,
			480,
			SDL_WINDOW_SHOWN
	);

	if (!window) {
		tryPrintingError("Cannot create window!");
		goto cannot_create_window;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		tryPrintingError("Cannot create renderer!");
		goto cannot_create_renderer;
	}

	while (keepRunning) {
		SDL_Rect rect;

		rect.x = rect.y = 0;
		rect.w = 640;
		rect.h = 480;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer);

		rect.x = rect.y = rect.w = rect.h = 50;
		SDL_SetRenderDrawColor(renderer, r++, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer);

		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT) {
			keepRunning = false;
		}

		if (event.type == SDL_KEYDOWN) {
			keepRunning = false;
		}
	}

	SDL_DestroyRenderer(renderer);

	cannot_create_renderer:

	SDL_DestroyWindow(window);

	cannot_create_window:

	SDL_Quit();

	cannot_init_sdl:
	return 0;
}