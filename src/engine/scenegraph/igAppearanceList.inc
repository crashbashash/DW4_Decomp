igMetaObject *g_igAppearanceList_metaObject;

igMetaObject *FUN_001a5fe0(void) {
    if (g_igAppearanceList_metaObject == 0) {
        g_igAppearanceList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAppearanceList_metaObject;
}

igMetaObject *igAppearanceList_GetMetaObject(void)
{
    igMetaObject *g = g_igAppearanceList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a60c0();
    return g_igAppearanceList_metaObject;
}

int igAppearanceList_GetVTable(void) {
    struct Obj_1a6080 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052a0f0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001a60c0(void)
{
    igMetaObject_RunStaticInit(igAppearanceList_Register);
}

static igMetaObjectCallback g_igAppearanceList_callbackList[] = { FUN_001a6450, 0 };

void igAppearanceList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAppearanceList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAppearanceList_GetMetaObject,
        "igAppearanceList",
        0x14, /* instance size */
        igAppearanceList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAppearanceList_callbackList /* callback list */
    );
}

void thunk_igAppearanceList_GetMetaObject(void) {
    igAppearanceList_GetMetaObject();
}

