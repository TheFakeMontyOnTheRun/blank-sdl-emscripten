#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <unistd.h>

#include "FixP.h"
#include "LoadBitmap.h"
#include "Enums.h"
#include "Engine.h"
#include "FixP.h"
#include "Common.h"
#include "LoadBitmap.h"
#include "Engine.h"
#include "CRenderer.h"
#include "CPackedFileReader.h"

#define kMazeSideSize 8

int interrogationMap[kMazeSideSize][kMazeSideSize];
int interrogationReveal[kMazeSideSize][kMazeSideSize];

int emotionAmount[4];

struct Bitmap *emotions[4];

struct Vec2i interrogationPosition;
struct Vec2i interrogationTargetSpot;
struct Bitmap *character;
struct Bitmap *eyesL;
struct Bitmap *eyesR;
struct Bitmap *eyesW;
struct Bitmap *eyesB;
struct Bitmap *eyesC;

char suspectName[256];
int noMoreMoves = FALSE;

extern size_t biggestOption;

struct Vec2i {
    int8_t x;
    int8_t y;
};

void initVec2i(struct Vec2i *__restrict__ vec, int8_t x, int8_t y) {
    vec->x = x;
    vec->y = y;
}


void initVec2i(struct Vec2i *__restrict__ vec, int8_t x, int8_t y);

void initMaze(const int indexZeroBased) {
    size_t fileSize;
    FILE *fileInput;
    char filename[16];
    int8_t x, y;
    char *index;
    char mazeBuffer[(kMazeSideSize + 1) * kMazeSideSize]; /* + 1 for \n */
    int randomTarget = 1 + (rand() % ((kMazeSideSize * 2) - 1));
    int randomStart = 1 + (rand() % ((kMazeSideSize * 2) - 1));
    int randomOrder = (rand() % 2);

    if (indexZeroBased != -1) {
        strcpy(&suspectName[0], "Sofia");
        sprintf (&filename[0], "%s.img", suspectName);
        character = loadBitmap(filename);
        sprintf (&filename[0], "%s.maze", suspectName);
    } else {
        sprintf (&filename[0], "Sofia.img");
        character = loadBitmap(filename);
        sprintf (&filename[0], "practice.maze");
    }

    memset (interrogationReveal, 0,
            kMazeSideSize * kMazeSideSize * sizeof(int));

    fileSize = sizeOfFile(filename);
    fileInput = openBinaryFileFromPath(filename);
    assert (fread(&mazeBuffer, fileSize, 1, fileInput));
    fclose(fileInput);

    index = mazeBuffer;
    for (y = 0; y < kMazeSideSize; ++y) {
        for (x = 0; x < kMazeSideSize; ++x) {
            interrogationMap[y][x] = ((*index) == '1');

            if (!interrogationMap[y][x]) {
                if (randomOrder) {
                    if (y < 4) {
                        randomTarget--;
                    } else {
                        randomStart--;
                    }

                } else {
                    if (y > 4) {
                        randomTarget--;
                    } else {
                        randomStart--;
                    }
                }
            }

            if (!randomStart) {
                interrogationPosition.x = x;
                interrogationPosition.y = y;
                interrogationMap[y][x] = FALSE;
            }

            if (!randomTarget) {
                interrogationTargetSpot.x = x;
                interrogationTargetSpot.y = y;
                interrogationMap[y][x] = FALSE;
            }

            ++index;
        }
        ++index;
    }
}

int32_t Interrogation_initStateCallback(int32_t tag, void *data) {

    emotionAmount[0] = 20;
    emotionAmount[1] = 20;
    emotionAmount[2] = 20;
    emotionAmount[3] = 20;

    noMoreMoves = FALSE;
    initMaze(tag - kInterrogate_Sofia);

    emotions[0] = loadBitmap("love.img");
    emotions[1] = loadBitmap("rage.img");
    emotions[2] = loadBitmap("nostalgia.img");
    emotions[3] = loadBitmap("volatility.img");

    currentBackgroundBitmap = loadBitmap("pattern.img");
    eyesL = loadBitmap("eyesl.img");
    eyesR = loadBitmap("eyesr.img");
    eyesW = loadBitmap("eyesw.img");
    eyesB = loadBitmap("eyesb.img");
    eyesC = loadBitmap("eyesc.img");

    timeUntilNextState = 10000 - 1;

    currentPresentationState = kWaitingForInput;
    return 0;
}

void Interrogation_initialPaintCallback() {

}

