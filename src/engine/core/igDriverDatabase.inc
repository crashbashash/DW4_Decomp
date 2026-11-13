int FUN_002c66f0(void) {
    if (DAT_005865c8[0] == 0) {
        DAT_005865c8[0] = ((int)igMetaEnum_Create((char *)(&SECTION_OVERRIDE_MODE[0]), (char **)(&DAT_004c0fb8[0]), &DAT_004c0fc0[0], 2));
    }
    return DAT_005865c8[0];
}

void FUN_002c6750(int arg0) {
    FUN_002c68f0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x5865D0), (MemoryPool *)arg0);
}

igMetaObject *igDriverDatabase_GetMetaObject(void)
{
    igMetaObject *g = g_igDriverDatabase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c68f0();
    return g_igDriverDatabase_metaObject[0];
}

int igDriverDatabase_GetVTable(void) {
    struct Obj_2c67e0 obj;
    int r;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00530630[0];
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.w[7] = 0;
    obj.w[8] = 0;
    obj.w[9] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj.vt = &DAT_00530630[0];
    FUN_001489a0(&obj.w[9], -1);
    FUN_001489a0(&obj.w[8], -1);
    FUN_00150180(&obj.w[7], -1);
    FUN_0019eeb0(&obj.w[4], -1);
    FUN_00227e70(&obj.w[3], -1);
    FUN_00227e70(&obj.w[2], -1);
    FUN_001a0790(&obj.w[1], -1);
    return r;
}

void FUN_002c68f0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDriverDatabase_Register);
}

void igDriverDatabase_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igDriverDatabase_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDriverDatabase_GetMetaObject,
        igDriverDatabase_className,
        0x38, /* instance size */
        igDriverDatabase_GetVTable,
        &igDriverDatabase_InitFields,
        0, /* extra callback item */
        g_igDriverDatabase_callbackList /* callback list */
    );
}

void thunk_igDriverDatabase_GetMetaObject(void) {
    igDriverDatabase_GetMetaObject();
}

void igDriverDatabase_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_s0;

    temp_s0 = (void *)g_igDriverDatabase_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igDriverDatabase_ctorTable[0], 0xC);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_002b9390();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_002c86a0();
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_002c86a0();
    ((igObjectRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_002bb030();
    FUN_002ea4b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4))), -1);
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5)));
    FUN_002dc7a0((igEnumMetaFieldView *)temp_v0, (const int *)&DAT_004c10b0[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_002c66f0);
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_002c4ce0();
    ((igObjectRefMetaField *)temp_s2_5)->_persistent = 0;
    ((igObjectRefMetaField *)temp_s2_5)->_deepCopyMethod = 3;
    ((igObjectRefMetaField *)temp_s2_5)->_shallowCopyMethod = 3;
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_002b9540();
    ((igObjectRefMetaField *)temp_s2_6)->_construct = 1;
    ((igObjectRefMetaField *)temp_s2_6)->_persistent = 0;
    ((igObjectRefMetaField *)temp_s2_6)->_deepCopyMethod = 3;
    ((igObjectRefMetaField *)temp_s2_6)->_shallowCopyMethod = 3;
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8)));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)FUN_002b9540();
    ((igObjectRefMetaField *)temp_s2_7)->_construct = 1;
    ((igObjectRefMetaField *)temp_s2_7)->_persistent = 0;
    ((igObjectRefMetaField *)temp_s2_7)->_deepCopyMethod = 3;
    ((igObjectRefMetaField *)temp_s2_7)->_shallowCopyMethod = 3;
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9)));
    ((igIntMetaField *)temp_v0_2)->_persistent = 0;
    ((igIntMetaField *)temp_v0_2)->_deepCopyMethod = 3;
    ((igIntMetaField *)temp_v0_2)->_shallowCopyMethod = 3;
    ((igBoolMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA)))->_persistent = 0;
    temp_v0_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xB)));
    ((igRawRefMetaField *)temp_v0_3)->_persistent = 0;
    ((igRawRefMetaField *)temp_v0_3)->_deepCopyMethod = 3;
    ((igRawRefMetaField *)temp_v0_3)->_shallowCopyMethod = 3;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igDriverDatabase_fieldTable[0], (igMetaField ***)&DAT_004c1050[0], &DAT_004c1080[0], temp_s1);
}

