#include "dw4/reflected.h"

struct UCodeState;
struct O176a50;
class V96;
class W;
struct Geometry1774;

extern "C" {
int FUN_0015cb50(...);
int FUN_001f7340(...);
int FUN_001f7360(...);
int FUN_0015d0d0(...);
void FUN_001f7370(float);
int igObject_Destroy(...);
void FUN_0015ce90(UCodeState *state);
int FUN_0015cfb0(...);
int FUN_0015cb60(...);
int FUN_0015d6c0(...);
int FUN_0015d700(...);
int FUN_0015d740(...);
int FUN_0015d7c0(...);
int FUN_0015d840(...);
int FUN_0015d860(...);
int FUN_0015d880(...);
int FUN_0015da00(...);
int FUN_0015da70(...);
int FUN_0015db40(...);
int FUN_0015db60(...);
extern int DAT_004df6b0[4];
int FUN_001ee730(...);
int FUN_001ee740(...);
int FUN_001e9730(...);
int FUN_001e9720(...);
int FUN_001e96d0(...);
int FUN_001e7560(...);
int FUN_001e74b0(...);
int FUN_001e7500(...);
int FUN_001eb5e0(...);
int FUN_00180060(...);
void FUN_00180170(int, unsigned int, int, int, int *, int *, unsigned int); /* matching construct: prototype sweep — unsigned blend index and count parameters order the argument loads */
void *FUN_0015f4a0(...);
extern unsigned char GPR_00554b6c;
extern int DAT_00561098[4];
extern int DAT_005610b0[4];
extern int DAT_00586818[4];
extern int DAT_00586830[4];
extern int DAT_00586840[4];
extern int DAT_00586898[4];

void FUN_001767c0(void *self, int value);
void FUN_00176800(int *arg0, int arg1, int arg2);
void FUN_00176900(int arg0, float farg0);
void FUN_00176920(UCodeState *state);
void FUN_001769f0(void *arg0);
void FUN_00176a50(O176a50 *arg0, V96 *arg1, int *arg2, int arg3, int arg4);
int FUN_00176ba0(void *arg0);
void FUN_00176bb0(void *arg0);
void FUN_00176c00(void *arg0);
void FUN_00176c50(void *arg0);
void FUN_00176ca0(void *arg0);
void FUN_00176cf0(void *arg0);
void FUN_00176d40(void *arg0);
void FUN_00176d90(W *arg0, int arg1, int arg2, float *arg3);
void FUN_00176ed0(void *arg0);
void FUN_00176f20(void *arg0);
void FUN_00176f70(void *arg0);
void FUN_00176fc0(void *arg0);
int FUN_00177010(igPsx2VisualContext *vc, int *arg1, int *arg2, int arg3, int arg4);
int FUN_001774c0(igPsx2VisualContext *vc, Geometry1774 *geom, unsigned char *useTexture);
}

class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int * vX(); };
class VB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void vX(int,int,int); };

struct UCodeAttr : igObject {
    char pad8[12];
    int flags;
};

class UCodeSource {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
    virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41();
    virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53();
    virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58();
    virtual UCodeAttr *currentAttr();
};

struct UCodeState {
    char pad0[24];
    UCodeAttr *attr;
    char pad28[4];
    unsigned char loaded;
    char pad33[3];
    int mode;
    char pad40[352];
    UCodeSource *source;
};

class V188 { public: virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27(); virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31(); virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35(); virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39(); virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43(); virtual void a44(); virtual int v188(int *); };
class V96 { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void v96(int *, int, int, int); };
struct O176a50 { char p0[24]; void *f24; char p28[364]; int f392; };
struct R { int w0; int rc; };

class DW4VC_116_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(); };
class DW4VC_120_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int vX(); };
class DW4VC_164_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int vX(); };
class DW4VC_168_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int vX(); };
class DW4VC_172_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual int vX(); };
class DW4VC_176_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual int vX(); };

class O176d90 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void set(int,int,float *); virtual void get(int,int,float *); int pad[4]; unsigned flags; };
struct V2 { float x, y; };
class W { public: int pad[6]; O176d90 *o; };

class DW4VC_204_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual int vX(); };
class DW4VC_208_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int vX(); };
class DW4VC_228_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual int vX(); };
class DW4VC_232_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual int vX(); };

/* Run the shared slot-57 step, then store the value into the +392 word of the object (past the
 * reflected igPsx2UserUCodeExt fields). */
void FUN_001767c0(void *self, int value) {
    FUN_0015cb50();
    *(int *)((char *)self + 392) = value;
}

