#include "dw4/reflected.h"

struct OO;
struct S4d0;

extern "C" {
int Memory_FreeBuffer(int);
int Memory_GetAllocatorBySelector(int);
void igObject_Destroy(void *);
int Matrix44_Copy(...);
int FUN_001904f0(void*,void*,void*);
int FUN_00190d80(void*,float*,int);
int FUN_00191860(void*,float,float,float,float,float,float);
int FUN_00192510(void*,float*,float*,float*,float*,float*,float*);
extern int DAT_00587020[4];
extern int DAT_004e0ef0[4];
void FUN_0015ce90(OO *arg0);
void FUN_0015d4d0(S4d0 *s);
}

union Ref { int w; struct { unsigned cnt:23; unsigned f:9; } b; };
struct Rc { int vt; Ref u; };
struct V2 { int a; int b; };
struct Inner { char p0[60]; int f60; int f64; char p1[8]; int f76; };
class Obj2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int v96(int *, int, int, int); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int v200(int, int, V2 *); Ref u; Inner *f8;};
class Al { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int v216(int); };
struct A1 { int vt; Ref u; char p0[16]; Al *f24; };
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int v168(int, int, V2 *); char p0[20]; Obj2 *f24;};

class DW4VC_244_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual int vX(); };
class DW4VC_812_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual int vX(int, char *); };
class DW4VC_832_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual int vX(int, char *); };
struct RR { int w0; int rc; };
struct OO { char pad[20]; void *f20; RR *f24; int pad3; char f32; char pad2[3]; int f36; char buf[512]; };

typedef struct R { int w0; int refs; } R;
class DW4VC_812 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual int vX(int, char *); };
struct X { char pad0[20]; DW4VC_812 *dev; R *obj; int w28; };
struct Y { char pad0[20]; DW4VC_812 *dev; R *obj; char pad1[4]; unsigned char b32; char pad2[3]; int w36; };

struct Cam { virtual void d0(); };
struct V {
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
  virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
  virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
  virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
  virtual int v48();
  virtual void d49(); virtual void d50();
  virtual void v51(int, int *, int *);
};
struct S4d0 {
  char p0[20]; V *o;
  char p1[272];
  float m[16];
  int w, h;
  float nl, nr, nb, nt, nn, nf;
};
class V164 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int vX(int, int); };
struct S740 { char pad24[24]; V164 *f24; };
class V168 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int vX(int, int); };
struct S7c0 { char pad24[24]; V168 *f24; };

class igVertexArrayView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40();
    virtual void vfunc_41(unsigned int index);
    virtual void vfunc_42(unsigned int index);
    virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50();
    virtual void vfunc_51(unsigned int index, float value);
    virtual void d52(); virtual void d53(); virtual void d54();
    virtual void vfunc_55();
    virtual void vfunc_56();
};
class igPointSpriteExtView {
public:
    int _vtable;
    unsigned int _refCount;
    char _pad8[16];
    igVertexArrayView *_vertexArray;
};

class T { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int m200(int, int, ...); virtual int m204(int, int, ...); };
struct O880 { char pad24[24]; T *p; };
class DW4VC_204_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual int vX(int, int); };
class DW4VC_208_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int vX(int, int); };
struct V2f { float x, y; };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void vX(int, void *); };
struct Sdb00 { char pad[24]; VC *o; };

