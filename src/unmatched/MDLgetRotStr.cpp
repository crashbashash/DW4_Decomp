extern "C" {
float FUN_00123640(float, float);
int sprintf(int *, int *, int, int, int);
int igMatrix44f_SetIdentity(float *);
int FUN_001908f0(float *, int);
int FUN_00192f50(float *, int *, float *);
int fptodp(float);
extern int DAT_004e1098[];
extern int DAT_0050db00[];
extern int DAT_0058a1e8[];
extern int DAT_0058a270[];
int *MDLgetRotStr(float fparg0, float fparg1, float fparg2);
}

int *MDLgetRotStr(float fparg0, float fparg1, float fparg2) {
    float vec[4];
    float mat[16];
    float ang;
    int a;
    int b;
    igMatrix44f_SetIdentity(mat);
    FUN_001908f0(mat, DAT_0058a1e8[0]);
    FUN_00192f50(vec, DAT_004e1098, mat);
    ang = FUN_00123640(vec[0], vec[2]);
    a = fptodp(fparg0);
    b = fptodp(57.29578f * ang + fparg1);
    sprintf(DAT_0058a270, DAT_0050db00, a, b, fptodp(fparg2));
    return DAT_0058a270;
}
