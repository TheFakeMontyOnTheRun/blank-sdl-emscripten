#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>


#ifndef __DJGPP__
const long UCLOCKS_PER_SEC = 1000;

long timeEllapsed = 0;

long uclock() {
    timeEllapsed += (1000 / 60);
    return timeEllapsed;
}

#endif

#include "FixP.h"
#include "Enums.h"
#include "Common.h"
#include "LoadBitmap.h"
#include "Engine.h"
#include "CRenderer.h"
#include "CPackedFileReader.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>
#include <emscripten/emscripten.h>
#endif

void initHW();

void shutdownHW();

char textBuffer[40 * 25];
extern int isRunning;
InitStateCallback initStateCallback = NULL;
InitialPaintCallback initialPaintCallback = NULL;
RepaintCallback repaintCallback = NULL;
TickCallback tickCallback = NULL;
UnloadStateCallback unloadStateCallback = NULL;

extern long timeUntilNextState;
extern enum EPresentationState currentPresentationState;
extern struct Bitmap *currentBackgroundBitmap;
extern uint8_t cursorPosition;
extern int32_t nextNavigationSelection;
extern int32_t currentGameMenuState;
extern const char *mainText;

int countLines() {
    int len = strlen(mainText);
    int lines = 2; /* initial line + final line must be accounted for */
    int charsInLine = 0;
    int c = 0;
    for (c = 0; c < len; ++c) {
        if (mainText[c] == '\n') {
            lines++;
            charsInLine = 0;
        } else {
            charsInLine++;
        }
    }

    return lines - 1;
}

void enterState(enum EGameMenuState newState) {

    if (unloadStateCallback != NULL) {
        unloadStateCallback();
    }

    timeUntilNextState = MENU_ITEM_TIME_TO_BECOME_ACTIVE_MS;
    currentPresentationState = kAppearing;
    currentBackgroundBitmap = NULL;
    cursorPosition = 0;
    nextNavigationSelection = -1;

    switch (newState) {
        default:
        case kMainMenu:
            initStateCallback = MainMenu_initStateCallback;
            initialPaintCallback = MainMenu_initialPaintCallback;
            repaintCallback = MainMenu_repaintCallback;
            tickCallback = MainMenu_tickCallback;
            unloadStateCallback = MainMenu_unloadStateCallback;
            break;
        case kHelp:
            initStateCallback = HelpScreen_initStateCallback;
            initialPaintCallback = HelpScreen_initialPaintCallback;
            repaintCallback = HelpScreen_repaintCallback;
            tickCallback = HelpScreen_tickCallback;
            unloadStateCallback = HelpScreen_unloadStateCallback;
            break;
        case kCredits:
            initStateCallback = CreditsScreen_initStateCallback;
            initialPaintCallback = CreditsScreen_initialPaintCallback;
            repaintCallback = CreditsScreen_repaintCallback;
            tickCallback = CreditsScreen_tickCallback;
            unloadStateCallback = CreditsScreen_unloadStateCallback;
            break;

        case kInterrogate_Sofia:
            menuStateToReturn = kMainMenu;
            initStateCallback = Interrogation_initStateCallback;
            initialPaintCallback = Interrogation_initialPaintCallback;
            repaintCallback = Interrogation_repaintCallback;
            tickCallback = Interrogation_tickCallback;
            unloadStateCallback = Interrogation_unloadStateCallback;
            break;
        case kQuit:
            isRunning = FALSE;
            break;
    }

    currentGameMenuState = newState;
    initStateCallback(newState, NULL);
    initialPaintCallback();
}

void initHW() {
    initFileReader("base.pfs");
    graphicsInit();
}

void shutdownHW() {
    graphicsShutdown();
}

int start_clock, end_clock, prev;

void mainLoop() {
    long now, delta_time;
    enum ECommand input;
    int32_t newState;

    handleSystemEvents();
    now = (end_clock - start_clock) / (UCLOCKS_PER_SEC / 1000);
    delta_time = now - prev;
    prev = now;

    /* protect against machines too fast for their own good. */
    if (delta_time <= 0) {
        delta_time = 1;
    }
    input = getInput();

#ifdef ANDROID
    delta_time = 50;
#endif


#ifdef __EMSCRIPTEN__
    delta_time = 500;
#endif
    newState = tickCallback(input, &delta_time);

    if (input == kCommandQuit) {
        isRunning = FALSE;
    }

    if (newState != currentGameMenuState && newState != -1) {
        enterState(newState);
    }

    repaintCallback();
    flipRenderer();

    end_clock = uclock();
}

#ifndef ANDROID

int main(int argc, char **argv) {


    puts(
            "The Mistral Report - Invisible Affairs, 2018-2019 - by the Brotherhood "
            "of 13h");

    srand(time(NULL));
    initHW();
    enterState(kMainMenu);

    end_clock = uclock();
    prev = 0;

    start_clock = uclock();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, 1);
#else
    while (isRunning) {
        mainLoop();
    }
#endif
    unloadStateCallback();
    shutdownHW();

    return 0;
}

#endif
