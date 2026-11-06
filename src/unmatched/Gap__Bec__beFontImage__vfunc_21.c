/* Glyph layout loop with a stack float pair, declaration order, inverted compare for the at-
 * register temp; alternate compiler -O3. */
struct GlyphPos { float x; float y; };
struct GlyphMetricsRecord { char pad[4]; float f4; };
/* glyph-metrics list header: record buffer pointer at +16 (list class not recovered) */
struct GlyphMetricsList { char pad[16]; char *f16; };
#include "dw4/reflected.h"
struct GlyphVertexBuffer { char pad[12]; int f12; };
int FUN_004535d0(beFontImage *, struct GlyphVertexBuffer *, int, struct GlyphPos *, struct GlyphMetricsRecord *);
int FUN_00453830(beFontImage *, int);
void Gap__Bec__beFontImage__vfunc_21(beFontImage *arg0, struct GlyphVertexBuffer *arg1, char *arg2) {
    struct GlyphPos p;
    int len;
    int i;
    int idx;
    char *s;
    struct GlyphMetricsRecord *rec;
    i = 0;
    p.y = arg0->_baseLine;
    p.x = 0.0f;
    len = arg1->f12;
    s = arg2;
    for (; *s != 0; s++) {
        idx = FUN_00453830(arg0, *s);
        if (idx >= 0) {
            if (i + 6 > len) {
                break;
            }
            rec = (struct GlyphMetricsRecord *)(((struct GlyphMetricsList *)arg0->_charMetricsList)->f16 + idx * 40);
            FUN_004535d0(arg0, arg1, i, &p, rec);
            i += 6;
            p.x += rec->f4;
        }
    }
}
