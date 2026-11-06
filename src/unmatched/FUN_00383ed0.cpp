#include "dw4/reflected.h"
typedef unsigned int u32;
struct Vec3Table { char p0[16]; char *base; int stride; };
extern "C" void FUN_00383ed0(beFont *self, int unused, beFontInfoData *par, Vec3Table *tab) {
    float ref = par->_width;
    int mode = par->_align;
    float f = 0.0f;
    float g = f;
    char *base = tab->base;
    u32 a = 0;
    int i;
    float *p;
    u32 lim;
    u32 j;
    for (i = 0; i < ((igUnsignedIntList *)self->_lineFeedList)->_count; i++) {
        lim = ((u32 *)((igUnsignedIntList *)self->_lineFeedList)->_data)[i];
        switch (mode) {
        case 1:
            f = ref - ((float *)((igFloatList *)self->_alignList)->_data)[i];
            break;
        case 2:
            f = (ref - ((float *)((igFloatList *)self->_alignList)->_data)[i]) / 2.0f;
            break;
        }
        while (a < lim) {
            for (j = a; j < a + 6; j++) {
                p = (float *)(base + tab->stride * j);
                p[0] = p[0] + f;
                p[1] = p[1] + g;
                p[2] = p[2] + g;
            }
            a += 6;
        }
    }
}