extern "C" {

void FUN_0015cb50(int a0, int a1)
{
    *(int *)((char *)a0 + 20) = a1;
}

int FUN_0015cb60(O *arg0, A1 *arg1, int *arg2, unsigned int arg3, int arg4) {
    Rc *a0;
    V2 sp90;
    int sp9C;
    V2 sp88;
    V2 sp80;
    int s5;
    int s3;
    unsigned int s6;
    int m;
    int r1;
    unsigned char t;
    int t2;
    int x;
    unsigned int i;

    if (0 != arg1) {
        arg1->u.w = arg1->u.w + 1;
    }
    a0 = (Rc *)arg0->f24;
    if (a0 != 0) {
        a0->u.w = a0->u.w - 1;
        if (a0->u.b.cnt == 0) {
            igObject_Destroy(a0);
        }
    }
    arg0->f24 = (Obj2 *)arg1;
    sp9C = *arg2;
    if ((((unsigned int)(*arg2 & 0xF0000) >> 0x10) & 0xFF) == 0) {
        t2 = sp9C & 0xFFF0FFFF;
        sp9C = t2;
        sp9C = 0x10000 | sp9C;
    }
    s6 = arg3 * 6;
    arg4 = arg0->f24->v96((int *)&sp9C, s6, arg4, 0);
    s5 = arg3 * 12;
    arg0->f24->f8->f64 = ((Al *)Memory_GetAllocatorBySelector(DAT_00587020[0]))->v216(s5);
    t = 0xFF & ((unsigned int)(*arg2 & 0x300000) >> 0x14);
    arg4 = s5 + arg4;
    if (t != 0) {
        m = arg3 * 24;
        x = arg0->f24->f8->f60;
        s5 = m * (t & 0xFF);
        if (x != 0) {
            Memory_FreeBuffer(x);
            arg4 -= s5;
            arg0->f24->f8->f60 = 0;
        }
        s5 = ((((unsigned int)(*arg2 & 0x300000) >> 0x14) & 0xFF) * 4) * arg3;
        r1 = arg1->f24->v216(s5);
        arg4 += s5;
        arg0->f24->f8->f60 = r1;
    }
    if (*arg2 & 0x01000000) {
        x = arg0->f24->f8->f76;
        s5 = arg3 * 24;
        if (0 != x) {
            Memory_FreeBuffer(x);
            arg4 = arg4 - s5;
            arg0->f24->f8->f76 = 0;
        }
        s3 = arg3 * 4;
        arg0->f24->f8->f76 = (arg1->f24->v216(s3));
        arg4 += s3;
    }
    for (i = 0; i < s6; i++) {
        sp90.a = 0;
        sp90.b = 0;
        arg0->f24->v200(0, i, &sp90);
    }
    if ((((unsigned int)(*arg2 & 0xF0000) >> 0x10) & 0xFF) == 0) {
        for (i = 0; i < arg3; i++) {
            sp88.a = 0;
            sp88.b = 0;
            arg0->v168(0, i, &sp88);
            sp80.a = 0x3F800000;
            sp80.b = 0x3F800000;
            arg0->v168(1, i, &sp80);
        }
    }
    return arg4;
}

void FUN_0015ce90(OO *arg0) {
    RR *temp_v0;
    RR *old;

    arg0->f32 = 1;
    temp_v0 = (RR *)((DW4VC_244_0 *)(arg0->f20))->vX();
    if (temp_v0 != 0) {
        temp_v0->rc = temp_v0->rc + 1;
    }
    old = arg0->f24;
    if (old != 0) {
        old->rc = old->rc - 1;
        if ((old->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    arg0->f24 = temp_v0;
    ((DW4VC_832_2 *)(arg0->f20))->vX(1, (char *)arg0 + 0x28);
    ((DW4VC_812_2 *)(arg0->f20))->vX(1, (char *)&DAT_004e0ef0[0]);
    if (arg0->f36 == 1) {
        ((DW4VC_832_2 *)(arg0->f20))->vX(0, (char *)arg0 + 0x68);
        FUN_0015d4d0((S4d0 *)arg0);
        ((DW4VC_812_2 *)(arg0->f20))->vX(0, (char *)arg0 + 0xA8);
        return;
    }
    Matrix44_Copy((int)arg0 + 0xE8, (int)arg0 + 0x28);
}

void FUN_0015cfb0(Y *arg0) {
    R *temp_a0_3;

    arg0->b32 = 0;
    arg0->dev->vX(1, (char *)arg0 + 0x28);
    if (arg0->w36 == 1) {
        arg0->dev->vX(0, (char *)arg0 + 0x68);
    }
    temp_a0_3 = arg0->obj;
    if (temp_a0_3 != 0) {
        temp_a0_3->refs = temp_a0_3->refs - 1;
        if (((unsigned long long)((long long)temp_a0_3->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0_3);
        }
    }
    arg0->obj = 0;
}

void FUN_0015d050(void *arg0, int dummy1, void *arg2) {
    float temp_f0;

    temp_f0 = 0.5f * *(float *)((char *)(arg0) + 28);
    *(float *)((char *)(arg2) + 0) = temp_f0;
    *(float *)((char *)(arg2) + 4) = temp_f0;
}

void FUN_0015d070(igPointSpriteExt *arg0, int arg1, void *arg2) {
    float temp_f0;
    int b, idx, c;
    b = ((igVertexArray1_1 *)arg0->_vertexArray)->_vdata;
    idx = arg1 * 4;
    c = *(int *)(b + 60);
    temp_f0 = *(float *)(c + idx);
    *(float *)((char *)(arg2) + 0) = temp_f0;
    *(float *)((char *)(arg2) + 4) = temp_f0;
}

void FUN_0015d0a0(igPointSpriteExt *arg0, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(((igVertexArray *)(arg0->_vertexArray))->_vdata) + 60) + (arg1 * 8));
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(temp_v1) + 0);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(temp_v1) + 4);
}

void FUN_0015d4d0(S4d0 *s)
{
  int sw, sh;
  int r = s->o->v48();
  s->o->v51(r, &sw, &sh);
  if (s->w == sw) { if (s->h != sh) goto L; } else { L:
    s->w = sw; s->h = sh;
    float hw = (float)sw / 2.0f;
    float hh = (float)sh / 2.0f;
    FUN_00192510((char*)s + 0x68, &s->nl, &s->nr, &s->nb, &s->nt, &s->nn, &s->nf);
    FUN_00191860((char*)s + 0xA8, -hw, hw, -hh, hh, s->nn, s->nf);
    float rw = 1.0f / (s->nr - s->nl);
    s->m[0] = 2.0f * s->nn * rw;
    s->m[4] = 0;
    s->m[8] = rw * (s->nr + s->nl);
    s->m[12] = 0;
    float rh = 1.0f / (s->nt - s->nb);
    s->m[1] = 0;
    s->m[5] = 2.0f * s->nn * rh;
    s->m[9] = rh * (s->nt + s->nb);
    s->m[13] = 0;
    s->m[2] = 0; s->m[6] = 0; s->m[10] = 0; s->m[14] = -1.0f;
    s->m[3] = 0; s->m[7] = 0; s->m[11] = -1.0f; s->m[15] = 0;
    float v[3];
    v[2] = 1.0f;
    v[0] = 0.5f * (float)sw;
    v[1] = 0.5f * (float)sh;
    FUN_00190d80((char*)s + 0x128, v, 0x3f800000);
  }
  FUN_001904f0((char*)s + 0xE8, (char*)s + 0x28, (char*)s + 0x128);
}

void FUN_0015d6c0(void *arg0, int arg1, void *arg2) {
    int temp_a0;
    float *var_v1;
    float *src = (float *)arg2;
    temp_a0 = *(int *)((char *)(*(int *)((char *)(*(int *)((char *)(arg0) + 24)) + 8)) + 64);
    var_v1 = temp_a0 ? (float *)(temp_a0 + arg1 * 0xC) : 0;
    var_v1[0] = src[0];
    var_v1[1] = src[1];
    var_v1[2] = src[2];
}

/* The pointer is reused across the stride multiply (p = idx*12; p = base + p) with the base as the
 * first addend. */
void FUN_0015d700(igPsx2PointSpriteExt *arg0, int arg1, void *arg2) {
    int temp_a0;
    char *var_v1;
    temp_a0 = *(int *)((char *)(((igVertexArray *)arg0->_vertexArray)->_vdata) + 64);
    if (temp_a0 != 0) { var_v1 = (char *)(arg1 * 0xC); var_v1 = (char *)(temp_a0 + (int)var_v1); } else { var_v1 = 0; }
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(var_v1) + 0);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(var_v1) + 4);
    *(float *)((char *)(arg2) + 8) = (float) *(float *)((char *)(var_v1) + 8);
}

