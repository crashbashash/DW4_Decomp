extern "C" int igObject_Destroy(void *);
extern "C" int FUN_00100610(void *);
extern "C" int FUN_00236b10(void *, void *);
extern "C" int FUN_00236f30(void *, void *);
struct S1 { char pad4[4]; int f4; };
struct O { S1 *m0; S1 *m4; S1 *m8; S1 *m12; unsigned char f16; char pad17[3]; S1 *m20; S1 *m24; };
extern "C" O *FUN_00463910(O *arg0, short arg1);
extern "C" O *FUN_00463910(O *arg0, short arg1) {
    if (arg0) {
        if (arg0->m24 != 0) {
            FUN_00236b10(arg0->m0, arg0->m12);
            FUN_00236b10(arg0->m0, arg0->m8);
            FUN_00236b10(arg0->m0, arg0->m4);
            if (arg0->f16 != 0) {
                FUN_00236f30(arg0->m0, arg0->m20);
            }
        }
        if (&arg0->m24) {
            S1 *t = arg0->m24;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m20) {
            S1 *t = arg0->m20;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m12) {
            S1 *t = arg0->m12;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m8) {
            S1 *t = arg0->m8;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m4) {
            S1 *t = arg0->m4;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (arg0) {
            S1 *t = arg0->m0;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}
