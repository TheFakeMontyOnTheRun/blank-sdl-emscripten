#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#ifdef AMIGA
#include "AmigaInt.h"
#else

#include <stdint.h>
#include <unistd.h>

#endif

#include "FixP.h"
#include "Enums.h"
#include "Common.h"
#include "LoadBitmap.h"
#include "CRenderer.h"
#include "CPackedFileReader.h"

int cursorX = -1;
int cursorZ = -1;


struct Bitmap *defaultFont;
uint8_t framebuffer[320 * 200];
long gameTicks = 0;


struct Bitmap *backdrop = NULL;
uint32_t palette[256];
enum ECommand mBufferedCommand = kCommandNone;


enum ECommand getInput() {
	const enum ECommand toReturn = mBufferedCommand;
	mBufferedCommand = kCommandNone;
	return toReturn;
}