void Interrogation_repaintCallback() {
    int c;
    int16_t x, y;
    int dx;
    int dy;
    int distance;
    int blinkTime;
    int sideEyeTime;

    drawRepeatBitmap(0, 32, 320, 200, currentBackgroundBitmap);

    fill(64 + 8, 8 + 8, 160, 128, 0, TRUE);
    fill(64, 8, 160, 128, 255, FALSE);
    drawBitmap(64, 8, character, TRUE);

    drawRect(64, 8, 160, 128, 0);
    fill(64, 8, 160, 8, 0, FALSE);
    drawTextAt(10, 2, suspectName, 255);

    fill(8, 144, 120, 8, 0, FALSE);
    fill(142, 144, 80, 8, 0, FALSE);
    fill(236, 144, 64, 8, 0, FALSE);

    drawTextAt(3, 19, "Interrogation", 255);
    drawTextAt(20, 19, "Emotions", 255);
    drawTextAt(32, 19, "Stress", 255);

    fill(8 + 8, 144 + 8, 120, 48, 0, TRUE);
    fill(142 + 8, 144 + 8, 80, 48, 0, TRUE);
    fill(236 + 8, 144 + 8, 64, 48, 0, TRUE);

    fill(8, 152, 120, 40, 255, FALSE);
    fill(142, 152, 80, 40, 255, FALSE);
    fill(236, 152, 64, 40, 255, FALSE);

    drawRect(8, 152, 120, 40, 0);
    drawRect(142, 152, 80, 40, 0);

    for (c = 0; c < 4; ++c) {
        drawBitmap(142 + 8, (uint16_t) (156 + (c * 8)), emotions[c],
                   FALSE);
    }

    for (c = 0; c < 4; ++c) {
        fill(142 + 20, (uint16_t) (156 + (c * 8)), emotionAmount[c] * 2,
             8, getPaletteEntry(0xFF999999), FALSE);

        drawRect(142 + 20, (uint16_t) (156 + (c * 8)),
                 emotionAmount[c] * 2, 8, 0);
    }

    drawBitmap(40, 154, emotions[0], FALSE);
    drawBitmap(40, 182, emotions[1], FALSE);
    drawBitmap(88, 154, emotions[2], FALSE);
    drawBitmap(88, 182, emotions[3], FALSE);

    for (y = 0; y < kMazeSideSize; ++y) {
        for (x = 0; x < kMazeSideSize; ++x) {

            if (!interrogationReveal[y][x]
                && ((abs(interrogationPosition.x - x) > 1)
                    || (abs(interrogationPosition.y - y) > 1))) {
                fill(52 + x * 4, 156 + (y * 4), 4, 4, 16, FALSE);
                continue;
            }

            if (interrogationTargetSpot.x == x && interrogationTargetSpot.y == y) {
                fill(52 + x * 4, 156 + (y * 4), 4, 4, 128, FALSE);
            } else {


                if (interrogationMap[y][x]) {
                    fill(52 + x * 4, 156 + (y * 4), 4, 4, 100, FALSE);
                } else {
                    fill(52 + x * 4, 156 + (y * 4), 4, 4, 255, FALSE);
                }
            }


            if (interrogationPosition.x == x && interrogationPosition.y == y) {
                fill(52 + x * 4, 156 + (y * 4), 4, 4,
                     (((timeUntilNextState / 100) % 2) == 0) ? 32 : 48, FALSE);
                continue;
            }
        }
    }

    for (y = 0; y < kMazeSideSize; ++y) {
        for (x = 0; x < kMazeSideSize; ++x) {
            drawRect(52 + x * 4, 156 + (y * 4), 4, 4, 0);
        }
    }

    dx = abs(interrogationPosition.x - interrogationTargetSpot.x);
    dy = abs(interrogationPosition.y - interrogationTargetSpot.y);
    distance = (dx + dy);
    blinkTime = (((timeUntilNextState / 1000) % 4) == 0);
    sideEyeTime = (((timeUntilNextState / 1000) % 2) == 0);

    if (distance <= 2 && !blinkTime) {
        drawBitmap(236, 152, eyesB, TRUE);
    } else if (timeUntilNextState >= (10000 - 250)) {
        drawBitmap(236, 152, eyesW, TRUE);
    } else if (blinkTime) {
        drawBitmap(236, 152, eyesC, TRUE);
    } else {
        if (distance > 8) {
            if (sideEyeTime) {
                drawBitmap(236, 152, eyesL, TRUE);
            }

            if (!sideEyeTime) {
                drawBitmap(236, 152, eyesR, TRUE);
            }
        } else {
            drawBitmap(236, 152, eyesW, TRUE);
        }
    }

    drawRect(236, 152, 64, 40, 0);


    switch (currentPresentationState) {
        case kConfirmInputBlink1:
        case kConfirmInputBlink3:
        case kConfirmInputBlink5: {
            uint8_t color = 128;
            const char *text = (noMoreMoves) ? "Failed!" : "GOTCHA!";
            size_t len = strlen(text);
            fill(0, 64, 320, 8, 0, FALSE);
            drawTextAt(20 - (len / 2), 9, text, color);
        }
            break;

        case kConfirmInputBlink2:
        case kConfirmInputBlink4:
        case kConfirmInputBlink6: {
            uint8_t color = 0;
            const char *text = (noMoreMoves) ? "Failed!" : "GOTCHA!";
            size_t len = strlen(text);
            fill(0, 64, 320, 8, 0, FALSE);
            drawTextAt(20 - (len / 2), 9, text, color);
        }
        case kAppearing:
        case kFade:
        case kWaitingForInput:
        default:
            break;
    }
}

