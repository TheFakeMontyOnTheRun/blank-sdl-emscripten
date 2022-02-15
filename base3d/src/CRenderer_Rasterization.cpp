#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "FixP.h"
#include "Enums.h"
#include "Common.h"
#include "LoadBitmap.h"
#include "Engine.h"
#include "CRenderer.h"

void drawRect(
        const int16_t x,
        const int16_t y,
        const uint16_t dx,
        const uint16_t dy,
        const uint8_t pixel) {

    uint8_t *destination = &framebuffer[0];
    uint8_t *destinationLineStart = destination + (640 * (y)) + x;
    int16_t py;

    if (pixel == TRANSPARENCY_COLOR) {
        return;
    }

    memset (destinationLineStart, pixel, dx);

    for (py = 0; py < (dy); ++py) {
        destinationLineStart = destination + (640 * (y + py)) + x;
        *destinationLineStart = pixel;
        destinationLineStart += dx;
        *destinationLineStart = pixel;
    }
    memset (destination + (640 * (y + dy)) + x, pixel, dx);
}

void fill(
        const int16_t x,
        const int16_t y,
        const int16_t dx,
        const int16_t dy,
        const uint8_t pixel,
        const bool stipple) {

    uint8_t *destination = &framebuffer[0];
    int16_t py;

    if (pixel == TRANSPARENCY_COLOR) {
        return;
    }

    for (py = 0; py < dy; ++py) {
        uint8_t *destinationLineStart = destination + (640 * (y + py)) + x;

        if (!stipple) {
            memset (destinationLineStart, pixel, dx);
        } else {
            int16_t px;
            for (px = 0; px < dx; ++px) {
                destinationLineStart++;
                if ((px + py) & 1) {
                    *destinationLineStart = pixel;
                }
            }
        }
    }
}

void drawBitmap(const int16_t dx,
                const int16_t dy,
                const struct Bitmap *__restrict__ tile,
                const bool transparent) {

    uint8_t *destination = &framebuffer[0];
    uint8_t *sourceLine = tile->data;
    size_t height = tile->height;
    size_t width = tile->width;
    size_t y;

    if ((dy + height) >= 480) {
        height = (480 - dy);
    }


    if (transparent) {
        for (y = 0; y < height; ++y) {
            uint8_t *destinationLineStart = destination + (640 * (dy + y)) + dx;
            uint8_t *sourceLineStart = sourceLine + (width * y);
            size_t x;

            for (x = 0; x < width; ++x) {
                uint8_t pixel = *sourceLineStart;

                if (!transparent || (pixel != TRANSPARENCY_COLOR)) {
                    *destinationLineStart = pixel;
                }

                ++sourceLineStart;
                ++destinationLineStart;
            }
        }
    } else {
        for (y = 0; y < height; ++y) {
            uint8_t *destinationLineStart = destination + (640 * (dy + y)) + dx;
            uint8_t *sourceLineStart = sourceLine + (width * y);
            size_t x;

            for (x = 0; x < width; ++x) {
                *destinationLineStart = *sourceLineStart;
                ++sourceLineStart;
                ++destinationLineStart;
            }
        }
    }

}

void drawRepeatBitmap(
        const int16_t x,
        const int16_t y,
        const int16_t dx,
        const int16_t dy,
        const struct Bitmap *__restrict__ tile) {

	int16_t repeatX;
	int16_t repeatY;
    uint16_t px, py;

	py = y;
    repeatY = dy;
    while (repeatY > 0) {
    	repeatX = dx;
		px = x;
    	while (repeatX > 0 ) {
			repeatX -= tile->width;

			if (px < 640 && py < 480) {
				drawBitmap(px, py, tile, false);
			}

			px += tile->width;
    	}
		py += tile->height;
		repeatY -= tile->height;
    }
}

void drawTextAt(const uint16_t x, const uint16_t y, const char *__restrict__ text, const uint8_t colour) {

    size_t len = strlen(text);
    int32_t dstX = (x - 1) * 8;
    int32_t dstY = (y - 1) * 8;
    uint8_t *dstBuffer = &framebuffer[0];
    size_t fontWidth = defaultFont->width;
    uint8_t *fontPixelData = defaultFont->data;
    size_t c;
    int32_t srcX, srcY;

    for (c = 0; c < len; ++c) {
        uint8_t ascii = text[c] - ' ';
        uint8_t line = ascii >> 5;
        uint8_t col = ascii & 31;
        uint8_t *letter =
                fontPixelData + (col * 8) + (fontWidth * (line * 8));

        if (text[c] == '\n' || dstX >= 640) {
            dstX = (x - 1) * 8;
            dstY += 8;
            continue;
        }

        if (text[c] == ' ') {
            dstX += 8;
            continue;
        }

        for (srcY = 0; srcY < 8; ++srcY) {

            uint8_t *letterSrc = letter + (fontWidth * srcY);
            uint8_t *letterDst = dstBuffer + dstX + (640 * (dstY + srcY));

            for (srcX = 0; srcX < 8; ++srcX) {

                if ((*letterSrc) != TRANSPARENCY_COLOR) {
                    *letterDst = colour;
                }

                ++letterSrc;
                ++letterDst;
            }
        }
        dstX += 8;
    }
}
