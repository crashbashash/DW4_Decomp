/* 0x0014c440 — FUN_0014c440. Hand-retyped from the m2c draft, verified byte-identical to retail by tools/verify.py. */
extern "C" int igObject_Destroy(void *);
extern "C" int thunk_FUN_002ed460__002ff810(void *);
extern int DAT_00526600[4];
extern int DAT_00527020[4];
extern int DAT_00530a10[4];
struct S1 { char pad4[4]; int f4; };
struct O { int *vt; char pad4[4]; S1 *m8; char pad12[4]; S1 *m16; char pad20[4]; S1 *m24; };
extern "C" O *FUN_0014c440(O *arg0, short arg1);
extern "C" O *FUN_0014c440(O *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_00526600[0];
        if (&arg0->m24) {
            S1 *t0 = arg0->m24;
            if (t0) { t0->f4 -= 1; if ((t0->f4 & 0x7fffff) == 0) igObject_Destroy(t0); }
        }
        if (arg0) {
            arg0->vt = &DAT_00527020[0];
            if (arg0) {
                arg0->vt = &DAT_00530a10[0];
                if (&arg0->m16) {
                    S1 *t = arg0->m16;
                    if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
                }
                if (&arg0->m8) {
                    S1 *t2 = arg0->m8;
                    if (t2) { t2->f4 -= 1; if ((t2->f4 & 0x7fffff) == 0) igObject_Destroy(t2); }
                }
            }
        }
        if (arg1 > 0) thunk_FUN_002ed460__002ff810(arg0);
    }
    return arg0;
}
