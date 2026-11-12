igMetaObject *igLod_GetMetaObject(void)
{
    igMetaObject *g = g_igLod_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019d710();
    return g_igLod_metaObject[0];
}

int igLod_GetVTable(void) {
    struct W_19d660 o;
    int *p16;
    int r;
    int *p17;
    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[2] = 0;
    o.f[3] = 0;
    o.f[6] = 0;
    o.vt = &DAT_00528b20[0];
    p16 = &o.f[7];
    *p16 = 0;
    p17 = &o.f[8];
    *p17 = 0;
    o.f[15] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00528b20[0];
    FUN_001354b0(&o.f[15], -1);
    FUN_00198210((ObjectRefWord *)p17, -1);
    FUN_001354b0(p16, -1);
    FUN_00195a90((struct T_195a90 *)&o, 0);
    return r;
}

void FUN_0019d710(void)
{
    igMetaObject_RunStaticInit(igLod_Register);
}

void igLod_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igLod_metaObject),
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igLod_GetMetaObject,
        igLod_className,
        0x44, /* instance size */
        igLod_GetVTable,
        &igLod_InitFields,
        0, /* extra callback item */
        g_igLod_callbackList /* callback list */
    );
}

void thunk_igLod_GetMetaObject(void) {
    igLod_GetMetaObject();
}

void igLod_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s1;
    int temp_s0;
    int sp40[3];
    void *temp_a0;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;

    temp_s1 = (void *)DAT_00561898[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_0048bd10[0], 7);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_002c9780();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    ((igMetaField *)temp_s2)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s2)->_shallowCopyMethod = 2;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0019cd50();
    ((igMetaField *)temp_s2_2)->_persistent = 0;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2)));
    FUN_002ea4b0(temp_v0, -1);
    ((igIntMetaField *)temp_v0)->_persistent = 0;
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3)));
    FUN_002e3810(temp_v0_2, 0.0f);
    ((igFloatMetaField *)temp_v0_2)->_persistent = 0;
    temp_v0_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4)));
    FUN_002e3810(temp_v0_3, 0.0f);
    ((igFloatMetaField *)temp_v0_3)->_persistent = 0;
    temp_a0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5)));
    sp40[0] = 0;
    sp40[1] = 0;
    sp40[2] = 0;
    FUN_0018e470(temp_a0, sp40);
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002c9780();
    igMetaObject_NameFields(temp_s1, &DAT_0048bd30[0], &DAT_0048bd50[0], &DAT_0048bd70[0], temp_s0);
}

