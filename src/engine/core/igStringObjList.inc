void * FUN_002b9350(int arg0) {
    FUN_002b9470();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x5858E8), (MemoryPool *)arg0));
}

igMetaObject *FUN_002b9390(void) {
    if (g_igStringObjList_metaObject[0] == 0) {
        g_igStringObjList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData)));
    }
    return g_igStringObjList_metaObject[0];
}

igMetaObject *igStringObjList_GetMetaObject(void)
{
    igMetaObject *g = g_igStringObjList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b9470();
    return g_igStringObjList_metaObject[0];
}

int igStringObjList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((ObjectHeader *)&tmp[0]);
    tmp[0] = (int)&DAT_005332e0[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_002b9470(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringObjList_Register);
}

void igStringObjList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStringObjList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igStringObjList_GetMetaObject,
        igStringObjList_className,
        0x14, /* instance size */
        igStringObjList_GetVTable,
        0,
        0, /* extra callback item */
        g_igStringObjList_callbackList /* callback list */
    );
}

void thunk_igStringObjList_GetMetaObject(void) {
    igStringObjList_GetMetaObject();
}

