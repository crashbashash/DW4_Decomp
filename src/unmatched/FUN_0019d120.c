/* 0x0019d120 — FUN_0019d120. m2c draft, hand-fixed; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int FUN_0013bfe0();
int FUN_00195a90();
int igObject_Destroy();
int thunk_FUN_002ed460__002ff810();
extern int DAT_00528e70[4];
extern int DAT_005294b0[4];

struct S {
    void *f0;
    char pad[36];
    void *f28;
};

void *FUN_0019d120(struct S *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00528e70[0];
        if (&arg0->f28) {
            p = arg0->f28;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = &DAT_005294b0[0];
            FUN_0013bfe0((char *)arg0 + 0x20, -1);
            FUN_00195a90(arg0, 0);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
