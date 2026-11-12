G_368310 *FUN_00368310(void) {
    G_368310 *g = DAT_00589b68[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00368450();
    return DAT_00589b68[0];
}

int beChangePosTransformInfoRam_GetVTable(void) {
    Obj_368360 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m40 = 0;
    obj.vt = &DAT_00534b70[0];
    obj.m44 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00534b70[0];
    obj.rel44();
    obj.vt = &DAT_00539e90[0];
    obj.rel40();
    return r;
}

void FUN_00368450(void)
{
    igMetaObject_RunStaticInit(beChangePosTransformInfoRam_Register);
}

void *beChangePosTransformInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beChangePosTransformInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beChangePosTransformInfoRam_GetMetaObject,
        beChangePosTransformInfoRam_className,
        0x30, /* instance size */
        beChangePosTransformInfoRam_GetVTable,
        beChangePosTransformInfoRam_InitFields,
        0, /* extra callback item */
        g_beChangePosTransformInfoRam_callbackList /* callback list */
    );
}

void beChangePosTransformInfoRam_GetMetaObject(void)
{
    FUN_00368310();
}

void beChangePosTransformInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589b68)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7778[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196190();
    igMetaObject_NameFields(temp_s0, &DAT_004c7780[0], &DAT_004c7788[0], &DAT_004c7790[0], temp_s2);
}

