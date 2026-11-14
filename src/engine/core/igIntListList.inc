igMetaObject *igIntListList_GetOrCreateMetaObject(void) {
    if (g_igIntListList_metaObject[0] == 0) {
        g_igIntListList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igIntListList_metaObject[0];
}

igMetaObject *igIntListList_GetMetaObject(void)
{
    igMetaObject *g = g_igIntListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igIntListList_EnsureRegistered();
    return g_igIntListList_metaObject[0];
}

int igIntListList_GetVTable(void) {
    igIntListList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00532110[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igIntListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igIntListList_Register);
}

void igIntListList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igIntListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igIntListList_GetMetaObjectFunction,
        igIntListList_className,
        0x14, /* instance size */
        igIntListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igIntListList_callbackList /* callback list */
    );
}

void igIntListList_GetMetaObjectFunction(void) {
    igIntListList_GetMetaObject();
}

