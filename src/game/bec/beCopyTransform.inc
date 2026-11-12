void *FUN_00367e50(void) {
    struct G *g = DAT_00589b48[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00367f40();
    }
    return DAT_00589b48[0];
}

int beCopyTransform_GetVTable(void) {
    CopyTransformView transform;
    return *(int *)((char *)&transform + *(int *)((char *)DAT_00586dc8[0] + 916));
}

void FUN_00367f40(void)
{
    igMetaObject_RunStaticInit(beCopyTransform_Register);
}

void *beCopyTransform_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCopyTransform_metaObject,
        igTransform_Register,
        igTransform_GetPublishedMetaObject,
        beCopyTransform_GetMetaObject,
        beCopyTransform_className,
        0x70, /* instance size */
        beCopyTransform_GetVTable,
        beCopyTransform_InitFields,
        FUN_00368090, /* extra callback item */
        g_beCopyTransform_callbackList /* callback list */
    );
}

void beCopyTransform_GetMetaObject(void)
{
    FUN_00367e50();
}

void beCopyTransform_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589b48)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7728[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196190();
    igMetaObject_NameFields(temp_s0, &DAT_004c7730[0], &DAT_004c7738[0], &DAT_004c7740[0], temp_s2);
}

void FUN_00368090(void)
{
    FUN_0037b760();
}

