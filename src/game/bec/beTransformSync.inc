void *FUN_00341070(void) {
    struct G *g = DAT_00587c08[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003411e0();
    }
    return DAT_00587c08[0];
}

int beTransformSync_GetVTable(void) {
    TransformSyncView transform;
    return *(int *)((char *)&transform + *(int *)((char *)DAT_00586dc8[0] + 916));
}

O *FUN_00341160(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

void FUN_003411e0(void)
{
    igMetaObject_RunStaticInit(beTransformSync_Register);
}

void *beTransformSync_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTransformSync_metaObject,
        igTransform_Register,
        igTransform_GetPublishedMetaObject,
        beTransformSync_GetMetaObject,
        beTransformSync_className,
        0x70, /* instance size */
        beTransformSync_GetVTable,
        beTransformSync_InitFields,
        0, /* extra callback item */
        g_beTransformSync_callbackList /* callback list */
    );
}

void beTransformSync_GetMetaObject(void)
{
    FUN_00341070();
}

void beTransformSync_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00587c08)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3358[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00195e70();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c3360[0], &DAT_004c3368[0], &DAT_004c3370[0], temp_s2);
}

