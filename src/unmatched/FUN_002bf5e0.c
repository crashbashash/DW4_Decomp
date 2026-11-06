int StringChunk_ReleaseHeader();
int thunk_FUN_002ed460__002ff810();
extern int DAT_0052ec50[4];
extern int DAT_0052f230[4];

struct S {
    void *f0;
    char pad[8];
    void *fc;
};

void *FUN_002bf5e0(struct S *arg0, short arg1) {
    void *p;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_0052ec50[0];
        if (arg0 != 0) {
            arg0->f0 = &DAT_0052f230[0];
            if (&arg0->fc) {
                p = arg0->fc;
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
