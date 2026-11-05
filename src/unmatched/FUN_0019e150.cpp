extern "C" int igObject_Destroy(void *);
extern "C" int thunk_FUN_002ed460__002ff810(void *);
extern int DAT_00528250[4];
extern int DAT_00528cf0[4];
struct S1 { char pad4[4]; int f4; };
struct O { int *vt; char pad4[24]; S1 *m28; S1 *m32; S1 *m36; S1 *m40; char pad44[8]; S1 *m52; S1 *m56; };
extern "C" O *FUN_0019e150(O *arg0, short arg1);
extern "C" O *FUN_0019e150(O *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_00528cf0[0];
        if (&arg0->m56) {
            S1 *t = arg0->m56;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m52) {
            S1 *t = arg0->m52;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m40) {
            S1 *t = arg0->m40;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m36) {
            S1 *t = arg0->m36;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m32) {
            S1 *t = arg0->m32;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (arg0) {
            arg0->vt = &DAT_00528250[0];
            if (&arg0->m28) {
                S1 *t = arg0->m28;
                if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
            }
        }
        if (arg1 > 0) thunk_FUN_002ed460__002ff810(arg0);
    }
    return arg0;
}
