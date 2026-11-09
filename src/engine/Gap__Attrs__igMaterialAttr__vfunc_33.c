extern float DAT_004e1170[4];
extern float DAT_004e1180[4];
typedef struct { char pad[16]; float c[4]; } A;
typedef struct { float c[4]; } B;
static inline void clampColor(float *c, const float *lo, const float *hi) {
    if (c[0] < lo[0]) c[0] = lo[0];
    if (c[1] < lo[1]) c[1] = lo[1];
    if (c[2] < lo[2]) c[2] = lo[2];
    if (c[3] < lo[3]) c[3] = lo[3];
    if (!(c[0] <= hi[0])) c[0] = hi[0];
    if (!(c[1] <= hi[1])) c[1] = hi[1];
    if (!(c[2] <= hi[2])) c[2] = hi[2];
    if (!(c[3] <= hi[3])) c[3] = hi[3];
}
void Gap__Attrs__igMaterialAttr__vfunc_33(A *a, B *b) {
    a->c[0] = b->c[0]; a->c[1] = b->c[1]; a->c[2] = b->c[2]; a->c[3] = b->c[3];
    clampColor(a->c, DAT_004e1170, DAT_004e1180);
}
