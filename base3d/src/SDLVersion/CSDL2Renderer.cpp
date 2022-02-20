#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "Common.h"
#include "Enums.h"
#include "Globals.h"
#include "FixP.h"
#include "LoadBitmap.h"
#include "Engine.h"
#include "CRenderer.h"

#include "SDL.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>
#endif

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *videoTexture;

uint8_t getPaletteEntry(const uint32_t origin) {
	uint8_t shade;

	if (!(origin & 0xFF000000)) {
		return TRANSPARENCY_COLOR;
	}

	shade = 0;
	shade += (((((origin & 0x0000FF)) << 2) >> 8)) << 6;
	shade += (((((origin & 0x00FF00) >> 8) << 3) >> 8)) << 3;
	shade += (((((origin & 0xFF0000) >> 16) << 3) >> 8)) << 0;

	return shade;
}


#ifdef __EMSCRIPTEN__
void enterFullScreenMode() {
	EmscriptenFullscreenStrategy s;
	memset(&s, 0, sizeof(s));
	s.scaleMode = EMSCRIPTEN_FULLSCREEN_SCALE_ASPECT;
	s.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE;
	s.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;
	emscripten_enter_soft_fullscreen(0, &s);
}
#endif


void graphicsInit() {
	int b, g, r, c;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");


	window = SDL_CreateWindow(
			"The Mistral Report",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			640,
			480,
			SDL_WINDOW_SHOWN
	);

	renderer = SDL_CreateRenderer(window, -1, 0);

	videoTexture = SDL_CreateTexture(renderer,
									 SDL_PIXELFORMAT_ABGR8888,
									 SDL_TEXTUREACCESS_STREAMING,
									 640, 480
	);

	for (b = 0; b < 256; b += 16) {
		for (g = 0; g < 256; g += 8) {
			for (r = 0; r < 256; r += 8) {
				uint32_t pixel = 0xFF000000 + ((b - 0x38) << 16) + ((g - 0x18) << 8) + (r - 0x10);
				uint8_t paletteEntry = getPaletteEntry(pixel);
				palette[paletteEntry] = pixel;
			}
		}
	}


#ifdef __EMSCRIPTEN__
	enterFullScreenMode ();
#endif
	defaultFont = loadBitmap("font.img");
}

void handleSystemEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT) {
			mBufferedCommand = kCommandQuit;
			return;
		}

		if (event.type == SDL_KEYDOWN) {

			switch (event.key.keysym.sym) {
				case SDLK_RETURN:
				case SDLK_z:
					mBufferedCommand = kCommandFire1;
					break;

				case SDLK_ESCAPE:
				case SDLK_q:
					mBufferedCommand = kCommandBack;
					break;

				case SDLK_SPACE:

				case SDLK_s:
					mBufferedCommand = kCommandStrafeLeft;
					break;
				case SDLK_d:
					mBufferedCommand = kCommandStrafeRight;
					break;

				case SDLK_x:
					mBufferedCommand = kCommandFire2;
					break;
				case SDLK_c:
					mBufferedCommand = kCommandFire3;
					break;
				case SDLK_e:
					mBufferedCommand = kCommandFire4;
					break;

				case SDLK_LEFT:
					mBufferedCommand = kCommandLeft;
					break;
				case SDLK_RIGHT:
					mBufferedCommand = kCommandRight;
					break;
				case SDLK_UP:
					mBufferedCommand = kCommandUp;
					break;
				case SDLK_DOWN:
					mBufferedCommand = kCommandDown;
					break;

				default:
					return;
			}
		}
	}
}

void graphicsShutdown() {
	SDL_Quit();

	releaseBitmap(defaultFont);
}

unsigned long t0, t1, t2;

void flipRenderer() {
	void *pixels;
	int pitch;

	uint8_t *src;
	uint32_t *dst;


	SDL_LockTexture(videoTexture, NULL, &pixels, &pitch);

	dst = (uint32_t *) pixels;
	src = &framebuffer[0];

	for (int c = 0; c < (640 * 480); ++c) {
		*dst++ = palette[*src++];
	}

	SDL_UnlockTexture(videoTexture);

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, videoTexture, NULL, NULL);
	SDL_RenderPresent(renderer);

#ifndef __EMSCRIPTEN__
	SDL_Delay(1000 / 60);
#endif
}
