#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "Common.h"
#include "Enums.h"
#include "FixP.h"
#include "LoadBitmap.h"
#include "Engine.h"
#include "CRenderer.h"

#ifdef __APPLE__

#include <SDL.h>

#else

#include <SDL/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>
#endif
#endif

SDL_Surface *video;
SDL_Surface *stretchedBuffer;

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


uint8_t getPaletteEntry(uint32_t origin) {
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

void graphicsInit() {
    int r, g, b, c;

    SDL_Init(SDL_INIT_EVERYTHING);
    video = SDL_SetVideoMode(320, 240, 32, 0);
    for (r = 0; r < 256; r += 16) {
        for (g = 0; g < 256; g += 8) {
            for (b = 0; b < 256; b += 8) {
                uint32_t pixel = 0xFF000000 + (r << 16) + (g << 8) + (b);
                uint8_t paletteEntry = getPaletteEntry(pixel);
                palette[paletteEntry] = SDL_MapRGB(video->format, (((pixel & 0x000000FF))) - 0x38,
                                                   (((pixel & 0x0000FF00) >> 8)) - 0x18,
                                                   (((pixel & 0x00FF0000) >> 16)) - 0x10);
            }
        }
    }

#ifdef __EMSCRIPTEN__
    enterFullScreenMode ();
#endif
    defaultFont = loadBitmap("font.img");
    stretchedBuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 32, video->format->Rmask, video->format->Gmask,
                                           video->format->Bmask, video->format->Rmask);
}

void handleSystemEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            mBufferedCommand = kCommandQuit;
            return;
        }

        if (event.type == SDL_KEYDOWN) {

            SDLKey key = event.key.keysym.sym;

            switch (key) {
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

void flipRenderer() {

    int x = 0, y = 0;
    int dstY = 0;
    int scaller = 0;
    int even = 0;
    int heightY = 1;
    int chunky;
    uint8_t *src;
    uint32_t *dst;


    SDL_LockSurface(stretchedBuffer);


    for (y = 0; y < 200; ++y) {
        if (scaller == 4) {
            heightY = 2;
        } else {
            heightY = 1;
        }


        for (chunky = 0; chunky < heightY; ++chunky) {
            dst = stretchedBuffer->pixels;
            src = &framebuffer[(320 * y)];
            dst += (320 * (dstY + chunky));

            for (x = 0; x < 320; ++x) {
                *dst++ = palette[*src++];
            }
        }

        dstY++;
        scaller++;


        if (scaller == 5) {
            scaller = 0;
            dstY++;
        }
    }

    SDL_UnlockSurface(stretchedBuffer);
    SDL_BlitSurface(stretchedBuffer, NULL, video, NULL);

    SDL_Flip(video);
#ifndef __EMSCRIPTEN__
    SDL_Delay(1000 / 60);
#endif
}

void clearRenderer() {
    SDL_FillRect(video, NULL, 0);
}
