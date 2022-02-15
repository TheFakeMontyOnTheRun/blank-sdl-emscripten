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
    int r, g, b;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

    window =
            SDL_CreateWindow("The Mistral Report", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);

    for (r = 0; r < 256; r += 16) {
        for (g = 0; g < 256; g += 8) {
            for (b = 0; b < 256; b += 8) {
                uint32_t pixel = 0xFF000000 + (r << 16) + (g << 8) + (b);
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
    SDL_Rect rect;
    uint32_t pixel;
    int x, y;

    rect.w = 1;
    rect.h = 1;

    for (y = 0; y < 480; ++y) {

        if ( y < dirtyLineY0 || y > dirtyLineY1 ) {
            continue;
        }

        for (x = 0; x < 640; ++x) {

            rect.x = x;
            rect.y = y;

            pixel = palette[framebuffer[(640 * y) + x]];

            SDL_SetRenderDrawColor(renderer, (pixel & 0x000000FF) - 0x38,
                                   ((pixel & 0x0000FF00) >> 8) - 0x18,
                                   ((pixel & 0x00FF0000) >> 16) - 0x10, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);

#ifndef __EMSCRIPTEN__
    SDL_Delay(1000 / 60);
#endif
}
