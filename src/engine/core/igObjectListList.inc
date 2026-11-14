igMetaObject *igObjectListList_GetOrCreateMetaObject(void) {
    if (g_igObjectListList_metaObject[0] == 0) {
        g_igObjectListList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igObjectListList_metaObject[0];
}

igMetaObject *igObjectListList_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igObjectListList_EnsureRegistered();
    return g_igObjectListList_metaObject[0];
}

int igObjectListList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&DAT_00532180[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void igObjectListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igObjectListList_Register);
}

void igObjectListList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igObjectListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igObjectListList_GetMetaObjectFunction,
        igObjectListList_className,
        0x14, /* instance size */
        igObjectListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igObjectListList_callbackList /* callback list */
    );
}

void igObjectListList_GetMetaObjectFunction(void) {
    igObjectListList_GetMetaObject();
}

