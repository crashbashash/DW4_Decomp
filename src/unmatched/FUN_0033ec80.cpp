extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(struct R *);
int thunk_FUN_002ed460__002ff810(struct S *);
extern int DAT_00524950[4];
extern int DAT_0052fde0[4];
extern int DAT_00539dc0[4];

struct R { int w0; int rc; };
struct S {
    void *f0;
    char pad[4];
    int *f8;
    char pad2[8];
    struct R *f20;
    struct R *f24;
};

void *FUN_0033ec80(struct S *arg0, short arg1) {
    struct R *p;
    int *h;
    int *a1;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00539dc0[0];
        if (&arg0->f24) {
            p = arg0->f24;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f20) {
            p = arg0->f20;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = &DAT_0052fde0[0];
            if (arg0 != 0) {
                arg0->f0 = &DAT_00524950[0];
                if (&arg0->f8) {
                    h = arg0->f8;
                    if (h != 0) {
                        a1 = h - 2;
                        rc = h[-1] - 1;
                        h[-1] = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*a1, a1);
                        }
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
}
