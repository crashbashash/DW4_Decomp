extern float DAT_004e1170[4];
extern float DAT_004e1180[4];
typedef struct { char pad[16]; float c[4]; } A;
typedef struct { float c[4]; } B;
void Gap__Attrs__igMaterialAttr__vfunc_33(A *a, B *b) {
    float t0, t1;
    a->c[0] = b->c[0]; a->c[1] = b->c[1]; a->c[2] = b->c[2]; a->c[3] = b->c[3];
    t0 = DAT_004e1170[0];
    if (a->c[0] < ((const float *)DAT_004e1170)[0]) a->c[0] = t0;
    if (a->c[1] < DAT_004e1170[1]) a->c[1] = DAT_004e1170[1];
    if (a->c[2] < DAT_004e1170[2]) a->c[2] = DAT_004e1170[2];
    if (a->c[3] < DAT_004e1170[3]) a->c[3] = DAT_004e1170[3];
    t1 = DAT_004e1180[0];
    if (!(a->c[0] <= ((const float *)DAT_004e1180)[0])) a->c[0] = t1;
    if (!(a->c[1] <= DAT_004e1180[1])) a->c[1] = DAT_004e1180[1];
    if (!(a->c[2] <= DAT_004e1180[2])) a->c[2] = DAT_004e1180[2];
    if (!(a->c[3] <= DAT_004e1180[3])) a->c[3] = DAT_004e1180[3];
}
