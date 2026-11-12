igMetaObject *FUN_002c23b0(void) {
    if (g_igLibraryList_metaObject[0] == 0) {
        g_igLibraryList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    }
    return g_igLibraryList_metaObject[0];
}

igMetaObject *igLibraryList_GetMetaObject(void)
{
    igMetaObject *g = g_igLibraryList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c2490();
    return g_igLibraryList_metaObject[0];
}

int igLibraryList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((ObjectHeader *)&tmp[0]);
    tmp[0] = (int)&DAT_00532830[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_002c2490(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLibraryList_Register);
}

void igLibraryList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igLibraryList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igLibraryList_GetMetaObject,
        igLibraryList_className,
        0x14, /* instance size */
        igLibraryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igLibraryList_callbackList /* callback list */
    );
}

void thunk_igLibraryList_GetMetaObject(void) {
    igLibraryList_GetMetaObject();
}

