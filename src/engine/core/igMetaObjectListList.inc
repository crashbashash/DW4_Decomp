igMetaObject *FUN_002c8ca0(void) {
    if (g_igMetaObjectListList_metaObject[0] == 0) {
        g_igMetaObjectListList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMetaObjectListList_metaObject[0];
}

igMetaObject *igMetaObjectListList_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaObjectListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c8d80();
    return g_igMetaObjectListList_metaObject[0];
}

int igMetaObjectListList_GetVTable(void) {
    struct Obj_2c8d40 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00532030[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002c8d80(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaObjectListList_Register);
}

void igMetaObjectListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMetaObjectListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMetaObjectListList_GetMetaObject,
        igMetaObjectListList_className,
        0x14, /* instance size */
        igMetaObjectListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMetaObjectListList_callbackList /* callback list */
    );
}

void thunk_igMetaObjectListList_GetMetaObject(void) {
    igMetaObjectListList_GetMetaObject();
}

