/* texture.c — indexed texture decode.  See dw4/texture.h. */
#include "dw4/texture.h"

#include <string.h>

static void pal_lookup(const uint8_t *pal, uint32_t pal_size, uint32_t entries,
                       dw4_pal_mode mode, uint32_t index, uint8_t out[4])
{
    if (mode == DW4_PAL_PS2_CSM1) {
        const uint8_t *e = pal + index * 2;
        uint32_t v;
        if (e + 2 > pal + pal_size) {
            out[0] = out[1] = out[2] = 0;
            out[3] = 255;
            return;
        }
        v = (uint32_t)e[0] | ((uint32_t)e[1] << 8);
        out[0] = (uint8_t)(((v >> 0) & 0x1f) * 255 / 31);
        out[1] = (uint8_t)(((v >> 5) & 0x1f) * 255 / 31);
        out[2] = (uint8_t)(((v >> 10) & 0x1f) * 255 / 31);
        out[3] = (v & 0x8000) ? 255 : 0;
        return;
    }
    {
        const uint8_t *e = pal + index * 4;
        if (e + 4 > pal + pal_size) {
            out[0] = out[1] = out[2] = 0;
            out[3] = 255;
            return;
        }
        memcpy(out, e, 4);
    }
    (void)entries;
}

int dw4_texture_rgba(const uint8_t *src, uint32_t src_size, uint32_t w, uint32_t h,
                     int bits, uint32_t bpr,
                     const uint8_t *pal, uint32_t pal_size, uint32_t pal_entries,
                     dw4_pal_mode mode, uint8_t *rgba)
{
    uint32_t x, y, packed;

    if (bits != 8 && bits != 4)
        return -1;
    if (!w || !h)
        return -1;
    packed = (w * (uint32_t)bits + 7) / 8;
    if (!bpr)
        bpr = packed;
    if (bpr < packed)
        return -1;
    if ((uint64_t)bpr * h > src_size)
        return -1;
    if (!pal_entries)
        return -1;
    if (mode == DW4_PAL_PS2_CSM1 ? (uint64_t)pal_entries * 2 > pal_size
                                 : (uint64_t)pal_entries * 4 > pal_size)
        return -1;

    for (y = 0; y < h; y++) {
        const uint8_t *row = src + (uint64_t)y * bpr;
        for (x = 0; x < w; x++) {
            uint32_t index;
            uint8_t c[4];
            if (bits == 8) {
                index = row[x];
            } else {
                uint8_t b = row[x >> 1];
                index = (x & 1) ? (b & 0x0f) : (b >> 4);
            }
            pal_lookup(pal, pal_size, pal_entries, mode, index, c);
            memcpy(rgba + ((uint64_t)y * w + x) * 4, c, 4);
        }
    }
    return 0;
}
