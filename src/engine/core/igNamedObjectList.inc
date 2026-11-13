igMetaObject *FUN_002be100(void) {
    if (g_igNamedObjectList_metaObject[0] == 0) {
        g_igNamedObjectList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igNamedObjectList_metaObject[0];
}

igMetaObject *igNamedObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igNamedObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002be1e0();
    return g_igNamedObjectList_metaObject[0];
}

int igNamedObjectList_GetVTable(void) {
    struct Obj_2be1a0 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00532c10[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002be1e0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igNamedObjectList_Register);
}

void igNamedObjectList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igNamedObjectList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igNamedObjectList_GetMetaObject,
        igNamedObjectList_className,
        0x14, /* instance size */
        igNamedObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNamedObjectList_callbackList /* callback list */
    );
}

void thunk_igNamedObjectList_GetMetaObject(void) {
    igNamedObjectList_GetMetaObject();
}

