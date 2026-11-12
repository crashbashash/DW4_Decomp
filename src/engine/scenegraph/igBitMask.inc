int FUN_001a4d90(void) {
    if (DAT_00561f58[0] == 0) {
        DAT_00561f58[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00561f58[0];
}

igMetaObject *igBitMask_GetMetaObject(void)
{
    igMetaObject *g = g_igBitMask_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a4e70();
    return g_igBitMask_metaObject[0];
}

int igBitMask_GetVTable(void) {
    struct Obj_1a4e30 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052a340[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001a4e70(void)
{
    igMetaObject_RunStaticInit(igBitMask_Register);
}

void igBitMask_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igBitMask_metaObject),
        igUnsignedIntList_Register,
        igUnsignedIntList_GetPublishedMetaObject,
        thunk_igBitMask_GetMetaObject,
        igBitMask_className,
        0x18, /* instance size */
        igBitMask_GetVTable,
        &igBitMask_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBitMask_GetMetaObject(void) {
    igBitMask_GetMetaObject();
}

int FUN_001a4f00(void) {
    return DAT_00586858[0];
}

void igBitMask_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00561f58[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048cb98[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048cba0[0], &DAT_0048cba8[0], &DAT_0048cbb0[0], temp_s1);
}

