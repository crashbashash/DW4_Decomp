#include "dw4/reflected.h"
/* 0x00453410 - Gap__Bec__beFontImage__vfunc_22. glyph layout loop with a stack float pair, declaration order, inverted compare for the at-register temp; alternate compiler -O3. Verified byte-identical by tools/verify.py. */
struct V2 { float x; float y; };
struct GlyphMetricsRecord { char pad[4]; float f4; };
struct TextLayoutBuffer { char pad[12]; int f12; };
int FUN_004535d0(beFontImage *, struct TextLayoutBuffer *, int, struct V2 *, struct GlyphMetricsRecord *);
int FUN_00453830(beFontImage *, int);
void Gap__Bec__beFontImage__vfunc_22(beFontImage *arg0, struct TextLayoutBuffer *arg1, unsigned short *arg2) {
    struct V2 p;
    int len;
    int i;
    int idx;
    int c;
    unsigned short *s;
    struct GlyphMetricsRecord *rec;
    i = 0;
    p.y = arg0->_baseLine;
    p.x = 0.0f;
    len = arg1->f12;
    s = arg2;
    for (; (c = *s) != 0; s++) {
        idx = FUN_00453830(arg0, c);
        if (idx >= 0) {
            if (i + 6 >= len) {
                break;
            }
            rec = (struct GlyphMetricsRecord *)((char *)((igCharMetricsList *)arg0->_charMetricsList)->_data + idx * 40);
            FUN_004535d0(arg0, arg1, i, &p, rec);
            i += 6;
            p.x += rec->f4;
        }
    }
}