void FUN_0015d740(S740 *arg0, int arg1, int arg2) {
    int i;

    for (i = 0; i < 6; i++) {
        arg0->f24->vX(i + arg1 * 6, arg2);
    }
}

void FUN_0015d7c0(S7c0 *arg0, int arg1, int arg2) {
    int i;

    for (i = 0; i < 6; i++) {
        arg0->f24->vX(i + arg1 * 6, arg2);
    }
}

void FUN_0015d840(igPointSpriteExtView *self, unsigned int index)
{
    self->_vertexArray->vfunc_41(index * 6);
}

void FUN_0015d860(igPointSpriteExtView *self, unsigned int index)
{
    self->_vertexArray->vfunc_42(index * 6);
}

void FUN_0015d880(O880 *arg0, int arg1, int arg2, float *arg3) {
    float v[2];
    int base;
    int i2, i1;
    unsigned char z;
    if (arg1 == 0) {
        base = arg2 * 6;
        arg0->p->m200(0, base);
    } else {
        base = arg2 * 6;
        arg0->p->m200(0, base + 3);
    }
    i2 = base + 2;
    arg0->p->m204(0, i2, v);
    z = !arg1;
    v[z] = arg3[z];
    arg0->p->m200(0, i2, v);
    arg0->p->m200(0, base + 4, v);
    i1 = base + 1;
    arg0->p->m204(0, i1, v);
    v[arg1] = arg3[arg1];
    arg0->p->m200(0, i1, v);
    arg0->p->m200(0, base + 5, v);
}

