typedef struct M { int a; int b; int c; } M;
typedef struct T { char p[208]; char f208; } T;
typedef struct S { char p0[20]; T *f20; char p1[28]; int f52; int f56; int f60; int pad; int f68; char p2[104]; int f176; } S;
extern int DAT_0058cab8[4];
int FUN_00453a20(int, int);
int FUN_004578c0(T *, M *);
int FUN_00462e50(S *);
void FUN_00462e90(S *arg0) {
    switch (arg0->f176) {
    case 0: {
        M m;
        arg0->f20->f208 = 0;
        m.a = 2;
        m.b = 0;
        m.c = DAT_0058cab8[0];
        FUN_004578c0(arg0->f20, &m);
        break;
    }
    case 1: {
        M m;
        FUN_00453a20(arg0->f52, arg0->f60);
        FUN_00453a20(arg0->f52, arg0->f68);
        FUN_00453a20(arg0->f52, arg0->f56);
        arg0->f20->f208 = 0;
        m.a = 2;
        m.b = 0;
        m.c = DAT_0058cab8[0];
        FUN_004578c0(arg0->f20, &m);
        break;
    }
    case 2: {
        M m;
        arg0->f20->f208 = 1;
        m.a = 2;
        m.b = 0;
        m.c = DAT_0058cab8[0];
        FUN_004578c0(arg0->f20, &m);
        FUN_00462e50(arg0);
        break;
    }
    }
}
