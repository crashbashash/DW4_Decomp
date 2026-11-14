igMetaObject *igThreadList_GetOrCreateMetaObject(void) {
    if (g_igThreadList_metaObject[0] == 0) {
        g_igThreadList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igThreadList_metaObject[0];
}

igMetaObject *igThreadList_GetMetaObject(void)
{
    igMetaObject *g = g_igThreadList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igThreadList_EnsureRegistered();
    return g_igThreadList_metaObject[0];
}

int igThreadList_GetVTable(void) {
    igThreadList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00533350[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igThreadList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igThreadList_Register);
}

void igThreadList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igThreadList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igThreadList_GetMetaObjectFunction,
        igThreadList_className,
        0x14, /* instance size */
        igThreadList_GetVTable,
        0,
        0, /* extra callback item */
        g_igThreadList_callbackList /* callback list */
    );
}

void igThreadList_GetMetaObjectFunction(void) {
    igThreadList_GetMetaObject();
}

