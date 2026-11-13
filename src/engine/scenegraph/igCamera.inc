void FUN_001a4520(int arg0) {
    FUN_001a4670();
    igMetaObject_CreateInstance(*(int *)0x561EA0, arg0);
}

igMetaObject *FUN_001a4560(void) {
    if (g_igCamera_metaObject[0] == 0) {
        g_igCamera_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igCamera_metaObject[0];
}

igMetaObject *igCamera_GetMetaObject(void)
{
    igMetaObject *g = g_igCamera_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a4670();
    return g_igCamera_metaObject[0];
}

int igCamera_GetVTable(void) {
    Obj_1a4600 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[2] = 0;
    o.w[3] = 0;
    o.vt = &DAT_0052a500[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_0052a500[0];
    FUN_00195970((struct T_195970 *)&o, 0);
    return r;
}

void FUN_001a4670(void)
{
    igMetaObject_RunStaticInit(igCamera_Register);
}

void igCamera_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igCamera_metaObject),
        igNode_Register,
        igNode_GetPublishedMetaObject,
        thunk_igCamera_GetMetaObject,
        igCamera_className,
        0x38, /* instance size */
        igCamera_GetVTable,
        &igCamera_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igCamera_GetMetaObject(void) {
    igCamera_GetMetaObject();
}

void igCamera_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)g_igCamera_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igCamera_ctorTable[0], 7);
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    FUN_002dc7a0(temp_v0, &DAT_0048ca90[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_001a47d0);
    FUN_002e3810(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)), 45.0f);
    igMetaObject_NameFields(temp_s0, &g_igCamera_fieldTable[0], &DAT_0048ca50[0], &DAT_0048ca70[0], temp_s2);
}

int FUN_001a47d0(void) {
    if (DAT_00561ee0[0] == 0) {
        DAT_00561ee0[0] = igMetaEnum_Create(&CameraType[0], &DAT_0048ca98[0], &DAT_0048caa0[0], 2);
    }
    return DAT_00561ee0[0];
}

