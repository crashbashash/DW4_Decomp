void FUN_002c3400(int arg0) {
    FUN_002c3520();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586120), (MemoryPool *)arg0);
}

igMetaObject *FUN_002c3440(void) {
    if (g_igInfoList_metaObject[0] == 0) {
        g_igInfoList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData)));
    }
    return g_igInfoList_metaObject[0];
}

igMetaObject *igInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c3520();
    return g_igInfoList_metaObject[0];
}

int igInfoList_GetVTable(void) {
    struct Obj_2c34e0 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00532600[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002c3520(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igInfoList_Register);
}

void igInfoList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igInfoList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igInfoList_GetMetaObject,
        igInfoList_className,
        0x14, /* instance size */
        igInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInfoList_callbackList /* callback list */
    );
}

void thunk_igInfoList_GetMetaObject(void) {
    igInfoList_GetMetaObject();
}

