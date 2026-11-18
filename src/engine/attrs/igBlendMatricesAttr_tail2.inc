igMetaObject *igBlendMatricesAttr_GetMeta(void) {
    return g_igBlendMatricesAttr_metaObject;
}

void igBlendMatricesAttr_UserPostLoad(Obj_142a00 *arg0) {
    if (arg0->f20 == 0) {
        arg0->f20 = arg0->f16;
    }
}

