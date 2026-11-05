/* 0x003a6850 - 100 bytes. Lazily-computed global float with a stack vector; alternate compiler -O3,p. */
extern "C" {
float FUN_00123640(float, float);
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
        DAT_0058a590[0] = FUN_00123640(sp[0], sp[2]);
    }
    return DAT_0058a590[0];
}
