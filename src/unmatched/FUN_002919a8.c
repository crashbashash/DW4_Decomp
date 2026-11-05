/* 0x002919a8 — FUN_002919a8 (76 bytes). Reports the picture size (+8, +12) and derived values: half the width rounded up to a multiple of 32, and half the height. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

struct Picture002919a8 {
    int f0, f4;
    int width;  /* +8 */
    int height; /* +12 */
};

void FUN_002919a8(struct Picture002919a8 *picture, int *width, int *height, int *halfWidthAligned, int *halfHeight) {
    int w = picture->width;
    int h = picture->height;

    *halfWidthAligned = (w / 2 + 31) / 32 * 32;
    *halfHeight = h / 2;
    *width = w;
    *height = h;
}
