#ifndef DW4_FRONTTEXT_H
#define DW4_FRONTTEXT_H
#include "dw4/mount.h"
#include "dw4/render.h"
typedef struct dw4_fronttext dw4_fronttext;
/* Localized FontTree rows and original title txt_mem.lua callback. */
dw4_fronttext *dw4_fronttext_open(const dw4_mount *);
void dw4_fronttext_close(dw4_fronttext *);
void dw4_fronttext_clear(dw4_fronttext *);
int dw4_fronttext_event(dw4_fronttext *,int32_t callno);
/* Native dynamic fields use original font codes and authored row geometry.
 * align is the font-layout enum: LEFT=0, RIGHT=1, CENTER=2. Empty hides the row.
 * Repeated identical publication keeps its cached glyph geometry. */
int dw4_fronttext_set(dw4_fronttext *,const char *group,const char *name,
    const uint32_t *codes,size_t count,int align,uint8_t luminance);
/* Borrowed triangles; no script or animation advancement during drawing. */
int dw4_fronttext_draw(dw4_fronttext *,unsigned,unsigned,const dw4_ui_draw **,size_t *);
const char *dw4_fronttext_error(const dw4_fronttext *);
#endif
