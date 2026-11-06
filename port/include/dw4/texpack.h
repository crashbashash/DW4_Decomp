/* dw4/texpack.h — texture-pack reader (the second pack kind in NDMW.AFS).
 *
 * A texture pack is a class directory, a string table, an id->class table, a stream of
 * serialised `igImage`/`igClut` objects and a flat pool holding every texture's index
 * grid and palette.  The layout is documented in
 * DW4_Decomp/docs/engine/texture-packs.md; the decoders it was recovered with are
 * DW4_Decomp/scripts/igb_texpack.py and verify_texpack_layout.py, and this is the port's
 * C reader for the same rules:
 *
 *   +0x00  u32[12] header      [6] = sum(block sizes) + 4*(nclut + 2)
 *                              [7] = nclut + nimg + 3
 *   +recs  igObject records    { u32 class, u32 bytes } then the fields at the offsets
 *                              data/reflection.json gives: class 10 = igImage
 *                              (_px +8, _py +12, _pfmt +44, _imageSize +48, _pImage +52,
 *                              _pClut +68, _bytesPerRow +76, _pNameString +88),
 *                              class 11 = igClut (_fmt +8, _numEntries +12, _stride +16,
 *                              _pData +20)
 *   +tbl   id -> class table   { u32 tableBytes, u32 idCount } then idCount u16; the
 *                              class numbering is pack-local and self-validating
 *   +pool  the blocks           in ascending id order, an image's grid one byte in
 *
 * The image -> palette link is `_pClut`'s rank among the ids of its class: the ids of a
 * class are in creation order (= file order), so that rank names the r-th igClut record,
 * whose `_pData` is the palette block.  No load replay is involved.
 */
#ifndef DW4_TEXPACK_H
#define DW4_TEXPACK_H

#include <stddef.h>
#include <stdint.h>

#include "dw4/texture.h"

#define DW4_TEXPACK_MAXTEX 512u
#define DW4_TEXPACK_POOLSZ 1024u   /* a clut block: 256 entries x 4 bytes */

typedef struct {
    char name[64];
    uint32_t image_id;          /* igImage._pImage — the grid block's id */
    uint32_t clut_id;           /* igClut._pData — the palette block's id */
    uint32_t rec_off;           /* the igImage record, in pack-relative bytes */
    uint32_t w, h;              /* igImage._px / _py */
    uint32_t grid_off;          /* grid block offset in the pack (data at +1) */
    uint32_t pal_off;           /* palette block offset in the pack */
} dw4_texpack_tex;

typedef struct {
    const uint8_t *b;           /* borrowed: the whole pack */
    size_t len;
    uint32_t pool_base, pool_end;
    uint32_t nclut, nimg, npad;
    uint32_t tbl_off, tbl_count;
    uint32_t block_class, obj_class;
    dw4_texpack_tex tex[DW4_TEXPACK_MAXTEX];
    uint32_t ntex;
} dw4_texpack;

/* Parse a texture pack.  Returns 0 on success, -1 when the header does not describe a
 * pool or the id->class table does not validate (a multi-asset pack), so a caller never
 * gets half-believed offsets.  `dw4_texpack_close` is a no-op on a borrow this way; call
 * it anyway so the ownership rule can change. */
int dw4_texpack_open(dw4_texpack *tp, const uint8_t *b, size_t len);
void dw4_texpack_close(dw4_texpack *tp);

const dw4_texpack_tex *dw4_texpack_find(const dw4_texpack *tp, const char *name);

/* Decode one texture to `rgba` (w*h*4 bytes, row-major, top row first).  The stored grid
 * is bottom-up and an image block's data starts one byte in; the palette is 4 bytes per
 * entry and the RGB lives in bytes 1..3 (entry 0's alpha is unreliable — it is the
 * previous block's last byte).  Returns 0, or -1 when the ids are not in the layout. */
int dw4_texpack_rgba(const dw4_texpack *tp, uint32_t image_id, uint32_t clut_id,
                     uint8_t *rgba);

#endif /* DW4_TEXPACK_H */
