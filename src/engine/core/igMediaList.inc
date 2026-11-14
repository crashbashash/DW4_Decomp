void * igMediaList_Create(int arg0) {
    igMediaList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586018), (igMemoryPoolView *)arg0));
}

igMetaObject *igMediaList_GetMetaObject(void)
{
    igMetaObject *g = g_igMediaList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMediaList_EnsureRegistered();
    return g_igMediaList_metaObject[0];
}

int igMediaList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&DAT_005328a0[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void igMediaList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMediaList_Register);
}

void igMediaList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMediaList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMediaList_GetMetaObjectFunction,
        igMediaList_className,
        0x14, /* instance size */
        igMediaList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMediaList_callbackList /* callback list */
    );
}

void igMediaList_GetMetaObjectFunction(void) {
    igMediaList_GetMetaObject();
}

