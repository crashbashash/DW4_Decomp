#include "dw4/reflected.h"
extern "C" {
void *FUN_0015f4a0(int, int, int);
int FUN_001eb5e0(int, int, int, int);
int FUN_001f10c0(int, int);
int igObject_IsKindOf(void *, int);
extern int DAT_005610c8[4];
extern int DAT_00586898[4];
extern int DAT_00586818[4];
extern int DAT_00586830[4];
extern int DAT_00586840[4];
void FUN_0017e980(igPsx2VisualContext *h, int arg1, int arg2);
}
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int meta(); int pad; int f16_; };
struct E { char pad[12]; Obj *obj; char pad2[16]; int f32; };
void FUN_0017e980(igPsx2VisualContext *h, int arg1, int arg2)
{
    int i;
    E *e;
    int v;
    Obj *o;

    if (h->_bMultiPassNum > 1 && h->_pixelPipelineMode == 3) {
        for (i = 1; i < h->_bMultiPassNum; i++) {
            e = (E *)FUN_0015f4a0(arg1, 4, h->_texCoordIndex[i]);
            v = 0;
            if (e != 0) {
                o = e->obj;
                if (o != 0 && igObject_IsKindOf(o, DAT_005610c8[0]) != 0) {
                    o = (Obj *)o;
                } else {
                    o = 0;
                }
                if (o != 0) {
                    v = ((int *)o)[4];
                } else {
                    o = e->obj;
                    if (DAT_00586898[0] == o->meta()) {
                        FUN_001eb5e0(2, 1, 7 - e->f32, e->f32);
                        v = ((int *)o)[4];
                    } else if (DAT_00586818[0] == o->meta()) {
                        FUN_001eb5e0(2, 0, 8 - e->f32, e->f32);
                        v = ((int *)o)[4];
                    } else if (DAT_00586830[0] == o->meta()) {
                        FUN_001eb5e0(2, 1, 15 - e->f32, e->f32);
                        v = ((int *)o)[4];
                    } else if (DAT_00586840[0] == o->meta()) {
                        FUN_001eb5e0(2, 0, 16 - e->f32, e->f32);
                        v = ((int *)o)[4];
                    }
                }
                if (h->_pIndexArray == 0) {
                    v += arg2 * 8;
                }
            }
            FUN_001f10c0(i, v);
        }
    }
}
