typedef struct M { float m[16]; } M;
typedef struct V4 { float v[4]; } V4;
typedef struct C { char pad[8]; struct D *f8; char pad2[64]; int f76; int f80; } C;
typedef struct D { char pad[12]; float f12; char p2[136]; long long f152; } D;
int igMatrix44f_SetIdentity(M *);
int FUN_00190ed0(M *, float, float, float);
int FUN_00191230(M *, float *, float *, float *);
int FUN_00191e30(void *, void *, M *);
int FUN_001c5b30(int, M *, long long);
int FUN_004578c0(D *, int *);
int Matrix44_GetTranslation(M *, V4 *);
int Matrix44_SetTranslation(M *, V4 *);
extern int DAT_0058cd38[4];
void FUN_004654d0(C *arg0) {
    int sp30[4];
    M sp40;
    V4 sp80;
    int sp90;
    float c, b, a;
    D *d;
    if (arg0->f80 != 0) {
        igMatrix44f_SetIdentity(&sp40);
        d = arg0->f8;
        FUN_001c5b30(arg0->f76, &sp40, d->f152);
        a = 0; b = 0; c = 0;
        FUN_00191230(&sp40, &a, &b, &c);
        Matrix44_GetTranslation(&sp40, &sp80);
        FUN_00190ed0(&sp40, a, b, c);
        Matrix44_SetTranslation(&sp40, &sp80);
        FUN_00191e30(&sp90, (char *)d + 12, &sp40);
        sp30[0] = 2;
        sp30[1] = 0;
        sp30[2] = DAT_0058cd38[0];
        FUN_004578c0(d, sp30);
    }
}