void FUN_0015da00(void *arg0, int arg1, int arg2) {
    void **temp_a0;
    void **temp_a0_2;

    if (arg1 == 0) {
        temp_a0 = (void **)(*(int *)((char *)(arg0) + 24));
        ((DW4VC_204_2 *)(temp_a0))->vX((int)(0), (int)(arg2 * 6));
        return;
    }
    temp_a0_2 = (void **)(*(int *)((char *)(arg0) + 24));
    ((DW4VC_204_2 *)(temp_a0_2))->vX((int)(0), (int)((arg2 * 6) + 3));
}

void FUN_0015da70(void *arg0, int arg1, int arg2) {
    void **temp_a0;
    void **temp_a0_2;

    if (arg1 == 0) {
        temp_a0 = (void **)(*(int *)((char *)(arg0) + 24));
        ((DW4VC_208_2 *)(temp_a0))->vX((int)(0), (int)(arg2 * 6));
        return;
    }
    temp_a0_2 = (void **)(*(int *)((char *)(arg0) + 24));
    ((DW4VC_208_2 *)(temp_a0_2))->vX((int)(0), (int)((arg2 * 6) + 3));
}

void FUN_0015dae0(igPointSpriteExtView *self, unsigned int index, float value)
{
    self->_vertexArray->vfunc_51(index, value);
}

void FUN_0015db00(Sdb00 *arg0, int arg1, V2f *arg2) {
    V2f v;
    v.x = arg2->x;
    v.y = arg2->y;
    arg0->o->vX(arg1, &v);
}

void FUN_0015db40(igPointSpriteExtView *self)
{
    self->_vertexArray->vfunc_55();
}

void FUN_0015db60(igPointSpriteExtView *self)
{
    self->_vertexArray->vfunc_56();
}

}
