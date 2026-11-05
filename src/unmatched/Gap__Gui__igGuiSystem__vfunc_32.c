struct P { int a, b, c; };
extern int DAT_0058c3d0[4];
int FUN_004578c0(void *, struct P *);
int Gap__Gui__igGuiSystem__vfunc_32(int *self, int x, int y) {
    struct P p;
    float *f = (float *)self[3];
    f[3] = (float)x;
    f[4] = (float)y;
    p.a = 2;
    p.b = 0;
    p.c = DAT_0058c3d0[0];
    FUN_004578c0((void *)self[3], &p);
    return 0;
}
