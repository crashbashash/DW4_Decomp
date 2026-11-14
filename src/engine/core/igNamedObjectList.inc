igMetaObject *igNamedObjectList_GetOrCreateMetaObject(void) {
    if (g_igNamedObjectList_metaObject[0] == 0) {
        g_igNamedObjectList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igNamedObjectList_metaObject[0];
}

igMetaObject *igNamedObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igNamedObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igNamedObjectList_EnsureRegistered();
    return g_igNamedObjectList_metaObject[0];
}

int igNamedObjectList_GetVTable(void) {
    igNamedObjectList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00532c10[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igNamedObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igNamedObjectList_Register);
}

void igNamedObjectList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igNamedObjectList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igNamedObjectList_GetMetaObjectFunction,
        igNamedObjectList_className,
        0x14, /* instance size */
        igNamedObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNamedObjectList_callbackList /* callback list */
    );
}

void igNamedObjectList_GetMetaObjectFunction(void) {
    igNamedObjectList_GetMetaObject();
}

