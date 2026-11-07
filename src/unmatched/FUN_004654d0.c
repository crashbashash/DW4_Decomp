typedef struct ViewerMatrix { float m[16]; } ViewerMatrix;
typedef struct ViewerVector4 { float v[4]; } ViewerVector4;
typedef struct ViewerPickView { char pad[8]; struct ViewerPickTarget *f8; char pad2[64]; int f76; int f80; } ViewerPickView;
typedef struct ViewerPickTarget { char pad[12]; float f12; char p2[136]; long long f152; } ViewerPickTarget;
int igMatrix44f_SetIdentity(ViewerMatrix *);
int FUN_00190ed0(ViewerMatrix *, float, float, float);
int FUN_00191230(ViewerMatrix *, float *, float *, float *);
int FUN_00191e30(void *, void *, ViewerMatrix *);
int FUN_001c5b30(int, ViewerMatrix *, long long);
int FUN_004578c0(ViewerPickTarget *, int *);
int Matrix44_GetTranslation(ViewerMatrix *, ViewerVector4 *);
int Matrix44_SetTranslation(ViewerMatrix *, ViewerVector4 *);
extern int DAT_0058cd38[4];
void FUN_004654d0(ViewerPickView *arg0) {
    float a, b, c;
    int sp90;
    ViewerVector4 sp80;
    ViewerMatrix sp40;
    int sp30[4];
    ViewerPickTarget *d;
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
