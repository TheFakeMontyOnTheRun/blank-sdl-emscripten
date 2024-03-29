#include <jni.h>
#include <string.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "Common.h"
#include "Enums.h"
#include "FixP.h"
#include "LoadBitmap.h"
#include "Engine.h"
#include "CRenderer.h"
#include "FixP.h"
#include "Enums.h"
#include "Common.h"
#include "LoadBitmap.h"
#include "Engine.h"
#include "CRenderer.h"
#include "CPackedFileReader.h"

int isInstantApp = FALSE;
long t0, t1, t2;

void initHW(void);

void enterState(enum EGameMenuState newState);

void mainLoop(void);

extern int currentGameMenuState;

uint8_t framebufferFinal[320 * 240 * 4];

AAssetManager *defaultAssetManager = NULL;


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

void graphicsInit(void) {
    int r, g, b;

    for (r = 0; r < 256; r += 16) {
        for (g = 0; g < 256; g += 8) {
            for (b = 0; b < 256; b += 8) {
                uint32_t pixel = 0xFF000000 + (r << 16) + (g << 8) + (b);
                uint8_t paletteEntry = getPaletteEntry(pixel);
                palette[paletteEntry] = pixel;
            }
        }
    }

    defaultFont = loadBitmap("font.img");
}

void handleSystemEvents(void) {

}

void graphicsShutdown(void) {
    releaseBitmap(defaultFont);
}

void flipRenderer(void) {
    unsigned char *ptr = &framebufferFinal[0];

    memset(ptr, 0, 320 * 240 * 4);

    for (int y = 0; y < 240; ++y) {
        for (int x = 0; x < 320; ++x) {

            int32_t pixel = palette[framebuffer[(int)(320 * ((200 * y) / 240 )) + x]];

            int r = (pixel & 0x000000FF) - 0x38;
            int g = ((pixel & 0x0000FF00) >> 8) - 0x18;
            int b = ((pixel & 0x00FF0000) >> 16) - 0x10;


            *ptr = r;
            ++ptr;
            *ptr = g;
            ++ptr;
            *ptr = b;
            ++ptr;
            *ptr = 255;
            ++ptr;

        }
    }
}

void clearRenderer(void) {}

JNIEXPORT void JNICALL
Java_pt_b13h_blank_JNIGlue_initAssets(JNIEnv *env, jclass clazz,
                                                    jobject assetManager) {

    AAssetManager *asset_manager = AAssetManager_fromJava(env, assetManager);
    defaultAssetManager = asset_manager;
    srand(time(NULL));
    initHW();
#ifndef INSTANT_APP
    enterState(kMainMenu);
#else
    enterState(kPracticeCrawling);
#endif
}

JNIEXPORT void JNICALL
Java_pt_b13h_blank_JNIGlue_getPixelsFromNative(JNIEnv *env, jclass clazz,
                                                             jbyteArray array) {
    mainLoop();
    jbyte *narr = (*env)->GetByteArrayElements(env, array, NULL);
    memcpy(narr, &framebufferFinal[0], 320 * 240 * 4);
}

int soundToPlay = -1;

void setupOPL2(int port) {}

void stopSounds() {}

void playSound(const int action) {
    soundToPlay = action;
}

void soundTick() {}

void muteSound() {}

    JNIEXPORT jint JNICALL
    Java_pt_b13h_blank_JNIGlue_getSoundToPlay(JNIEnv *env, jclass clazz) {
    int toReturn = soundToPlay;
    soundToPlay = -1;
    return toReturn;
}

    JNIEXPORT jint JNICALL
    Java_pt_b13h_blank_JNIGlue_isOnMainMenu(JNIEnv *env, jclass clazz) {
    return currentGameMenuState == (kMainMenu);
}

JNIEXPORT void JNICALL
    Java_pt_b13h_blank_JNIGlue_sendCommand(JNIEnv *env, jclass clazz, jchar cmd) {
    switch (cmd) {
        case 'w':
            mBufferedCommand = kCommandUp;
            break;

        case 's':
            mBufferedCommand = kCommandDown;
            break;

        case 'z':
            mBufferedCommand = kCommandFire1;
            break;


        case 'x':
            mBufferedCommand = kCommandFire2;
            break;

        case 'c':
            mBufferedCommand = kCommandFire3;
            break;

        case 'a':
            mBufferedCommand = kCommandLeft;
            break;


        case 'd':
            mBufferedCommand = kCommandRight;
            break;

        case 'q':
            mBufferedCommand = kCommandBack;
            break;

        case 'n':
            mBufferedCommand = kCommandStrafeLeft;
            break;

        case 'm':
            mBufferedCommand = kCommandStrafeRight;
            break;

        defaut:
            mBufferedCommand = kCommandNone;

    }
}