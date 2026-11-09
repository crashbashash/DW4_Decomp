extern "C" {
int Memory_FreeBuffer(int);
int Memory_GetAllocatorBySelector(int);
int igObject_Destroy(void *);
extern int DAT_00587020[4];
}
union Ref { int w; struct { unsigned cnt:23; unsigned f:9; } b; };
struct Rc { int vt; Ref u; };
struct V2 { int a; int b; };
struct Inner { char p0[60]; int f60; int f64; char p1[8]; int f76; };
class Obj2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int v96(int *, int, int, int); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int v200(int, int, V2 *); Ref u; Inner *f8;};
class Al { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int v216(int); };
struct A1 { int vt; Ref u; char p0[16]; Al *f24; };
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int v168(int, int, V2 *); char p0[20]; Obj2 *f24;};

extern "C" int FUN_0015cb60(O *arg0, A1 *arg1, int *arg2, unsigned int arg3, int arg4);
extern "C" int FUN_0015cb60(O *arg0, A1 *arg1, int *arg2, unsigned int arg3, int arg4) {
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
