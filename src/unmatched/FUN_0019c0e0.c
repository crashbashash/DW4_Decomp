/* 0x0019c0e0 — FUN_0019c0e0. m2c draft, hand-fixed; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int FUN_001958f0();
int FUN_00195970();
int igObject_Destroy();
int thunk_FUN_002ed460__002ff810();
extern int DAT_005294b0[4];
extern int DAT_00528dd0[4];

struct S {
    void *f0;
    char pad[28];
    void *f20;
};

void *FUN_0019c0e0(struct S *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_005294b0[0];
        if (&arg0->f20) {
            p = arg0->f20;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = &DAT_00528dd0[0];
            FUN_001958f0((char *)arg0 + 0x1C, -1);
            FUN_00195970(arg0, 0);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
