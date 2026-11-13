igMetaObject *FUN_002c86a0(void) {
    if (g_igStringRefListList_metaObject[0] == 0) {
        g_igStringRefListList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData)));
    }
    return g_igStringRefListList_metaObject[0];
}

igMetaObject *igStringRefListList_GetMetaObject(void)
{
    igMetaObject *g = g_igStringRefListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c8780();
    return g_igStringRefListList_metaObject[0];
}

int igStringRefListList_GetVTable(void) {
    struct Obj_2c8740 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_005321f0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002c8780(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringRefListList_Register);
}

void igStringRefListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStringRefListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igStringRefListList_GetMetaObject,
        igStringRefListList_className,
        0x14, /* instance size */
        igStringRefListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igStringRefListList_callbackList /* callback list */
    );
}

void thunk_igStringRefListList_GetMetaObject(void) {
    igStringRefListList_GetMetaObject();
}

