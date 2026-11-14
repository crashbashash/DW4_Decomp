int igMemoryFileEntryList_Create(int arg0) {
    igMemoryFileEntryList_EnsureRegistered();
    return igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585F40), (igMemoryPoolView *)arg0);
}

igMetaObject *igMemoryFileEntryList_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryFileEntryList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryFileEntryList_EnsureRegistered();
    return g_igMemoryFileEntryList_metaObject[0];
}

int igMemoryFileEntryList_GetVTable(void) {
    igMemoryFileEntryList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00532970[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igMemoryFileEntryList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryFileEntryList_Register);
}

void igMemoryFileEntryList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igMemoryFileEntryList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
        igMemoryFileEntryList_GetMetaObjectFunction,
        igMemoryFileEntryList_className,
        0x14,
        igMemoryFileEntryList_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igMemoryFileEntryList_callbackList
    );
}

void igMemoryFileEntryList_GetMetaObjectFunction(void) {
    igMemoryFileEntryList_GetMetaObject();
}

