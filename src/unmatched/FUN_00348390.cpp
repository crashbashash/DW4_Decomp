extern "C" {
int igObject_Destroy(struct R *);
int thunk_FUN_002ed460__002ff810(struct S *);
extern int DAT_0053c070[4];

struct R { int w0; int rc; };
struct S {
    void *f0;
    char pad[44];
    struct R *f48;
    struct R *f52;
    struct R *f56;
};

void *FUN_00348390(struct S *arg0, short arg1) {
    struct R *p;

    if (arg0 != 0) {
        arg0->f0 = &DAT_0053c070[0];
        if (&arg0->f56) {
            p = arg0->f56;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                    asm { nop }
                }
            }
        }
        if (&arg0->f52) {
            p = arg0->f52;
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
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
}
