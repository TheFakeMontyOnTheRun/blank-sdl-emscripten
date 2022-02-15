#ifndef BITMAP_H
#define BITMAP_H

struct Bitmap {
    uint8_t *data;
    uint16_t width;
    uint16_t height;
};


struct Bitmap *loadBitmap(const char *__restrict__ filename);

void releaseBitmap(struct Bitmap *ptr);

FixP_t lerpFix(const FixP_t v0, const FixP_t v1, const FixP_t t, const FixP_t total);

int lerpInt(const int v0, const int v1, const long t, const long total);
#endif
