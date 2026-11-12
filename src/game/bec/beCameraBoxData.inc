void *FUN_003691b0(void) {
    struct G *g = DAT_00589c08[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003692d0();
    }
    return DAT_00589c08[0];
}

int beCameraBoxData_GetVTable(void) {
    struct Obj_369200 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005349d0[0];
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_005349d0[0];
    FUN_00341160((O *)(&obj.w[5]), (short)(-1));
    FUN_00341160((O *)(&obj.w[4]), (short)(-1));
    FUN_00341160((O *)(&obj.w[3]), (short)(-1));
    FUN_0019c220(&obj.w[2], -1);
    FUN_00343260((ObjectRefWord *)(&obj.w[1]), -1);
    return r;
}

void FUN_003692d0(void)
{
    igMetaObject_RunStaticInit(beCameraBoxData_Register);
}

void *beCameraBoxData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCameraBoxData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCameraBoxData_GetMetaObject,
        beCameraBoxData_className,
        0x1c, /* instance size */
        beCameraBoxData_GetVTable,
        beCameraBoxData_InitFields,
        0, /* extra callback item */
        g_beCameraBoxData_callbackList /* callback list */
    );
}

void beCameraBoxData_GetMetaObject(void)
{
    FUN_003691b0();
}

void beCameraBoxData_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s1;

    temp_s1 = (void *)((int *)DAT_00589c08)[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c78d0[0], 5);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00196930();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0019f930();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00195e70();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00195e70();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00195e70();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004c78f0[0], &DAT_004c7910[0], &DAT_004c7930[0], temp_s0);
}

