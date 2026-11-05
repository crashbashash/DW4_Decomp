#include "dw4/fetext.h"

#include <stdlib.h>
#include <string.h>

/* --- the text: the front-end font's own glyph quads, at the positions the real screen's draws put them --
 * (ring of 82 quads in `option-screen/03-*.gs.zst`: ALPHA 0x44, AREF 12, vertex colour 0.9/0.95).  A line is
 * anchored by its first glyph's quad (left, top) in the 640x448 frame. */


#define SX(t) ((t)->sx > 0.0f ? (t)->sx : (t)->s)
#define GS(t) ((t)->gs > 0.0f ? (t)->gs : (t)->s)

static void text_push(dw4_fetext *t, const float box[4], const float uv[4])
{
    dw4_ui_draw *dd;
    float q[4][5];
    int k;

    if (box[2] <= box[0] || box[3] <= box[1])
        return;
    if (*t->n + 2 > *t->cap) {
        int nc = *t->cap ? 2 * *t->cap : 512;
        dw4_ui_draw *g = (dw4_ui_draw *)realloc(*t->dl, (size_t)nc * sizeof **t->dl);

        if (!g)
            return;
        *t->dl = g;
        *t->cap = nc;
    }
    /* the atlas rows are stored the way fefont draws them: the quad's top edge samples v1 */
    q[0][0] = box[0]; q[0][1] = box[1]; q[0][2] = uv[0]; q[0][3] = uv[3];
    q[1][0] = box[2]; q[1][1] = box[1]; q[1][2] = uv[2]; q[1][3] = uv[3];
    q[2][0] = box[2]; q[2][1] = box[3]; q[2][2] = uv[2]; q[2][3] = uv[1];
    q[3][0] = box[0]; q[3][1] = box[3]; q[3][2] = uv[0]; q[3][3] = uv[1];
    for (k = 0; k < 4; k++)
        q[k][4] = 1.0f;
    for (k = 0; k < 2; k++) {
        int a = k == 0 ? 1 : 2, b = k == 0 ? 2 : 3;

        dd = &(*t->dl)[(*t->n)++];
        memset(dd,0,sizeof *dd);
        dd->tex = &t->atlas;
        dd->blend = 1;
        dd->stq = 1;
        memcpy(dd->v[0], q[0], sizeof dd->v[0]);
        memcpy(dd->v[1], q[a], sizeof dd->v[1]);
        memcpy(dd->v[2], q[b], sizeof dd->v[2]);
        dd->rgba[0][0] = dd->rgba[1][0] = dd->rgba[2][0] = 114;      /* 0.9 */
        dd->rgba[0][1] = dd->rgba[1][1] = dd->rgba[2][1] = 114;
        dd->rgba[0][2] = dd->rgba[1][2] = dd->rgba[2][2] = 114;
        dd->rgba[0][3] = dd->rgba[1][3] = dd->rgba[2][3] = 121;      /* 0.95 */
    }
}

/* A run of glyph codes whose first quad's top-left is (left, top) in 640x448 pixels. */
void dw4_fetext_codes(dw4_fetext *t, const uint32_t *codes, int nc, float left, float top)
{
    float box[4], uv[4], adv, pen = 0.0f, y0 = 0.0f;
    int i;

    if (nc <= 0 || dw4_fefont_quad(t->font, codes[0], 0.0f, 0.0f, GS(t), box, uv, &adv) != 0)
        return;
    pen = (t->cx + (left - 320.0f) * SX(t)) - box[0];
    y0 = top * t->s - box[1];
    for (i = 0; i < nc; i++) {
        if (dw4_fefont_quad(t->font, codes[i], pen, y0, GS(t), box, uv, &adv) != 0)
            continue;
        text_push(t, box, uv);
        pen += adv;
    }
}

void dw4_fetext_str(dw4_fetext *t, const char *str, float left, float top)
{
    uint32_t c[64];
    int n = 0;

    while (*str && n < 64)
        c[n++] = (unsigned char)*str++;
    dw4_fetext_codes(t, c, n, left, top);
}

/* The same, centred on x = `centre` (640x448) with the glyph tops at `top`. */
void dw4_fetext_centred(dw4_fetext *t, const char *str, float centre, float top)
{
    uint32_t c[64];
    float box[4], uv[4], adv, w = 0.0f, pen, y0;
    int n = 0, i;

    while (*str && n < 64)
        c[n++] = (unsigned char)*str++;
    if (!n)
        return;
    for (i = 0; i < n; i++)
        if (dw4_fefont_quad(t->font, c[i], 0.0f, 0.0f, GS(t), box, uv, &adv) == 0)
            w += adv;
    if (dw4_fefont_quad(t->font, c[0], 0.0f, 0.0f, GS(t), box, uv, &adv) != 0)
        return;
    pen = t->cx + (centre - 320.0f) * SX(t) - w * 0.5f;
    y0 = top * t->s - box[1];
    for (i = 0; i < n; i++) {
        if (dw4_fefont_quad(t->font, c[i], pen, y0, GS(t), box, uv, &adv) != 0)
            continue;
        text_push(t, box, uv);
        pen += adv;
    }
}

