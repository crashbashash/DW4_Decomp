void igLightingStateAttr_CreateInstance(int arg0) {
    FUN_00135f40();
    igMetaObject_CreateInstance(*(int *)0x55F048, arg0);
}

igMetaObject *FUN_00135e60(void) {
    if (g_igLightingStateAttr_metaObject[0] == 0) {
        g_igLightingStateAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igLightingStateAttr_metaObject[0];
}

igMetaObject *igLightingStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igLightingStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00135f40();
    return g_igLightingStateAttr_metaObject[0];
}

int igLightingStateAttr_GetVTable(void) {
    struct Obj_135f00 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_005235e0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00135f40(void)
{
    igMetaObject_RunStaticInit(igLightingStateAttr_Register);
}

void igLightingStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightingStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igLightingStateAttr_GetMetaObject,
        igLightingStateAttr_className,
        0x10, /* instance size */
        igLightingStateAttr_GetVTable,
        &igLightingStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igLightingStateAttr_GetMetaObject(void) {
    igLightingStateAttr_GetMetaObject();
}

void igLightingStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igLightingStateAttr_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igLightingStateAttr_ctorTable[0], 1);
    igMetaObject_NameFields(temp_s0, &g_igLightingStateAttr_fieldTable[0], &DAT_004862f8[0], &DAT_00486300[0], temp_s1);
}

