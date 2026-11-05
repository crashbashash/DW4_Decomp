/* dw4/uireplay.h — replay a captured GS frame's 2D layer (an analysis path, `dw4asset` only).
 *
 * A replay file is one `scripts/gs_ui.py` TSV: one screen-space triangle per row, in the GS's own
 * draw order, `TEX<TAB>x y u v r g b a<TAB>...` three times, where `TEX` names a `<TEX>.rgba` in
 * `texdir` (`-` = an untextured overlay).  The reader serves `dw4asset render --ui/--ui-only/--ui-seq`
 * for analysis; the shipped `dw4` host generates the front-end layer from the pack instead
 * (`src/frontlayer.c`) and no longer uses this path.
 *
 * A captured frame of the front-end menu carries the whole screen: the logo, the menu rows, the
 * cursor, the copyright and the streaming additive light trails (findings #609/#610).  `hide` is a
 * comma-separated texture-key list (NULL draws everything), so an analysis render can isolate a
 * layer.
 */
#ifndef DW4_UIREPLAY_H
#define DW4_UIREPLAY_H

#include "dw4/render.h"

/* Draw one replay TSV.  `nthreads` <= 0 means one thread per core.  `sx`/`sy` scale the captured
 * screen coordinates, so a capture composed for one framebuffer size can be drawn into another
 * (pass 1,1 for the capture's own size).  Returns the triangle count drawn, or -1 when the file
 * cannot be read. */
int dw4_ui_draw_file(dw4_fb *fb, const char *path, const char *texdir, int nthreads,
                     const char *hide, float sx, float sy);

/* A directory of `uiNNN.tsv` frames in name order: the engine's animated layer, sampled at the
 * capture rate (PCSX2's screenshot hotkey, ~5.2 fps measured — the ceiling is the capture). */
typedef struct dw4_uiseq dw4_uiseq;

dw4_uiseq *dw4_uiseq_open(const char *dir, const char *texdir, const char *hide, float sx, float sy);
int  dw4_uiseq_count(const dw4_uiseq *q);
/* Draw frame `idx` (taken mod the count).  Returns triangles drawn, or -1. */
int  dw4_uiseq_draw(dw4_uiseq *q, dw4_fb *fb, int idx, int nthreads);
/* Draw the frame for an elapsed time and rate: `idx = (int)(secs * fps) % count`. */
int  dw4_uiseq_draw_at(dw4_uiseq *q, dw4_fb *fb, double secs, double fps, int nthreads);
void dw4_uiseq_close(dw4_uiseq *q);

#endif /* DW4_UIREPLAY_H */
