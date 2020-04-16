#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "Enums.h"
#include "FixP.h"
#include "LoadBitmap.h"
#include "Common.h"
#include "CPackedFileReader.h"
#include "CRenderer.h"
#include "Engine.h"
#include "FixP.h"

FixP_t lerpFix(const FixP_t v0, const FixP_t v1, const FixP_t dt, const FixP_t total) {
    FixP_t delta = (v1 - v0);
    FixP_t progress = Div(dt, total);
    FixP_t reach = Mul(delta, progress);

    return (v0 + reach);
}

int lerpInt(const int v0, const int v1, const long t, const long total) {
    return fixToInt(lerpFix(intToFix(v0), intToFix(v1), intToFix(t),
                            intToFix(total)));
}

struct Bitmap *loadBitmap(const char *__restrict__ filename) {
    int c, d = 0;
    uint8_t pixel;
    uint8_t repetitions;

    struct Bitmap *toReturn =
            (struct Bitmap *) calloc(1, sizeof(struct Bitmap));

    FILE *src = openBinaryFileFromPath(filename);
    size_t size;
    size_t sizeInDisk = sizeOfFile(filename) - 4;
    int pixelIndex = 0;
    uint8_t *buffer;
    uint8_t width = 0;
    uint8_t height = 0;

    toReturn->width = 0;
    assert (fread(&width, 1, 1, src));
    toReturn->width += (width & 0xFF) << 8;
    assert (fread(&width, 1, 1, src));
    toReturn->width += width & 0xFF;

    toReturn->height = 0;
    assert (fread(&height, 1, 1, src));
    toReturn->height += (height & 0xFF) << 8;
    assert (fread(&height, 1, 1, src));
    toReturn->height += height & 0xFF;

    size = toReturn->width * toReturn->height;
    buffer = (uint8_t *) calloc(1, sizeInDisk);

    assert (fread(&buffer[0], sizeInDisk, 1, src));

    toReturn->data = (uint8_t *) calloc(1, size);

    for (c = 0; c < sizeInDisk; c += 2) {
        pixel = buffer[c];
        repetitions = buffer[c + 1];

        for (d = 0; d < repetitions; ++d) {
            toReturn->data[pixelIndex++] = pixel;
        }
    }

    free(buffer);

    fclose(src);

    return toReturn;
}

void releaseBitmap(struct Bitmap *__restrict__ ptr) {
    assert (ptr != NULL);

    free(ptr->data);
    free(ptr);
}