int32_t Interrogation_tickCallback(int32_t tag, void *data) {

    long delta = *((long *) data);

    timeUntilNextState -= delta;


    if (timeUntilNextState <= 0) {

        switch (currentPresentationState) {
            case kAppearing:
                timeUntilNextState = MENU_ITEM_TIME_TO_BECOME_ACTIVE_MS;
                currentPresentationState = kWaitingForInput;
                break;
            case kWaitingForInput:
                timeUntilNextState = 10000 - 1;
                /* return kMainMenu; */
                break;
            case kConfirmInputBlink1:
            case kConfirmInputBlink2:
            case kConfirmInputBlink3:
            case kConfirmInputBlink4:
            case kConfirmInputBlink5:
            case kConfirmInputBlink6:
                timeUntilNextState = MENU_ITEM_TIME_TO_BLINK_MS;
                currentPresentationState =
                        (enum EPresentationState) ((int) currentPresentationState + 1);
                break;
            case kFade:
                return nextNavigationSelection;
        }
    }

    if (currentPresentationState == kWaitingForInput) {
        int px;
        int py;

        /* did we reach the target? give the clue and go straight to the dossier, showing the clue. */
        if (interrogationPosition.x == interrogationTargetSpot.x
            && interrogationPosition.y == interrogationTargetSpot.y) {

            timeUntilNextState = MENU_ITEM_TIME_TO_BECOME_ACTIVE_MS;
            currentPresentationState = kConfirmInputBlink1;

            nextNavigationSelection = kMainMenu;

            return -1;
        }

        px = interrogationPosition.x;
        py = interrogationPosition.y;
        interrogationReveal[py][px] = TRUE;

        /* perform checks for early bailing out if no more moves are available */

        if (noMoreMoves) {
            timeUntilNextState = MENU_ITEM_TIME_TO_BECOME_ACTIVE_MS;
            currentPresentationState = kConfirmInputBlink1;
            nextNavigationSelection = kMainMenu;
            return -1;
        }

        switch (tag) {
            case kCommandBack:
                timeUntilNextState = 0;
                return kMainMenu;
            case kCommandUp:

                if (!emotionAmount[0] || !emotionAmount[2]) {
                    noMoreMoves = TRUE;
                    return -1;
                }

                if (interrogationPosition.y <= 0) {
                    return -1;
                }

                if (interrogationMap[interrogationPosition.y - 1]
                    [interrogationPosition.x]
                    == 1) {
                    return -1;
                }
                interrogationPosition.y--;

                if (!interrogationReveal[interrogationPosition.y]
                [interrogationPosition.x]
                    && emotionAmount[0] > 0 && emotionAmount[2] > 0) {

                    emotionAmount[0]--;
                    emotionAmount[2]--;
                }

                break;
            case kCommandDown:
                if (!emotionAmount[1] || !emotionAmount[3]) {
                    noMoreMoves = TRUE;
                    return -1;
                }

                if (interrogationPosition.y >= 7) {
                    return -1;
                }

                if (interrogationMap[interrogationPosition.y + 1]
                    [interrogationPosition.x]
                    == 1) {
                    return -1;
                }

                interrogationPosition.y++;

                if (!interrogationReveal[interrogationPosition.y]
                [interrogationPosition.x]
                    && emotionAmount[1] > 0 && emotionAmount[3] > 0) {
                    emotionAmount[1]--;
                    emotionAmount[3]--;
                }
                break;

            case kCommandLeft:
                if (!emotionAmount[1] || !emotionAmount[0]) {
                    noMoreMoves = TRUE;
                    return -1;
                }

                if (interrogationPosition.x <= 0) {
                    return -1;
                }

                if (interrogationMap[interrogationPosition.y]
                    [interrogationPosition.x - 1]
                    == 1) {
                    return -1;
                }

                interrogationPosition.x--;

                if (!interrogationReveal[interrogationPosition.y]
                [interrogationPosition.x]
                    && emotionAmount[0] > 0 && emotionAmount[1] > 0) {
                    emotionAmount[0]--;
                    emotionAmount[1]--;
                }
                break;
            case kCommandRight:
                if (!emotionAmount[2] || !emotionAmount[3]) {
                    noMoreMoves = TRUE;
                    return -1;
                }

                if (interrogationPosition.x >= 7) {
                    return -1;
                }

                if (interrogationMap[interrogationPosition.y]
                    [interrogationPosition.x + 1]
                    == 1) {
                    return -1;
                }

                interrogationPosition.x++;

                if (!interrogationReveal[interrogationPosition.y]
                [interrogationPosition.x]
                    && emotionAmount[2] > 0 && emotionAmount[2] > 0) {
                    emotionAmount[2]--;
                    emotionAmount[3]--;
                }
                break;

            case kCommandFire1:
                break;
            default:
                return -1;
        }
    }

    return -1;
}

void Interrogation_unloadStateCallback() {

    releaseBitmap(currentBackgroundBitmap);
    releaseBitmap(character);
    releaseBitmap(eyesL);
    releaseBitmap(eyesR);
    releaseBitmap(eyesW);
    releaseBitmap(eyesB);
    releaseBitmap(eyesC);
}
