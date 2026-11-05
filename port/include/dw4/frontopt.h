/* dw4/frontopt.h -- the title's Option screen (finding #724).
 *
 * The screen is the pack's own graphs: `j_optionwin02` (the dark left band, the legend panel, three
 * pill rows with their icons) and the highlight cursor `j_optioncursor11/12`, all in `NDMW.AFS`
 * entry 806, drawn head-on in screen space like the title UI (one model unit = one pixel at 640x448,
 * +y up, origin at the centre) with the GS state of the real draws (ALPHA 0x44, AREF 12, bilinear,
 * REPEAT).  The text over it is the front-end font, drawn by the caller.
 */
#ifndef DW4_FRONTOPT_H
#define DW4_FRONTOPT_H

#include "dw4/mount.h"
#include "dw4/titlehost.h"
#include "dw4/fefont.h"
#include "dw4/render.h"

typedef struct dw4_frontopt dw4_frontopt;

dw4_frontopt *dw4_frontopt_open(const dw4_mount *mnt);
/* Opt into ordered GPU replay; NULL reports unavailable/failed GPU. */
const char *dw4_frontopt_enable_gpu(dw4_frontopt *, int w, int h);
struct dw4_gl_layer;
const char *dw4_frontopt_use_gpu(dw4_frontopt *, struct dw4_gl_layer *);
const char *dw4_frontopt_gpu_info(const dw4_frontopt *);
void dw4_frontopt_close(dw4_frontopt *o);

/* Start the open animation (the window's bars slide in) with the cursor on row `sel`. */
void dw4_frontopt_bind_title(dw4_frontopt *, const dw4_title_host *);
void dw4_frontopt_reset(dw4_frontopt *o, int sel);

/* Draw the window/cursors from a bound title host's joint clocks and visibility;
 * drawing never advances that host. With no host, retain the legacy standalone
 * preview (one tick per draw; sel 0 camera, 1 light, 2 Return). */
void dw4_frontopt_draw(dw4_frontopt *o, dw4_fb *fb, int sel, const dw4_fefont *font, int camera_far,
                        int light_hard);

#endif /* DW4_FRONTOPT_H */
