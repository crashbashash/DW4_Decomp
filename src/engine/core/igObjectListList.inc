igMetaObject *FUN_002c8810(void) {
    if (g_igObjectListList_metaObject[0] == 0) {
        g_igObjectListList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData)));
    }
    return g_igObjectListList_metaObject[0];
}

igMetaObject *igObjectListList_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c88f0();
    return g_igObjectListList_metaObject[0];
}

int igObjectListList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((ObjectHeader *)&tmp[0]);
    tmp[0] = (int)&DAT_00532180[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_002c88f0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igObjectListList_Register);
}

void igObjectListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igObjectListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igObjectListList_GetMetaObject,
        igObjectListList_className,
        0x14, /* instance size */
        igObjectListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igObjectListList_callbackList /* callback list */
    );
}

void thunk_igObjectListList_GetMetaObject(void) {
    igObjectListList_GetMetaObject();
}

