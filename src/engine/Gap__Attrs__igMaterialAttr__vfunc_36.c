extern float DAT_004e1170[4], DAT_004e1180[4];
extern float D_004e1170[4], D_004e1174[4], D_004e1178[4], D_004e117c[4], D_004e1180[4], D_004e1184[4], D_004e1188[4], D_004e118c[4];
typedef struct S { char pad[64]; float r, g, b, a; } S;
void Gap__Attrs__igMaterialAttr__vfunc_36(S *self, float *src) {
    self->r = src[0];
    self->g = src[1];
    self->b = src[2];
    self->a = src[3];
    { float lo = DAT_004e1170[0]; if (self->r < D_004e1170[0]) self->r = lo; }
    if (self->g < D_004e1174[0]) self->g = D_004e1174[0];
    if (self->b < D_004e1178[0]) self->b = D_004e1178[0];
    if (self->a < D_004e117c[0]) self->a = D_004e117c[0];
    { float hi = DAT_004e1180[0]; if (self->r > D_004e1180[0]) self->r = hi; }
    if (self->g > D_004e1184[0]) self->g = D_004e1184[0];
    if (self->b > D_004e1188[0]) self->b = D_004e1188[0];
    if (self->a > D_004e118c[0]) self->a = D_004e118c[0];
}
