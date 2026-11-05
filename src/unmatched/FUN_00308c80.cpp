/* 0x00308c80 - FUN_00308c80. Smart-pointer slot (volatile) with plain copies, three vcalls (92, 200 and 136 with discarded R); the last parameter of the 00304f00 call is unsigned so its global is loaded before the receiver field. Alternate -O3. */
extern "C" {
void *FUN_002bc0d0(int);
void *FUN_00304f00(void *, int (*)(), unsigned);
void *Memory_GetAllocatorBySelector(int);
void igObject_Destroy(void *);
int igObject_GetAllocator(void *);
extern int DAT_004c22e8[4];
extern int DAT_00587020[4];
int FUN_00308c00();
}
struct R { int v; };
struct RO { int vt; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
class V92 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vA(); };
class V200 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual R vB(int); };
class V136 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual R vC(int); };
struct T { char p[28]; unsigned char f28; char q[3]; RO *f32; RO *f36; };
extern "C" {
void FUN_00308c80(T *arg0) {
    RO *volatile sp3C;
    RO *q;
    RO *old;
    RO *p;
    R sp38;
    R sp34;
    sp3C = (RO *)FUN_002bc0d0(igObject_GetAllocator(arg0));
    q = sp3C;
    if (q != 0) {
        q->u.w = q->u.w + 1;
    }
    old = arg0->f32;
    if (old != 0) {
        old->u.w = old->u.w - 1;
        if (old->u.b.cnt == 0) {
            igObject_Destroy(old);
        }
    }
    arg0->f32 = q;
    q = sp3C;
    if (q != 0) {
        q->u.w = q->u.w - 1;
        q = sp3C;
        if (q->u.b.cnt == 0) {
            igObject_Destroy(q);
        }
    }
    ((V92 *)arg0->f32)->vA();
    p = (RO *)FUN_00304f00(arg0->f32, &FUN_00308c00, DAT_004c22e8[0]);
    if (p != 0) {
        p->u.w = p->u.w + 1;
    }
    old = arg0->f36;
    if (old != 0) {
        old->u.w = old->u.w - 1;
        if (old->u.b.cnt == 0) {
            igObject_Destroy(old);
        }
    }
    arg0->f36 = p;
    sp38 = ((V200 *)arg0->f36)->vB(255);
    arg0->f28 = 1;
    sp34 = ((V136 *)Memory_GetAllocatorBySelector(DAT_00587020[0]))->vC(1);
}
}
