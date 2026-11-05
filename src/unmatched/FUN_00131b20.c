/* 0x00131b20 — FUN_00131b20. m2c draft, hand-fixed; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int StringChunk_ReleaseHeader();
int thunk_FUN_002ed460__002ff810();
extern int DAT_0052fde0[4];
extern int DAT_00524950[4];

struct S {
    void *f0;
    char pad[4];
    void *f8;
};

void *FUN_00131b20(struct S *arg0, short arg1) {
    void *p;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_0052fde0[0];
        if (arg0 != 0) {
            arg0->f0 = &DAT_00524950[0];
            if (&arg0->f8) {
                p = arg0->f8;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader(*h, h);
                    }
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
