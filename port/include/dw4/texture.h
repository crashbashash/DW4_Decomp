/* dw4/texture.h — indexed texture decode.
 *
 * The fields are the recovered `igImage`/`igClut` ones (data/reflection.json):
 *
 *   igImage._px/_py        width / height
 *   igImage._bitsIdx       bits per index (8 or 4)
 *   igImage._bytesPerRow   the packed row stride in the source
 *   igImage._pImage        the index buffer (a memory ref)
 *   igImage._pClut         the palette object
 *   igClut._numEntries     palette size
 *   igClut._pData          the palette bytes
 *
 * What this module canNOT do is find those buffers: a memory ref is a load-time ordinal
 * (finding #433), so the bytes have to come from the loader's own replay or a live
 * session.  Decoding them is well defined, and that half is here.
 */
#ifndef DW4_TEXTURE_H
#define DW4_TEXTURE_H

#include <stdint.h>

typedef enum {
    DW4_PAL_RGBA8888 = 0,   /* four bytes per entry, memory order R,G,B,A */
    DW4_PAL_PS2_CSM1 = 1    /* u16 LE: A(15) B(14..10) G(9..5) R(4..0) */
} dw4_pal_mode;

/* Decode to `rgba` (w*h*4 bytes, row-major).  `bpr` is the source row stride in bytes;
 * pass 0 for the packed stride (w*bits/8 rounded up).  Returns 0 on success, -1 when a
 * read would leave `src` or `pal` (so a wrong guess fails instead of reading garbage). */
int dw4_texture_rgba(const uint8_t *src, uint32_t src_size, uint32_t w, uint32_t h,
                     int bits, uint32_t bpr,
                     const uint8_t *pal, uint32_t pal_size, uint32_t pal_entries,
                     dw4_pal_mode mode, uint8_t *rgba);

#endif /* DW4_TEXTURE_H */
