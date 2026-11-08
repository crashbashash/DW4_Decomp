extern "C" {
float atan2f(float, float);
int FUN_00192f50(float *, int *, int *);
extern int DAT_004e1098[4];
extern float DAT_0058a590[4];
extern int DAT_0058a5a0[4];
float FUN_003a6850(void);
}
float FUN_003a6850(void) {
    float sp[4];
    if (DAT_0058a590[0] == -100.0f) {
        FUN_00192f50(sp, &DAT_004e1098[0], &DAT_0058a5a0[0]);
        DAT_0058a590[0] = atan2f(sp[0], sp[2]);
    }
    return DAT_0058a590[0];
}
