int FUN_002c0a00(int arg0) {
    FUN_002c0ad0();
    return igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585F40), (igMemoryPoolView *)arg0);
}

igMetaObject *igMemoryFileEntryList_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryFileEntryList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c0ad0();
    return g_igMemoryFileEntryList_metaObject[0];
}

int igMemoryFileEntryList_GetVTable(void) {
    igMemoryFileEntryList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00532970[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002c0ad0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryFileEntryList_Register);
}

void igMemoryFileEntryList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMemoryFileEntryList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMemoryFileEntryList_GetMetaObject,
        igMemoryFileEntryList_className,
        0x14, /* instance size */
        igMemoryFileEntryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMemoryFileEntryList_callbackList /* callback list */
    );
}

void thunk_igMemoryFileEntryList_GetMetaObject(void) {
    igMemoryFileEntryList_GetMetaObject();
}

