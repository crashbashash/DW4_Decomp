extern "C" {
int Matrix44_GetTranslation(void *, float *);
int Matrix44_Copy(int *, void *);
extern float DAT_0058a580[4];
extern float DAT_0058a584[4];
extern float DAT_0058a588[4];
extern int DAT_0058a590[4];
extern int DAT_0058a5a0[4];
extern float DAT_0058a5e0[4];
extern float DAT_0058a5e4[4];
extern float DAT_0058a5e8[4];
extern float DAT_0058a5f0[4];
extern int DAT_0058a5f8[4];
int FUN_003a6750(void *m, float *p);
}
int FUN_003a6750(void *m, float *p) {
    float v[3];
    float dx, dy, dz;
    Matrix44_GetTranslation(m, v);
    DAT_0058a580[0] = v[0];
    DAT_0058a584[0] = v[1];
    DAT_0058a588[0] = v[2];
    Matrix44_Copy(&DAT_0058a5a0[0], m);
    DAT_0058a590[0] = 0xC2C80000;
    DAT_0058a5e0[0] = p[0];
    DAT_0058a5e4[0] = p[1];
    DAT_0058a5e8[0] = p[2];
    dy = v[1] - p[1];
    dx = v[0] - p[0];
    dz = v[2] - p[2];
    DAT_0058a5f8[0] = 0;
    DAT_0058a5f0[0] = dx*dx + dy*dy + dz*dz;
    return 1;
}
