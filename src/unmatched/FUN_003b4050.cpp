
struct R { int w0; int rc; };
struct S {
    void *f0;
    char pad[48];
    int f52;
    int f56;
    int f60;
    int f64;
    int f68;
    int f72;
    int f76;
    int *f80;
    char pad2[24];
    struct R *f108;
};
extern "C" {
int ObjectRef_Destruct_001c6460(int *, int);
int FUN_003b2f30(int *, int);
int FUN_003b2fb0(int *, int);
int ObjectRef_Destruct_00150eb0(int *, int);
int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(R *);
int thunk_FUN_002ed460__002ff810(S *);
extern int DAT_0053dc30[4];
extern int DAT_0053f4f0[4];
void *FUN_003b4050(struct S *arg0, short arg1);
}
void *FUN_003b4050(struct S *arg0, short arg1) {
    struct R *p;
    int *h;
    int *a1;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_0053f4f0[0];
        if (&arg0->f108) {
            p = arg0->f108;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f80) {
            h = arg0->f80;
            if (h != 0) {
                a1 = h - 2;
                rc = h[-1] - 1;
                h[-1] = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = &DAT_0053dc30[0];
            ObjectRef_Destruct_001c6460(&arg0->f76, -1);
            ObjectRef_Destruct_00150eb0(&arg0->f72, -1);
            ObjectRef_Destruct_001c6460(&arg0->f68, -1);
            ObjectRef_Destruct_001c6460(&arg0->f64, -1);
            ObjectRef_Destruct_001c6460(&arg0->f60, -1);
            FUN_003b2f30(&arg0->f56, -1);
            FUN_003b2fb0(&arg0->f52, -1);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
