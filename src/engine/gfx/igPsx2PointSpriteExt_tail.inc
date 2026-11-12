igMetaObject *igPsx2PointSpriteExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2PointSpriteExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00153260();
    return g_igPsx2PointSpriteExt_metaObject[0];
}

int igPsx2PointSpriteExt_GetVTable(void) {
    struct O_1531c0 o;
    int temp_s0;
    char *pa = (char *)&o;

    igObject_InitHeader(&o);
    o.f8 = 0;
    o.vt = (int)&DAT_00526600[0];
    o.f16 = 0;
    o.f24 = 0;
    igMatrix44f_SetIdentity(&o.t[8]);
    igMatrix44f_SetIdentity(pa + 104);
    igMatrix44f_SetIdentity(pa + 168);
    igMatrix44f_SetIdentity(pa + 232);
    igMatrix44f_SetIdentity(pa + 296);
    o.vt = (int)&DAT_00525320[0];
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = (int)&DAT_00525320[0];
    FUN_0014c440((O *)&o, 0);
    return temp_s0;
}

void FUN_00153260(void)
{
    igMetaObject_RunStaticInit(igPsx2PointSpriteExt_Register);
}

void igPsx2PointSpriteExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2PointSpriteExt_metaObject,
        igPointSpriteExt_Register,
        igPointSpriteExt_GetPublishedMetaObject,
        thunk_igPsx2PointSpriteExt_GetMetaObject,
        igPsx2PointSpriteExt_className,
        0x18C, /* instance size */
        igPsx2PointSpriteExt_GetVTable,
        &igPsx2PointSpriteExt_InitFields,
        0, /* extra callback item */
        g_igPsx2PointSpriteExt_callbackList /* callback list */
    );
}

igMetaObject *FUN_001532f0(void) {
    return g_igPointSpriteExt_metaObject[0];
}

void igPsx2PointSpriteExt_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igPsx2PointSpriteExt_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489e90[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00150770();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00489e98[0], &DAT_00489ea0[0], &DAT_00489ea8[0], temp_s2);
}