void FUN_00176800(int *arg0, int arg1, int arg2) {
    int *p;
    int *q;
    int s3, a1, a0_3, s3_2;
    if (!(((int *)arg0[6])[5] & 0x10)) {
        FUN_0015d0d0(arg0);
        return;
    }
    p = ((VA *)arg0[6])->vX();
    s3 = ((unsigned int)(*p & 0xF0000) >> 0x10) & 0xFF;
    q = ((VA *)arg0[6])->vX();
    a1 = *q;
    a0_3 = ((unsigned int)(a1 & 0x300000) >> 0x14) & 0xFF;
    s3_2 = DAT_004df6b0[a0_3 | (((s3 & 0xFF) == 2) * 4)];
    if (s3_2 != FUN_001f7360(a0_3, a1)) {
        FUN_001f7340(s3_2);
    }
    ((VB *)arg0[98])->vX(0x1000, arg1, arg2);
}

void FUN_00176900(int arg0, float farg0) {
    *(float *)((char *)(arg0) + 28) = farg0;
    FUN_001f7370((0.5f * farg0));
}

void FUN_00176920(UCodeState *state) {
    UCodeAttr *attr = state->source->currentAttr();
    UCodeAttr *previous;

    if (attr != 0) {
        attr->_refCount = attr->_refCount + 1;
    }
    previous = state->attr;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previous);
        }
    }
    state->attr = attr;
    if (!(state->attr->flags & 0x10)) {
        FUN_0015ce90(state);
        return;
    }
    if (state->mode == 1) {
        FUN_0015ce90(state);
    }
    state->loaded = 1;
}

void FUN_001769f0(void *arg0) {
    int temp_a1;

    if (!(*(int *)((char *)(*(int *)((char *)(arg0) + 24)) + 20) & 0x10)) {
        FUN_0015cfb0();
        return;
    }
    temp_a1 = *(int *)((char *)(arg0) + 36);
    if (temp_a1 == 1) {
        FUN_0015cfb0(arg0, temp_a1);
    }
    *(char *)((char *)(arg0) + 32) = 0;
}

void FUN_00176a50(O176a50 *arg0, V96 *arg1, int *arg2, int arg3, int arg4) {
    int sp6C;
    int temp_v1;
    R *a0;

    if (arg1 != 0) {
        ((R *)arg1)->rc = ((R *)arg1)->rc + 1;
    }
    a0 = (R *)arg0->f24;
    if (a0 != 0) {
        a0->rc = a0->rc - 1;
        if ((a0->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(a0);
        }
    }
    arg0->f24 = arg1;
    if (((V188 *)arg0)->v188(arg2) == 0) {
        FUN_0015cb60(arg0, arg1, arg2, arg3, (arg4 & ~0x10) | 4);
        return;
    }
    sp6C = *arg2;
    if ((((unsigned int)(*arg2 & 0xF0000) >> 0x10) & 0xFF) == 1) {
        temp_v1 = sp6C & 0xFFF0FFFF;
        sp6C = temp_v1;
        sp6C = sp6C | 0x20000;
    }
    arg1->v96((int *)&sp6C, arg3, arg4 | 0x10, arg0->f392);
}

int FUN_00176ba0(void *arg0) {
    return *(int *)((char *)(arg0) + 36) != 1;
}

void FUN_00176bb0(void *arg0) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_116_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015d6c0(arg0);
}

void FUN_00176c00(void *arg0) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_120_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015d700(arg0);
}

void FUN_00176c50(void *arg0) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_164_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015d740(arg0);
}

void FUN_00176ca0(void *arg0) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_168_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015d7c0(arg0);
}

void FUN_00176cf0(void *arg0) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_172_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015d840(arg0);
}

void FUN_00176d40(void *arg0) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_176_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015d860(arg0);
}

void FUN_00176d90(W *arg0, int arg1, int arg2, float *arg3) {
    /* matching construct: variant search — locals declared in reverse order, which sets their stack slots and registers */
    V2 a;
    V2 b;
    if (arg0->o->flags & 0x10) {
        arg0->o->get(0, arg2, &a.x);
        arg0->o->get(1, arg2, &b.x);
        if (arg1 == 0) {
            b.y = arg3[1];
            a.x = arg3[0];
            arg0->o->set(0, arg2, &a.x);
            arg0->o->set(1, arg2, &b.x);
            return;
        }
        a.y = arg3[1];
        b.x = arg3[0];
        arg0->o->set(0, arg2, &a.x);
        arg0->o->set(1, arg2, &b.x);
        return;
    }
    FUN_0015d880(arg0);
}

void FUN_00176ed0(void *arg0) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_204_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015da00(arg0);
}

void FUN_00176f20(void *arg0) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_208_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015da70(arg0);
}

void FUN_00176f70(void *arg0) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_228_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015db40(arg0);
}

