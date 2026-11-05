/* Typed refcount release (-= 1 with the 23-bit mask); verified by tools/verify.py. */
extern "C" {
int igObject_Destroy(void *);
int thunk_FUN_002ed460__002ff810(void *);
extern int DAT_00538d40[4];
}
struct Q { char pad4[4]; int f4; };
struct O { int *vt; int p4; int p8; Q *m; };
extern "C" O *FUN_00347150(O *arg0, short arg1) {
    Q *t;

    if (arg0 != 0) {
        arg0->vt = &DAT_00538d40[0];
        if (&arg0->m != 0) {
            t = arg0->m;
            if (t != 0) {
                t->f4 -= 1;
                if ((t->f4 & 0x7fffff) == 0) {
                    igObject_Destroy(t);
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
