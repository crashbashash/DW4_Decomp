igMetaObject *igObjectPool_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001967c0();
    return g_igObjectPool_metaObject[0];
}

int igObjectPool_GetVTable(void) {
    struct Obj_196780 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052b5c0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001967c0(void)
{
    igMetaObject_RunStaticInit(igObjectPool_Register);
}

void igObjectPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igObjectPool_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igObjectPool_GetMetaObject,
        igObjectPool_className,
        0x20, /* instance size */
        igObjectPool_GetVTable,
        &igObjectPool_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igObjectPool_GetMetaObject(void) {
    igObjectPool_GetMetaObject();
}

void igObjectPool_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005612e8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048b1d0[0], 3);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), 0x32);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048b1e0[0], &DAT_0048b1f0[0], &DAT_0048b200[0], temp_s1);
}

