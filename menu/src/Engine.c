#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "SpyTravel.h"
#include "FixP.h"
#include "Vec.h"
#include "Enums.h"
#include "CActor.h"
#include "MapWithCharKey.h"
#include "Common.h"
#include "LoadBitmap.h"
#include "Engine.h"
#include "CTile3DProperties.h"
#include "CRenderer.h"
#include "VisibilityStrategy.h"
#include "CPackedFileReader.h"

char textBuffer[40 * 25];

InitStateCallback initStateCallback = NULL;
InitialPaintCallback initialPaintCallback = NULL;
RepaintCallback repaintCallback = NULL;
TickCallback tickCallback = NULL;
UnloadStateCallback unloadStateCallback = NULL;

extern long timeUntilNextState;
extern enum EPresentationState currentPresentationState;
extern const char *mainText;
extern int32_t currentGameMenuState;

int countLines() {
    int len = strlen(mainText);
    int lines = 2; //initial line + final line must be accounted for
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

void enterState(int newState) {

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
        case kPassTurn: {
            if (mapGameTick() == -1) {
                enterState(kGameOver);
            } else {
                enterState(kGameMenu);
            }
            return;
        } /* this has to fall thru to kPlayGame, so we continue playing */
            break;
        case kPlayGame:
            initSpyGame();
        case kGameMenu:
            menuStateToReturn = kGameMenu;

        case kTravelPorto:
        case kTravelLisbon:
        case kTravelMadrid:
        case kTravelBarcelona:
        case kTravelFrankfurt:
        case kTravelHamburg:
        case kTravelLuxembourg:
        case kTravelBrussels:
            newState = kGameMenu;
        case kStatusMenu:
        case kTravelMenu:
        case kDossiersMenu:
        case kAccuseMenu:
        case kReadDossier_Sofia:
        case kReadDossier_Ricardo:
        case kReadDossier_Lola:
        case kReadDossier_Pau:
        case kReadDossier_Lina:
        case kReadDossier_Elias:
        case kReadDossier_Carmen:
        case kVictory:
        case kGameOver:
        case kEpilogue:
        case kReadDossier_Jean:
            initStateCallback = GameMenu_initStateCallback;
            initialPaintCallback = GameMenu_initialPaintCallback;
            repaintCallback = GameMenu_repaintCallback;
            tickCallback = GameMenu_tickCallback;
            unloadStateCallback = GameMenu_unloadStateCallback;
            break;

        case kAccuse_Sofia:
        case kAccuse_Ricardo:
        case kAccuse_Lola:
        case kAccuse_Pau:
        case kAccuse_Lina:
        case kAccuse_Elias:
        case kAccuse_Carmen:
        case kAccuse_Jean:
            if (accuse(newState - kAccuse_Sofia) /*&& isBanditPresent()*/ ) {
                enterState(kVictory);
                return;
            } else {
                enterState(kGameOver);
                return;
            }
        case kPracticeCrawling:
            initSpyGame();
        case kPrologue:
            menuStateToReturn = kMainMenu;
            initStateCallback = Crawler_initStateCallback;
            initialPaintCallback = Crawler_initialPaintCallback;
            repaintCallback = Crawler_repaintCallback;
            tickCallback = Crawler_tickCallback;
            unloadStateCallback = Crawler_unloadStateCallback;
            break;
        case kPracticeInterrogation:
        case kInterrogate_Sofia:
        case kInterrogate_Ricardo:
        case kInterrogate_Lola:
        case kInterrogate_Pau:
        case kInterrogate_Lina:
        case kInterrogate_Jean:
        case kInterrogate_Elias:
        case kInterrogate_Carmen:
            menuStateToReturn = kMainMenu;
            initStateCallback = Interrogation_initStateCallback;
            initialPaintCallback = Interrogation_initialPaintCallback;
            repaintCallback = Interrogation_repaintCallback;
            tickCallback = Interrogation_tickCallback;
            unloadStateCallback = Interrogation_unloadStateCallback;
            break;

        case kInvestigateMenu: {

            if (isSuspectAlive() && hasGivenClue(getPlayerLocation())) {
                getClue();
                enterState(kReadDossier_Sofia + getPlayerLocation());
                return;
            }

            menuStateToReturn = kMainMenu;
            initStateCallback = Crawler_initStateCallback;
            initialPaintCallback = Crawler_initialPaintCallback;
            repaintCallback = Crawler_repaintCallback;
            tickCallback = Crawler_tickCallback;
            unloadStateCallback = Crawler_unloadStateCallback;
        }
            break;
        case kQuit:
            isRunning = FALSE;
            break;
        case kEndGame:
            menuStateToReturn = kGameMenu;
            initStateCallback = GameMenu_initStateCallback;
            initialPaintCallback = GameMenu_initialPaintCallback;
            repaintCallback = GameMenu_repaintCallback;
            tickCallback = GameMenu_tickCallback;
            unloadStateCallback = GameMenu_unloadStateCallback;
            break;
    }

    currentGameMenuState = newState;
    initStateCallback(newState, NULL);
    initialPaintCallback();
}

enum ESoundDriver soundDriver = kNoSound;

int menuTick(long delta_time) {

    enum ECommand input;
    int32_t newState;

    handleSystemEvents();

    if (soundDriver != kNoSound) {
        soundTick();
    }

    /* protect against machines too fast for their own good. */
    if (delta_time <= 0) {
        delta_time = 1;
    }

    input = getInput();

    newState = tickCallback(input, &delta_time);

    if (input == kCommandQuit) {
        return FALSE;
    }

    if (newState != currentGameMenuState && newState != -1) {
        playSound(STATE_CHANGE_SOUND);
        enterState(newState);
    }

    repaintCallback();
    flipRenderer();

    return TRUE;
}
