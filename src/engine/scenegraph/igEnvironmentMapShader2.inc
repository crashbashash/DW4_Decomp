igMetaObject *igEnvironmentMapShader2_GetMetaObject(void)
{
    igMetaObject *g = g_igEnvironmentMapShader2_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a15a0();
    return g_igEnvironmentMapShader2_metaObject[0];
}

void FUN_001a15a0(void)
{
    igMetaObject_RunStaticInit(igEnvironmentMapShader2_Register);
}

void igEnvironmentMapShader2_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igEnvironmentMapShader2_metaObject),
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igEnvironmentMapShader2_GetMetaObject,
        igEnvironmentMapShader2_className,
        0x70, /* instance size */
        0,
        &igEnvironmentMapShader2_InitFields,
        0, /* extra callback item */
        g_igEnvironmentMapShader2_callbackList /* callback list */
    );
}

void thunk_igEnvironmentMapShader2_GetMetaObject(void) {
    igEnvironmentMapShader2_GetMetaObject();
}

void igEnvironmentMapShader2_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_11;
    void *temp_s2_12;
    void *temp_s2_13;
    void *temp_s2_14;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)g_igEnvironmentMapShader2_metaObject)[0]);
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igEnvironmentMapShader2_ctorTable[0], 0x15);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00131fe0();
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00132850();
    FUN_002e3810(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3)), 1.0f);
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00132ba0();
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7))))->_persistent = 0;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0013abd0();
    ((igObjectRefMetaField *)temp_s2_4)->_construct = 1;
    ((igMetaField *)temp_s2_4)->_persistent = 0;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0013abd0();
    ((igObjectRefMetaField *)temp_s2_5)->_construct = 1;
    ((igMetaField *)temp_s2_5)->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA))))->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB))))->_persistent = 0;
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00132850();
    ((igMetaField *)temp_s2_6)->_persistent = 0;
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xD)));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_001325e0();
    ((igMetaField *)temp_s2_7)->_persistent = 0;
    temp_s2_8 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xE)));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_00131ca0();
    ((igMetaField *)temp_s2_8)->_persistent = 0;
    temp_s2_9 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xF)));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_001325e0();
    ((igMetaField *)temp_s2_9)->_persistent = 0;
    temp_s2_10 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x10)));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_00131ca0();
    ((igMetaField *)temp_s2_10)->_persistent = 0;
    temp_s2_11 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x11)));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = FUN_00139640();
    ((igMetaField *)temp_s2_11)->_persistent = 0;
    temp_s2_12 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x12)));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = FUN_00132850();
    ((igMetaField *)temp_s2_12)->_persistent = 0;
    temp_s2_13 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x13)));
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = FUN_001325e0();
    ((igMetaField *)temp_s2_13)->_persistent = 0;
    temp_s2_14 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x14)));
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = FUN_00131ca0();
    ((igMetaField *)temp_s2_14)->_persistent = 0;
    igMetaObject_NameFields(temp_s1, &g_igEnvironmentMapShader2_fieldTable[0], &DAT_0048c210[0], &DAT_0048c270[0], temp_s0);
    ((igMetaObject *)(((void * *)g_igEnvironmentMapShader2_metaObject)[0]))->_abstractProxy = (int)(&thunk_igPsx2EnvironmentMapShader_GetMetaObject);
}

