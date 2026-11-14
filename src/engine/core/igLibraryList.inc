igMetaObject *igLibraryList_GetOrCreateMetaObject(void) {
    if (g_igLibraryList_metaObject[0] == 0) {
        g_igLibraryList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igLibraryList_metaObject[0];
}

igMetaObject *igLibraryList_GetMetaObject(void)
{
    igMetaObject *g = g_igLibraryList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igLibraryList_EnsureRegistered();
    return g_igLibraryList_metaObject[0];
}

int igLibraryList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&DAT_00532830[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void igLibraryList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLibraryList_Register);
}

void igLibraryList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igLibraryList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igLibraryList_GetMetaObjectFunction,
        igLibraryList_className,
        0x14, /* instance size */
        igLibraryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igLibraryList_callbackList /* callback list */
    );
}

void igLibraryList_GetMetaObjectFunction(void) {
    igLibraryList_GetMetaObject();
}

