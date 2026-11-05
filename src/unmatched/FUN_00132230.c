int igObject_Destroy();
int thunk_FUN_002ed460__002ff810();
extern int DAT_00522c60[4];

struct R { int w0; int rc; };
struct S {
    void *f0;
    char pad[8];
    struct R *f12;
    char pad2[32];
    struct R *f48;
    char pad3[4];
    struct R *f56;
    char pad4[4];
    struct R *f64;
};

void *FUN_00132230(struct S *arg0, short arg1) {
    struct R *p;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00522c60[0];
        if (&arg0->f64) {
            p = arg0->f64;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f56) {
            p = arg0->f56;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f48) {
            p = arg0->f48;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f12) {
            p = arg0->f12;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
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
