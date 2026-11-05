extern "C" int igObject_Destroy(void *);
extern "C" int thunk_FUN_002ed460__002ff810(void *);
extern int DAT_00527020[4];
extern int DAT_00530a10[4];
struct S1 { char pad4[4]; int f4; };
struct O { int *vt; char pad4[4]; S1 *m8; char pad12[4]; S1 *m16; };
extern "C" O *FUN_0014c580(O *arg0, short arg1);
extern "C" O *FUN_0014c580(O *arg0, short arg1) {
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
        if (arg1 > 0) thunk_FUN_002ed460__002ff810(arg0);
    }
    return arg0;
}
