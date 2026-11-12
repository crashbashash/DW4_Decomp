void * FUN_002c1580(int arg0) {
    FUN_002c1650();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586018), (MemoryPool *)arg0));
}

igMetaObject *igMediaList_GetMetaObject(void)
{
    igMetaObject *g = g_igMediaList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c1650();
    return g_igMediaList_metaObject[0];
}

int igMediaList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((ObjectHeader *)&tmp[0]);
    tmp[0] = (int)&DAT_005328a0[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_002c1650(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMediaList_Register);
}

void igMediaList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMediaList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMediaList_GetMetaObject,
        igMediaList_className,
        0x14, /* instance size */
        igMediaList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMediaList_callbackList /* callback list */
    );
}

void thunk_igMediaList_GetMetaObject(void) {
    igMediaList_GetMetaObject();
}

