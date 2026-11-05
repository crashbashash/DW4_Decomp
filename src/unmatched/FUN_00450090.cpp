extern "C" int igObject_Destroy(void *);
extern "C" int thunk_FUN_002ed460__002ff810(void *);
extern int DAT_00541300[4];
struct S1 { char pad4[4]; int f4; };
struct O { int *vt; char pad4[8]; S1 *m12; S1 *m16; S1 *m20; char pad24[4]; S1 *m28; };
extern "C" O *FUN_00450090(O *arg0, short arg1);
extern "C" O *FUN_00450090(O *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_00541300[0];
        if (&arg0->m28) {
            S1 *t = arg0->m28;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m20) {
            S1 *t = arg0->m20;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m16) {
            S1 *t = arg0->m16;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m12) {
            S1 *t = arg0->m12;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (arg1 > 0) thunk_FUN_002ed460__002ff810(arg0);
    }
    return arg0;
}
