#include "dw4/reflected.h"
extern "C" {
void *igVertexArray2__FindVertexData(...);
extern int DAT_00586808[4];
extern int DAT_005610c8[4];
extern int DAT_005610b8[4];
extern int DAT_005610a8[4];
void Gap__Gfx__igVertexArray2Helper__vfunc_44(igVertexArray2Helper *arg0, int arg1, int arg2, float arg3);
}
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct T : VC { int f4; int f8; int f12; float *f16; };
struct S { char pad[12]; T *f12; int f16; int f20; int f24; };
struct V2 { float f[2]; V2(){} V2(const V2 &o){ f[0]=o.f[0]; f[1]=o.f[1]; } V2 &operator=(const V2 &o){ f[0]=o.f[0]; f[1]=o.f[1]; return *this; } float &operator[](int i){ return f[i]; } };
struct V3 { float f[3]; V3(){} V3(const V3 &o){ f[0]=o.f[0]; f[1]=o.f[1]; f[2]=o.f[2]; } V3 &operator=(const V3 &o){ f[0]=o.f[0]; f[1]=o.f[1]; f[2]=o.f[2]; return *this; } float &operator[](int i){ return f[i]; } };
struct V4 { float f[4]; V4(){} V4(const V4 &o){ f[0]=o.f[0]; f[1]=o.f[1]; f[2]=o.f[2]; f[3]=o.f[3]; } V4 &operator=(const V4 &o){ f[0]=o.f[0]; f[1]=o.f[1]; f[2]=o.f[2]; f[3]=o.f[3]; return *this; } float &operator[](int i){ return f[i]; } };
void Gap__Gfx__igVertexArray2Helper__vfunc_44(igVertexArray2Helper *arg0, int arg1, int arg2, float arg3) {
    S *v;
    int s3;
    T *c;
    v = (S *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 5, 0));
    s3 = DAT_00586808[0];
    if (s3 == v->f12->vX()) {
        int idx;
        c = v->f12;
        idx = arg1 + arg2 * v->f24;
        if (c->f8 != 0 && idx >= 0 && idx < c->f8) {
            c->f16[idx] = arg3;
        }
    } else {
    s3 = DAT_005610c8[0];
    if (s3 == v->f12->vX()) {
        c = v->f12;
        V2 *q = (V2 *)c->f16 + arg2;
        V2 t(*q);
        t[arg1] = arg3;
        if (c->f8 != 0 && arg2 >= 0 && arg2 < c->f8) {
            *q = t;
        }
    } else {
    s3 = DAT_005610b8[0];
    if (s3 == v->f12->vX()) {
        c = v->f12;
        V3 *q = (V3 *)c->f16 + arg2;
        V3 t(*q);
        t[arg1] = arg3;
        if (c->f8 != 0 && arg2 >= 0 && arg2 < c->f8) {
            *q = t;
        }
    } else {
    s3 = DAT_005610a8[0];
    if (s3 == v->f12->vX()) {
        c = v->f12;
        V4 *q = (V4 *)c->f16 + arg2;
        V4 t(*q);
        t[arg1] = arg3;
        if (c->f8 != 0 && arg2 >= 0 && arg2 < c->f8) {
            *q = t;
        }
    }
    }
    }
    }
}
