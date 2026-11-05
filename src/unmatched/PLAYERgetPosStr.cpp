extern "C" {
int sprintf(int *, int *, int, int, int);
int FUN_00230298(float);
int Matrix44_GetTranslation(float *, float *);
int Matrix44_TranslateLocal(float *, float *);
int beMessenger_GetMatrix(float *, int, int);
int beMessenger_GetMatrixCount(int);
int beMessenger_SendNamed(int, int *, int, int, int *);
extern int DAT_0050db00[4];
extern int DAT_0050dda8[4];
extern int DAT_0050ddb0[4];
extern int DAT_0058a1c0[4];
extern int DAT_0058a2f0[4];
int *PLAYERgetPosStr(int arg0, float fparg0, float fparg1, float fparg2);
}

int *PLAYERgetPosStr(int arg0, float fparg0, float fparg1, float fparg2) {
    float sp90[3];
    float sp80[4];
    float sp40[16];
    int temp_s1;
    int temp_s0;

    beMessenger_SendNamed(DAT_0058a1c0[0], &DAT_0050dda8[0], 0, arg0, &DAT_0050ddb0[0]);
    if (beMessenger_GetMatrixCount(DAT_0058a1c0[0]) != 0) {
        beMessenger_GetMatrix(sp40, DAT_0058a1c0[0], 0);
        sp90[0] = fparg0;
        sp90[1] = fparg1;
        sp90[2] = fparg2;
        Matrix44_TranslateLocal(sp40, sp90);
        Matrix44_GetTranslation(sp40, sp80);
        temp_s1 = FUN_00230298(sp80[0]);
        temp_s0 = FUN_00230298(sp80[1]);
        sprintf(&DAT_0058a2f0[0], &DAT_0050db00[0], temp_s1, temp_s0, FUN_00230298(sp80[2]));
        return &DAT_0058a2f0[0];
    }
    return 0;
}
