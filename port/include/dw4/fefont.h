/* dw4/fefont.h -- the front-end's own text: `bectext.igb`'s bitmap font.
 *
 * The engine generates its menu strings from a bitmap font, not from a font in the OS: `NDMW.AFS`
 * entry 79 (`bectext.igb`) holds an `igImage` (`font00.png`, a 512x512 8-bit grid + a 256-entry
 * `igClut`) and two `igCharMetricsList`s (484 glyphs each: the `NORMAL` and `MINIMUM` faces).  This
 * decodes them natively from the disc -- the same offline route the texture packs use (the pool is
 * the pack's id remap table + block offsets) -- so the port draws the game's
 * text instead of its diagnostic 5x7 readout font.
 *
 * All geometry is in the font's own units: a glyph's quad is its atlas texel rectangle, and the pen
 * advances by the metric's `advance`.  `scale` is a single multiplier (1.0 draws the glyph at the
 * atlas' own resolution, ~26 px tall for the NORMAL face).
 */
#ifndef DW4_FEFONT_H
#define DW4_FEFONT_H

#include <stdint.h>
#include "dw4/render.h"
#include "dw4/mount.h"
#include "dw4/igb.h"

typedef struct {
    float advance;      /* pen advance, font units */
    float bx, by;       /* glyph bearing relative to the pen origin */
    float w, h;         /* glyph box, font units */
    float u0, v0, u1, v1;  /* the glyph's rect in the 512x512 atlas, normalised */
} dw4_glyph;

typedef struct {
    int         have;
    uint8_t    *atlas;  /* aw*ah*4 RGBA, top row first (linear palette) */
    int         aw, ah;
    int         nglyph;
    dw4_glyph   glyph[256];   /* indexed by character code (ASCII range used) */
    char        name[64];     /* the atlas image's own name ("font00.png") */
    dw4_glyph  *all;          /* every metric record (codes are Unicode-like, icons included) */
    uint32_t   *allcode;
    int         nall;
    float       height, baseline; /* named face metadata, in font units */
} dw4_fefont;

/* Load `bectext.igb` from `<roms>/NDMW.AFS` and decode the NORMAL face.  Returns 0, or -1. */
int  dw4_fefont_load(dw4_fefont *f, const char *roms);
/* Decode the selected beFontImage through its metrics/texture/image references. */
int dw4_fefont_decode(dw4_fefont *, const dw4_igb *, uint32_t id);
/* Load a named through an already-mounted archive. */
int dw4_fefont_load_face(dw4_fefont *, const dw4_mount *, const char *face);
void dw4_fefont_free(dw4_fefont *f);

/* Measure `text` in pixels at `scale` (pen advance summed, box height = the metric height). */
void dw4_fefont_size(const dw4_fefont *f, const char *text, float scale, float *w, float *h);

/* Draw `text` with its top-left box corner at (x, y) in screen pixels, in `rgba` (0..128, as the GS
 * stores a vertex colour; 128 = full).  Alpha-blended (the GS ALPHA 0x44 blend) with the decoded
 * atlas as the glyph texture.  Returns the number of quads drawn. */
int  dw4_fefont_draw(dw4_fb *fb, const dw4_fefont *f, float x, float y, float scale,
                     const char *text, const uint8_t rgba[3][4]);
struct dw4_gl_layer;
/* Same legacy glyph geometry, submitted as one ordered GPU batch. */
int dw4_fefont_draw_gpu(struct dw4_gl_layer *,dw4_fb *,const dw4_fefont *,float,float,float,
    const char *,const uint8_t [3][4]);

/* One glyph by its font code (ASCII, or an icon such as 8801/8711/8811/8810 on the Option screen's legend).
 * NULL when the font has none. */
const dw4_glyph *dw4_fefont_glyph(const dw4_fefont *f, uint32_t code);

/* The screen quad of glyph `code` with the pen at (x, y) at `scale`: its box, its atlas rectangle and the
 * pen advance (all in pixels / normalised UV).  Returns 0, or -1 when the font has no such glyph. */
int dw4_fefont_quad(const dw4_fefont *f, uint32_t code, float x, float y, float scale,
                    float box[4], float uv[4], float *advance);

#endif /* DW4_FEFONT_H */