void FUN_00176fc0(void *arg0) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_232_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015db60(arg0);
}

struct VertexArray177 {
    int *vtbl;
    int pad4;
    int *f8;
    char pad12[20];
    int f32;
    int f36;
    char pad40[32];
    int f72[16];
    int f136;
};
class VertexFormat177 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int *format(); };
struct DListEntry177 { int f0; VertexArray177 *va; };
struct DLists177 { char pad[16]; DListEntry177 **entries; };

int FUN_00177010(igPsx2VisualContext *vc, int *arg1, int *arg2, int arg3, int arg4) {
    int i;
    VertexArray177 *prev;
    int j; /* matching construct: declaration-order sweep — second loop counter gets a1, count a0 */
    int limit;
    int count;
    bool enabled = false;
    int result = 0;
    int levels = 0;
    VertexArray177 *va;

    if (vc->_bVertexBlendingEnabled) {
        if (arg3 > -1) {
            levels = FUN_001ee730(arg3);
            limit = FUN_001ee740(arg3);
            if (levels != 0) {
                enabled = true;
                if (levels > 0 && levels < 5 && vc->_blendMatricesCount < 121 && !GPR_00554b6c
                    && limit >= vc->_blendMatricesCount) {
                    result = 2;
                } else {
                    result = 3;
                }
            }
        } else {
            va = (VertexArray177 *)vc->_pVertexArray;
            levels = (unsigned char)(((unsigned int)*((VertexFormat177 *)va)->format() & 0xf0) >> 4);
            if (levels > 0) {
                enabled = true;
                if (levels > 0 && levels < 5 && vc->_blendMatricesCount < 121 && !GPR_00554b6c) {
                    result = 2;
                    FUN_001e9730(va->f36);
                    FUN_001e9720(va->f32);
                } else {
                    result = 1;
                    if (vc->_currentDListHandle >= 0) {
                        vc->_dlistErrors = 1;
                    }
                }
            }
        }
    }
    if ((VertexArray177 *)vc->_pVertexArray != 0 && vc->_currentDListHandle != -1) {
        ((VertexArray177 *)vc->_pVertexArray)->f72[0] = vc->_texCoordIndex[0];
        if (vc->_pixelPipelineMode == 3) {
            for (i = 1; i < vc->_bMultiPassNum; i++) {
                ((VertexArray177 *)vc->_pVertexArray)->f72[i] = vc->_texCoordIndex[i];
            }
            ((VertexArray177 *)vc->_pVertexArray)->f136 = vc->_bMultiPassNum;
        } else {
            ((VertexArray177 *)vc->_pVertexArray)->f136 = 0;
        }
        ((DLists177 *)vc->_pDLists)->entries[vc->_currentDListHandle]->va = (VertexArray177 *)vc->_pVertexArray;
    }
    if (arg4 == -1) {
        *arg1 = ((VertexArray177 *)vc->_pVertexArray)->f8[0] ? ((VertexArray177 *)vc->_pVertexArray)->f8[0] : 0;
        *arg2 = ((VertexArray177 *)vc->_pVertexArray)->f8[1] ? ((VertexArray177 *)vc->_pVertexArray)->f8[1] : 0;
    } else {
        prev = ((DLists177 *)vc->_pDLists)->entries[arg4]->va;
        if (prev != 0) {
            if (vc->_texEnable[0] && vc->_texCoordIndex[0] != prev->f72[0]) {
                result = 3;
            }
            if (vc->_pixelPipelineMode == 3) {
                count = vc->_bMultiPassNum;
                if (count != prev->f136) {
                    result = 3;
                } else {
                    for (j = 1; j < count; j++) {
                        if (vc->_texEnable[j] && vc->_texCoordIndex[j] != prev->f72[j]) {
                            result = 3;
                        }
                    }
                }
            } else if (prev->f136 != 0) {
                result = 3;
            }
        }
    }
    if (enabled) {
        if (result == 2) {
            FUN_001e96d0(levels, levels);
            if (!FUN_001e7560(9)) {
                FUN_001e74b0(9);
            }
        } else if (result == 1) {
            if (FUN_001e7560(9)) {
                FUN_001e7500(9);
            }
            if (vc->_bLightingEnabled || vc->_texCoordSource[0] == 2) {
                if (vc->_inverseTransposeNeedValidation) {
                    FUN_00180060(vc);
                }
                FUN_00180170(vc->_pVertexArray, vc->_blendIndex, vc->_blendMatrices, vc->_inverseTranspose, arg1, arg2, vc->_blendMatricesCount);
            } else {
                FUN_00180170(vc->_pVertexArray, vc->_blendIndex, vc->_blendMatrices, 0, arg1, arg2, vc->_blendMatricesCount);
            }
        }
    } else if (FUN_001e7560(9)) {
        FUN_001e7500(9);
    }
    if (FUN_001e7560(27)) {
        FUN_001e7500(27);
        FUN_001eb5e0(0, 0, 0, 0);
        FUN_001eb5e0(1, 0, 0, 0);
        FUN_001eb5e0(2, 0, 0, 0);
        FUN_001eb5e0(3, 0, 0, 0);
        FUN_001eb5e0(4, 0, 0, 0);
    }
    return result;
}

