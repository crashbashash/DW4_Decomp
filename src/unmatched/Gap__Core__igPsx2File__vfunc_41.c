typedef struct F { char pad[40]; int *f40; char pad2[28]; int f72; } F;
int FUN_0032c240();
int StringChunk_ReleaseHeader();

int *Gap__Core__igPsx2File__vfunc_41(F *arg0, int arg1) {
    int *volatile sp2C;
    int *t;
    int *s;
    int *p;
    int *a1;
    int v0;

    FUN_0032c240(&sp2C, arg0->f72, arg1);
    t = sp2C;
    if (t != 0) {
        t[-1] = t[-1] + 1;
    }
    p = arg0->f40;
    if (p != 0) {
        a1 = p - 2;
        v0 = p[-1] - 1;
        p[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    arg0->f40 = sp2C;
    s = sp2C;
    if (s != 0) {
        a1 = s - 2;
        v0 = s[-1] - 1;
        s[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    return s;
}
