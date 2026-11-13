igMetaObject *FUN_001aa5c0(void) {
    if (g_igActorList_metaObject[0] == 0) {
        g_igActorList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igActorList_metaObject[0];
}

igMetaObject *igActorList_GetMetaObject(void)
{
    igMetaObject *g = g_igActorList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001aa6a0();
    return g_igActorList_metaObject[0];
}

int igActorList_GetVTable(void) {
    struct Obj_1aa660 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00529750[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001aa6a0(void)
{
    igMetaObject_RunStaticInit(igActorList_Register);
}

void igActorList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igActorList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igActorList_GetMetaObject,
        igActorList_className,
        0x14, /* instance size */
        igActorList_GetVTable,
        0,
        0, /* extra callback item */
        g_igActorList_callbackList /* callback list */
    );
}

void thunk_igActorList_GetMetaObject(void) {
    igActorList_GetMetaObject();
}

