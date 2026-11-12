void FUN_00132b60(int arg0) {
    FUN_00132cf0();
    igMetaObject_CreateInstance(*(int *)0x55EDA0, arg0);
}

int FUN_00132ba0(void) {
    if (DAT_0055eda0[0] == 0) {
        DAT_0055eda0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055eda0[0];
}

igMetaObject *igTextureAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureAttr_metaObject[0] != 0) {
        ready = (g_igTextureAttr_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00132cf0();
done:
    return g_igTextureAttr_metaObject[0];
}

int igTextureAttr_GetVTable(void) {
    union U_132c40 u;
    int temp_s;
    char *p136;
    char *p128;
    char *p92;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00522c60[0];
    p92 = &u.b[12];
    *(int *)p92 = 0;
    p128 = &u.b[48];
    *(int *)p128 = 0;
    p136 = &u.b[56];
    *(int *)p136 = 0;
    *(int *)&u.b[64] = 0;
    temp_s = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00522c60[0];
    FUN_00132130((Ref **)&u.b[64], -1);
    FUN_001321b0((void **)p136, -1);
    FUN_00132390((O *)p128, -1);
    FUN_00130140((void **)p92, -1);
    return temp_s;
}

void FUN_00132cf0(void)
{
    igMetaObject_RunStaticInit(igTextureAttr_Register);
}

void igTextureAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureAttr_GetMetaObject,
        igTextureAttr_className,
        0x48, /* instance size */
        igTextureAttr_GetVTable,
        &igTextureAttr_InitFields,
        0, /* extra callback item */
        g_igTextureAttr_callbackList /* callback list */
    );
}

void thunk_igTextureAttr_GetMetaObject(void) {
    igTextureAttr_GetMetaObject();
}

void igTextureAttr_InitFields(void) {
    int temp_s0;
    int temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_7;

    temp_s0 = DAT_0055eda0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485cf0[0], 0xF);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    FUN_002dc7a0(temp_v0, &DAT_00485df0[0]);
    *(void **)&((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (void *)FUN_00149980;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    FUN_002dc7a0(temp_v0_2, &DAT_00485df8[0]);
    *(void **)&((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (void *)FUN_00149980;
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    FUN_002dc7a0(temp_v0_3, &DAT_00485e00[0]);
    *(void **)&((igEnumMetaField *)temp_v0_3)->_getMetaEnumFunction = (void *)FUN_00149920;
    temp_v0_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    FUN_002dc7a0(temp_v0_4, &DAT_00485e08[0]);
    *(void **)&((igEnumMetaField *)temp_v0_4)->_getMetaEnumFunction = (void *)FUN_00149920;
    temp_v0_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    FUN_002ea4b0(temp_v0_5, -1);
    ((igIntMetaField *)temp_v0_5)->_persistent = 0;
    ((igIntMetaField *)temp_v0_5)->_deepCopyMethod = 4;
    ((igIntMetaField *)temp_v0_5)->_shallowCopyMethod = 4;
    ((igIntMetaField *)temp_v0_5)->_isAlikeShallowMethod = 3;
    temp_v0_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    FUN_002dc7a0(temp_v0_6, &DAT_00485e10[0]);
    *(void **)&((igEnumMetaField *)temp_v0_6)->_getMetaEnumFunction = (void *)FUN_00149860;
    temp_v0_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    FUN_002dc7a0(temp_v0_7, &DAT_00485e18[0]);
    *(void **)&((igEnumMetaField *)temp_v0_7)->_getMetaEnumFunction = (void *)FUN_001498c0;
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0014dfb0();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00131160();
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB), 1);
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00132ff0();
    ((igObjectRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0014a040();
    ((igObjectRefMetaField *)temp_s2_4)->_persistent = 0;
    ((igObjectRefMetaField *)temp_s2_4)->_deepCopyMethod = 1;
    ((igObjectRefMetaField *)temp_s2_4)->_shallowCopyMethod = 1;
    ((igObjectRefMetaField *)temp_s2_4)->_isAlikeShallowMethod = 3;
    ((igRawRefMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE))->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00485d30[0], &DAT_00485d70[0], &DAT_00485db0[0], temp_s1);
}

