extern "C" {
float FUN_00123640(float, float);
int sprintf(int *, int *, int, int, int, int);
int FUN_00192f50(float *, int *, float *);
int FUN_00230298(float);
int Matrix44_GetTranslation(float *, float *);
int beMessenger_AppendInt(int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetMatrix(float *, int, int);
int beMessenger_SelectGroup(int, int *);
extern int DAT_004e1098[4];
extern int DAT_0050dd58[4];
extern int DAT_0050dd80[4];
extern int DAT_0050dd90[4];
extern int DAT_0058a1c0[4];
extern int DAT_0058a2b0[4];
int *PLAYERgetDataStr(int arg0, int arg1, float fparg0);
}

int *PLAYERgetDataStr(int arg0, int arg1, float fparg0) {
    float ang;
    float v[3];
    float mat[16];
    float t[3];
    int c, b, a;

    beMessenger_SelectGroup(DAT_0058a1c0[0], &DAT_0050dd58[0]);
    beMessenger_AppendInt(DAT_0058a1c0[0], arg0);
    beMessenger_AppendInt(DAT_0058a1c0[0], arg1);
    beMessenger_DispatchSelected(DAT_0058a1c0[0], &DAT_0050dd80[0]);
    beMessenger_GetMatrix(mat, DAT_0058a1c0[0], 0);
    Matrix44_GetTranslation(mat, t);
    FUN_00192f50(v, &DAT_004e1098[0], mat);
    ang = FUN_00123640(v[0], v[2]);
    sprintf(&DAT_0058a2b0[0], &DAT_0050dd90[0], (FUN_00230298(t[0])), (FUN_00230298(t[1])), (FUN_00230298(t[2])), FUN_00230298((57.29578f * ang) + fparg0));
    return &DAT_0058a2b0[0];
}
