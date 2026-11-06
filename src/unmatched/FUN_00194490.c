int igObject_Destroy();
int thunk_FUN_002ed460__002ff810();
extern int DAT_00528250[4];

struct S {
    void *f0;
    char pad[24];
    void *f1c;
};

void *FUN_00194490(struct S *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00528250[0];
        if (&arg0->f1c) {
            p = arg0->f1c;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
