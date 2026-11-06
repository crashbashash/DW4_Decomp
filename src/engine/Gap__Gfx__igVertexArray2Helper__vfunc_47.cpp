#include "dw4/reflected.h"
extern "C" {
void *igVertexArray2__FindVertexData(...);
extern int DAT_00586818[4];
extern int DAT_005610b0[4];
extern int DAT_00561098[4];
struct B3 { unsigned char b[3]; };
struct B4 { unsigned char b[4]; };
unsigned char Gap__Gfx__igVertexArray2Helper__vfunc_47(igVertexArray2Helper *arg0, int arg1, int arg2);
}
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct T : VC { int f4; int f8; int f12; unsigned char *f16; };
struct S { char pad[12]; T *f12; int f16; int f20; int f24; };
unsigned char Gap__Gfx__igVertexArray2Helper__vfunc_47(igVertexArray2Helper *arg0, int arg1, int arg2) {
    S *v;
    int s3;
    unsigned char sp3[3];
    unsigned char sp4[4];
    unsigned char *p;
    int idx;
    T *t;
    v = (S *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 6, 0));
    s3 = DAT_00586818[0];
    if (s3 == v->f12->vX()) {
        idx = arg1 + arg2 * v->f24;
        return v->f12->f16[idx];
    }
    s3 = DAT_005610b0[0];
    if (s3 == v->f12->vX()) {
        p = v->f12->f16 + arg2 * 3;
        sp3[0] = p[0];
        sp3[1] = p[1];
        sp3[2] = p[2];
        return sp3[arg1];
    }
    s3 = DAT_00561098[0];
    if (s3 == v->f12->vX()) {
        p = v->f12->f16 + arg2 * 4;
        sp4[0] = p[0];
        sp4[1] = p[1];
        sp4[2] = p[2];
        sp4[3] = p[3];
        return sp4[arg1];
    }
    return 0;
}
