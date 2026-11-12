/* Setter for the material's reflected _shininess field. */
void Gap__Attrs__igMaterialAttr__vfunc_32(igMaterialAttr *self, float shininess) {
    self->_shininess = shininess;
}

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

void Gap__Attrs__igMaterialAttr__vfunc_33(A_13f0b0 *a, B_13f0b0 *b) {
    a->c[0] = b->c[0]; a->c[1] = b->c[1]; a->c[2] = b->c[2]; a->c[3] = b->c[3];
    clampColor(a->c, DAT_004e1170, DAT_004e1180);
}

void Gap__Attrs__igMaterialAttr__vfunc_36(S_13f1c0 *self, float *src) {
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

void Gap__Attrs__igMaterialAttr__vfunc_35(igMaterialAttr *material, const float *color) {
    material->_ambient[0] = color[0];
    material->_ambient[1] = color[1];
    material->_ambient[2] = color[2];
    material->_ambient[3] = color[3];
    clampColor(material->_ambient, DAT_004e1170, DAT_004e1180);
}

void Gap__Attrs__igMaterialAttr__vfunc_34(A_13f3e0 *a, float *b) {
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

void Gap__Attrs__igMaterialAttr__vfunc_24(char * arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_112(arg1, (arg0 + 32), (arg0 + 16), (arg0 + 64), (arg0 + 48), *(float *)((char *)(arg0) + 12));
}

void Gap__Attrs__igMaterialAttr__vfunc_26(MaterialAttrView *material, MaterialContextView *context) {
    igVec4f color;

    context->getMaterialDiffuse(&color);
    material->setDiffuse(&color);
    context->getMaterialAmbient(&color);
    material->setAmbient(&color);
    context->getMaterialSpecular(&color);
    material->setSpecular(&color);
    context->getMaterialEmission(&color);
    material->setEmission(&color);
    material->setShininess(context->getMaterialShininess());
}

