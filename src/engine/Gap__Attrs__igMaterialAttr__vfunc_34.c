extern float DAT_004e1170[4];
extern float g_004e1170[4];
extern float g_004e1180[4];
extern float DAT_004e1174[4];
extern float DAT_004e1178[4];
extern float DAT_004e117c[4];
extern float DAT_004e1180[4];
extern float DAT_004e1184[4];
extern float DAT_004e1188[4];
extern float DAT_004e118c[4];
typedef struct { char pad[48]; float v[4]; } A;
void Gap__Attrs__igMaterialAttr__vfunc_34(A *a, float *b) {
    a->v[0] = b[0]; a->v[1] = b[1]; a->v[2] = b[2]; a->v[3] = b[3];
    { float lo = g_004e1170[0];
    if (a->v[0] < DAT_004e1170[0]) a->v[0] = lo; }
    if (a->v[1] < DAT_004e1174[0]) a->v[1] = DAT_004e1174[0];
    if (a->v[2] < DAT_004e1178[0]) a->v[2] = DAT_004e1178[0];
    if (a->v[3] < DAT_004e117c[0]) a->v[3] = DAT_004e117c[0];
    { float hi = g_004e1180[0];
    if (!(a->v[0] <= DAT_004e1180[0])) a->v[0] = hi; }
    if (!(a->v[1] <= DAT_004e1184[0])) a->v[1] = DAT_004e1184[0];
    if (!(a->v[2] <= DAT_004e1188[0])) a->v[2] = DAT_004e1188[0];
    if (!(a->v[3] <= DAT_004e118c[0])) a->v[3] = DAT_004e118c[0];
}
