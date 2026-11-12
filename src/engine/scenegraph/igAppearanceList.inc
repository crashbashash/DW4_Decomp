igMetaObject *FUN_001a5fe0(void) {
    if (g_igAppearanceList_metaObject[0] == 0) {
        g_igAppearanceList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAppearanceList_metaObject[0];
}

igMetaObject *igAppearanceList_GetMetaObject(void)
{
    igMetaObject *g = g_igAppearanceList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a60c0();
    return g_igAppearanceList_metaObject[0];
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

void igAppearanceList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAppearanceList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAppearanceList_GetMetaObject,
        igAppearanceList_className,
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

