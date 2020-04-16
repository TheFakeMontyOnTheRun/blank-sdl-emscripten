#include <conio.h>
#include <dpmi.h>
#include <go32.h>
#include <pc.h>
#include <bios.h>
#include <sys/movedata.h>
#include <sys/farptr.h>
#include <sys/nearptr.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#include "Enums.h"
#include "FixP.h"
#include "Common.h"
#include "CPackedFileReader.h"

#include "Engine.h"
#include "LoadBitmap.h"
#include "CRenderer.h"

enum EColor {
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_RED,
    COLOR_MAGENTA,
    COLOR_BROWN,
    COLOR_LIGHT_GRAY,
    COLOR_DARK_GRAY,
    COLOR_LIGHT_BLUE,
    COLOR_LIGHT_GREEN,
    COLOR_LIGHT_CYAN,
    COLOR_LIGHT_RED,
    COLOR_LIGHT_MAGENTA,
    COLOR_YELLOW,
    COLOR_WHITE,
};

long frame = 0;

void graphicsShutdown() {

    textmode(C80);
    clrscr();
    printf(
            "Thanks for playing!\nDOS is back with a vengeance.\n\nSource code and "
            "licenses:\nhttps://bitbucket.org/MontyOnTheRun/the-mistral-report\n\n");
}

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
    textmode(C80);
    clrscr();

    __dpmi_regs reg;

    reg.x.ax = 0x13;
    __dpmi_int(0x10, &reg);

    outp(0x03c8, 0);

    for (int r = 0; r < 4; ++r) {
        for (int g = 0; g < 8; ++g) {
            for (int b = 0; b < 8; ++b) {
                outp(0x03c9, (r * (16)));
                outp(0x03c9, (g * (8)));
                outp(0x03c9, (b * (8)));
            }
        }
    }

    defaultFont = loadBitmap("font.img");
}

void handleSystemEvents() {

    int lastKey = 0;

    if (kbhit()) {
        char getched = getch();
        switch (getched) {
            case 'c':
                mBufferedCommand = kCommandFire3;
                break;

            case 27:
            case 'q':
                mBufferedCommand = kCommandBack;
                break;

            case 's':
                mBufferedCommand = kCommandStrafeLeft;
                break;
            case 'd':
                mBufferedCommand = kCommandStrafeRight;
                break;

            case 13:
            case 'z':
                mBufferedCommand = kCommandFire1;
                break;

            case 'x':
            case ' ':
                mBufferedCommand = kCommandFire2;
                break;

            case 224:
            case 0: {
                char arrow = getch();
                switch (arrow) {
                    case 75:
                        mBufferedCommand = kCommandLeft;
                        break;
                    case 72:
                        mBufferedCommand = kCommandUp;
                        break;
                    case 77:
                        mBufferedCommand = kCommandRight;
                        break;
                    case 80:
                        mBufferedCommand = kCommandDown;
                        break;
                }
            }
                break;
        }
    }
}

void flipRenderer() {
    dosmemput(&framebuffer[0], 320 * 200, 0xa0000);
}

void clear() {}
