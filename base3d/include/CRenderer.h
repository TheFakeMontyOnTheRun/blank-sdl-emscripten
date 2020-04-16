#ifndef RENDERER_H
#define RENDERER_H

#define TRANSPARENCY_COLOR 199

extern struct Bitmap *defaultFont;
extern uint8_t framebuffer[320 * 200];
extern uint32_t palette[256];
extern enum ECommand mBufferedCommand;

void graphicsInit();

void graphicsShutdown();

void flipRenderer();

enum ECommand getInput();

void handleSystemEvents();

uint8_t getPaletteEntry(const uint32_t origin);

void fill(
        const int16_t x, const int16_t y,
        const int16_t dx, const int16_t dy,
        const uint8_t pixel, const int stipple);

void drawTextAt(const uint16_t x,
                const uint16_t y,
                const char *__restrict__ text,
                const uint8_t colour);

void drawBitmap(const int16_t x,
                const int16_t y,
                const struct Bitmap *__restrict__ tile,
                const int transparent);

void drawRepeatBitmap(
        const int16_t x,
        const int16_t y,
        const int16_t dx,
        const int16_t dy,
        const struct Bitmap *__restrict__ tile);

void drawRect(const int16_t x,
              const int16_t y,
              const uint16_t dx,
              const uint16_t dy,
              const uint8_t pixel);

void drawMask(const FixP_t x0,
              const FixP_t y0,
              const FixP_t x1,
              const FixP_t y1);

#endif
