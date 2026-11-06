extern "C" {
float FUN_00123640(float, float);
extern float DAT_0058a5e0[4];
extern float DAT_0058a580[4];
extern float DAT_0058a5e8[4];
extern float DAT_0058a588[4];
float FUN_003a68e0(float fparg0);
}
float FUN_003a68e0(float fparg0) {
    return fparg0 + FUN_00123640(DAT_0058a5e0[0] - DAT_0058a580[0], DAT_0058a5e8[0] - DAT_0058a588[0]);
}
