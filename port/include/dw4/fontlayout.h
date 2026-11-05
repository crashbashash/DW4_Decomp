/* Retail font geometry in authored units, independent of rendering clocks. */
#ifndef DW4_FONTLAYOUT_H
#define DW4_FONTLAYOUT_H
#include "dw4/fefont.h"
typedef struct { float x,y,z,u,v; } dw4_font_vertex;
/* Six vertices in original triangle order (4535d0). */
void dw4_fontlayout_glyph(const dw4_glyph *,float pen,float baseline,dw4_font_vertex out[6]);
/* Owned geometry. CR is ignored; LF moves the following run down one face height.
 * Width controls alignment, not wrapping; height does not clip the original geometry.
 * Unknown codes have no geometry. Caller frees *vertices. */
int dw4_fontlayout_build(const dw4_fefont *,const uint32_t *,size_t,float width,int align,
    dw4_font_vertex **vertices,size_t *count);
int dw4_fontlayout_replace_unknown(const dw4_fefont *,uint16_t *,size_t,uint16_t);
#endif
