/* dw4/fetext.h -- the front-end font's glyph quads as screen draws (shared by the Option and slot screens).
 *
 * A line is anchored by its first glyph's quad (left, top) in the 640x448 frame; the draws are the real
 * screen's own (ALPHA 0x44, AREF 12, vertex colour 0.9/0.95).
 */
#ifndef DW4_FETEXT_H
#define DW4_FETEXT_H

#include "dw4/fefont.h"
#include "dw4/render.h"

typedef struct {
    dw4_ui_draw **dl;
    int *n, *cap;
    const dw4_fefont *font;
    dw4_tex atlas;
    float s, cx, w640;
    float sx;                    /* the horizontal position scale when it differs from `s` (0 = same) */
    float gs;                    /* glyph scale when it differs from the position scale `s` (0 = same) */
} dw4_fetext;

/* A run of glyph codes whose first quad's top-left is (left, top) in 640x448 pixels. */
void dw4_fetext_codes(dw4_fetext *t, const uint32_t *codes, int nc, float left, float top);
void dw4_fetext_str(dw4_fetext *t, const char *str, float left, float top);
/* The same, centred on x = `centre` (640x448) with the glyph tops at `top`. */
void dw4_fetext_centred(dw4_fetext *t, const char *str, float centre, float top);

#endif /* DW4_FETEXT_H */
