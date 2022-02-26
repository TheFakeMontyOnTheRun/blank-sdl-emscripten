#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <unistd.h>

#include "FixP.h"
#include "Globals.h"
#include "LoadBitmap.h"
#include "Enums.h"
#include "Engine.h"
#include "FixP.h"
#include "Common.h"
#include "LoadBitmap.h"
#include "Engine.h"
#include "CRenderer.h"
#include "CPackedFileReader.h"


struct Bitmap *character;

extern size_t biggestOption;

struct Vec2i {
    int x;
    int y;
};

void initVec2i(struct Vec2i *__restrict__ vec, int x, int y) {
    vec->x = x;
    vec->y = y;
}

struct Vec2i playerPos;

int32_t Interrogation_initStateCallback(int32_t tag, void *data) {

    currentBackgroundBitmap = loadBitmap("pattern.img");
	character = loadBitmap("player.img");
    timeUntilNextState = 10000 - 1;

	initVec2i(&playerPos, 32, 32);

    currentPresentationState = kWaitingForInput;
    return 0;
}

void Interrogation_initialPaintCallback() {
    dirtyLineY0 = 0;
    dirtyLineY1 = 480;
}

void Interrogation_repaintCallback() {
	drawRepeatBitmap(0, 0, 640, 480, currentBackgroundBitmap);
	drawBitmap(playerPos.x, playerPos.y, character, true);
}

int32_t Interrogation_tickCallback(int32_t tag, void *data) {

    long delta = *((long *) data);

    timeUntilNextState -= delta;


        switch (tag) {
            case kCommandBack:
                timeUntilNextState = 0;
                return kMainMenu;
            case kCommandUp:
            	playerPos.y -= 32;
            	break;
            case kCommandDown:
				playerPos.y += 32;
                break;
            case kCommandLeft:
				playerPos.x -= 32;
                break;
            case kCommandRight:
				playerPos.x += 32;
                break;

            case kCommandFire1:
                break;
            default:
                return -1;
        }

	if (playerPos.x < 0) {
		playerPos.x = 0;
	}

	if (playerPos.y < 0) {
		playerPos.y = 0;
	}

	if (playerPos.x >= 640) {
		playerPos.x = 608;
	}

	if (playerPos.y >= 480) {
		playerPos.y = 448;
	}

	return -1;
}

void Interrogation_unloadStateCallback() {

    releaseBitmap(currentBackgroundBitmap);
    releaseBitmap(character);
}
