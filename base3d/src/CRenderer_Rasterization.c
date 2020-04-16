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

#define mTransparency 199


void drawRect(
        const int16_t x,
        const int16_t y,
        const uint16_t dx,
        const uint16_t dy,
        const uint8_t pixel) {

    uint8_t *destination = &framebuffer[0];
    uint8_t *destinationLineStart = destination + (320 * (y)) + x;
    int16_t py;

    if (pixel == mTransparency) {
        return;
    }

    memset (destinationLineStart, pixel, dx);

    for (py = 0; py < (dy); ++py) {
        destinationLineStart = destination + (320 * (y + py)) + x;
        *destinationLineStart = pixel;
        destinationLineStart += dx;
        *destinationLineStart = pixel;
    }
    memset (destination + (320 * (y + dy)) + x, pixel, dx);
}

void fill(
        const int16_t x,
        const int16_t y,
        const int16_t dx,
        const int16_t dy,
        const uint8_t pixel,
        const int stipple) {

    uint8_t *destination = &framebuffer[0];
    int16_t py;

    if (pixel == mTransparency) {
        return;
    }

    for (py = 0; py < dy; ++py) {
        uint8_t *destinationLineStart = destination + (320 * (y + py)) + x;

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
                const int transparent) {

    uint8_t *destination = &framebuffer[0];
    uint8_t *sourceLine = tile->data;
    size_t height = tile->height;
    size_t width = tile->width;
    size_t y;

    if ((dy + height) >= 200) {
        height = (200 - dy);
    }


    if (transparent) {
        for (y = 0; y < height; ++y) {
            uint8_t *destinationLineStart = destination + (320 * (dy + y)) + dx;
            uint8_t *sourceLineStart = sourceLine + (width * y);
            size_t x;

            for (x = 0; x < width; ++x) {
                uint8_t pixel = *sourceLineStart;

                if (!transparent || (pixel != mTransparency)) {
                    *destinationLineStart = pixel;
                }

                ++sourceLineStart;
                ++destinationLineStart;
            }
        }
    } else {
        for (y = 0; y < height; ++y) {
            uint8_t *destinationLineStart = destination + (320 * (dy + y)) + dx;
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

    size_t repeatX = (dx / tile->width) + 1;
    size_t repeatY = (dy / tile->height) + 1;
    size_t c, d;
    for (c = 0; c < repeatY; ++c) {
        for (d = 0; d < repeatX; ++d) {

            size_t px = d * tile->width;
            size_t py = c * tile->height;

            if (px < 320 && py < 200) {
                drawBitmap(px, py, tile, FALSE);
            }
        }
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

        if (text[c] == '\n' || dstX >= 320) {
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
            uint8_t *letterDst = dstBuffer + dstX + (320 * (dstY + srcY));

            for (srcX = 0; srcX < 8; ++srcX) {

                if ((*letterSrc) != mTransparency) {
                    *letterDst = colour;
                }

                ++letterSrc;
                ++letterDst;
            }
        }
        dstX += 8;
    }
}