class AttrValue1774 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int meta(); int pad[3]; int f16; };
struct AttrNode1774 { char p0[12]; AttrValue1774 *obj; char p16[8]; int f24; char p28[4]; int f32; };
struct Geometry1774 { char p0[20]; int attrs; char p24[24]; int f48[16]; int f112; int f116; int f120; char p124[4]; int f128; };

int FUN_001774c0(igPsx2VisualContext *vc, Geometry1774 *geom, unsigned char *useTexture) {
    int j;
    int limit;
    AttrNode1774 *node;
    AttrValue1774 *value;
    int attrs;
    int levels = 0; /* matching construct: declaration-order sweep — levels in s4, texture in s3 */
    int matrices;
    int texture;
    int prebuilt;
    int result = 0;

    prebuilt = geom->f128;
    *useTexture = 0;
    if (vc->_bVertexBlendingEnabled) {
        matrices = 0;
        texture = 0;
        if (prebuilt) {
            levels = geom->f120;
            limit = geom->f116;
        } else {
            attrs = geom->attrs;
            node = (AttrNode1774 *)FUN_0015f4a0(attrs, 6, 0);
            int m1 = DAT_00586818[0]; /* matching construct: spelling sweep — the compared metas are locals, spilled with sw */
            if (m1 == node->obj->meta()) {
                matrices = node->obj->f16;
                levels = node->f24;
            } else {
                int m2 = DAT_005610b0[0];
                if (m2 == node->obj->meta()) {
                    matrices = node->obj->f16;
                    levels = 3;
                } else {
                    int m3 = DAT_00561098[0];
                    if (m3 == node->obj->meta()) {
                        levels = 3;
                        matrices = node->obj->f16;
                    }
                }
            }
            node = (AttrNode1774 *)FUN_0015f4a0(attrs, 5, 0);
            if (node != 0) {
                value = node->obj;
                if (value->meta() == DAT_00586898[0]) {
                    int a = node->f32;
                    FUN_001eb5e0(3, 1, 7 - a, a);
                    texture = value->f16;
                    *useTexture = 1;
                } else if (node->obj->meta() == DAT_00586818[0]) {
                    int a = node->f32;
                    FUN_001eb5e0(3, 0, 8 - a, a);
                    texture = value->f16;
                    *useTexture = 1;
                } else if (node->obj->meta() == DAT_00586830[0]) {
                    int a = node->f32;
                    FUN_001eb5e0(3, 1, 0xF - a, a);
                    texture = value->f16;
                    *useTexture = 1;
                } else if (node->obj->meta() == DAT_00586840[0]) {
                    int a = node->f32;
                    FUN_001eb5e0(3, 0, 0x10 - a, a);
                    texture = value->f16;
                    *useTexture = 1;
                } else {
                    texture = node->obj->f16;
                }
            }
            limit = vc->_blendMatricesCount;
        }
        if (levels > 0 && levels < 5 && vc->_blendMatricesCount < 121 && !GPR_00554b6c && limit >= vc->_blendMatricesCount) {
            result = 2;
            if (!prebuilt) {
                FUN_001e9730(matrices);
                FUN_001e9720(texture);
            }
        } else {
            result = 1;
        }
        if (result == 2) {
            FUN_001e96d0(levels, levels);
            if (!FUN_001e7560(9)) {
                FUN_001e74b0(9);
            }
        } else if (result == 1) {
            if (FUN_001e7560(9)) {
                FUN_001e7500(9);
            }
        }
    } else if (FUN_001e7560(9)) {
        FUN_001e7500(9);
    }
    if (prebuilt) {
        if (vc->_texEnable[0] && vc->_texCoordIndex[0] != geom->f48[0]) {
            result = 3;
        }
        if (vc->_pixelPipelineMode == 3) {
            if (vc->_bMultiPassNum != geom->f112) {
                result = 3;
            } else {
                for (j = 1; j < vc->_bMultiPassNum; j++) {
                    if (vc->_texEnable[j] && vc->_texCoordIndex[j] != geom->f48[j]) {
                        result = 3;
                    }
                }
            }
        } else if (geom->f112 != 0) {
            result = 3;
        }
    }
    return result;
}
