struct Mx { float f[16]; };
struct T { char p[44]; float f[16]; };
struct O { char p[12]; int f12; };
extern "C" { void *FUN_00236f80(int, int); int igMatrix44f_SetIdentity(Mx *); int FUN_001906d0(Mx *, void *); int FUN_001c51b0(int, int, Mx *); extern int DAT_0058c790[4]; }
extern "C" bool FUN_003a0570(O *o, int a1, int a2);
bool FUN_003a0570(O *o, int a1, int a2) {
    bool r = false;
    T *t = (T *)(((int *)FUN_00236f80(o->f12, DAT_0058c790[0]))[5]);
    Mx m;
    igMatrix44f_SetIdentity(&m);
    Mx *q = &m;
    float *p = (float *)q;
    p[0] = t->f[0];
    p[1] = t->f[1];
    p[2] = t->f[2];
    p[3] = t->f[3];
    p[4] = t->f[4];
    p[5] = t->f[5];
    p[6] = t->f[6];
    p[7] = t->f[7];
    p[8] = t->f[8];
    p[9] = t->f[9];
    p[10] = t->f[10];
    p[11] = t->f[11];
    p[12] = t->f[12];
    p[13] = t->f[13];
    p[14] = t->f[14];
    p[15] = t->f[15];
   
    FUN_001906d0(&m, (char *)t + 108);
    switch (FUN_001c51b0(a1, a2, &m)) {
    case 1: case 3: case 4: case 5: r = true; break;
    case 2: break;
    }
    return r;
}
