typedef struct R { int w0; unsigned rc; } R;
int igInsightPlugin_GetMetaObject();
int igMetaObject_CountTree(int);
int FUN_002fe300(int, int);
int igObject_GetAllocator(int);
int FUN_002fd6e0(R **, int, int);
int igObject_Destroy(R *);
int FUN_00236dd0(int, R *);
void FUN_00236ca0(int arg0) {
    R *sp68;
    R *volatile sp6C;
    R *q;
    int i;
    int n;
    int meta;
    n = igMetaObject_CountTree(meta = igInsightPlugin_GetMetaObject());
    for (i = 0; i < n; i++) {
        int s4 = FUN_002fe300(meta, i);
        FUN_002fd6e0(&sp68, s4, igObject_GetAllocator(arg0));
        sp6C = sp68;
        q = sp6C;
        if (q != 0) {
            q->rc = q->rc + 1;
        }
        if (sp68 != 0) {
            sp68->rc = sp68->rc - 1;
            if ((sp68->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(sp68);
            }
        }
        q = sp6C;
        if (q != 0) {
            FUN_00236dd0(arg0, q);
        }
        q = sp6C;
        if (q != 0) {
            q->rc = q->rc - 1;
            if ((q->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(q);
            }
        }
    }
}
