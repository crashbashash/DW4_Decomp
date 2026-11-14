void igContextList_Create(int arg0) {
    igContextList_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5868F0), (igMemoryPoolView *)arg0);
}

igMetaObject *igContextList_GetMetaObject(void)
{
    igMetaObject *g = g_igContextList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igContextList_EnsureRegistered();
    return g_igContextList_metaObject[0];
}

int igContextList_GetVTable(void) {
    igContextList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00531840[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igContextList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContextList_Register);
}

void igContextList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igContextList_metaObject),
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        igContextList_GetMetaObjectFunction,
        igContextList_className,
        0x14, /* instance size */
        igContextList_GetVTable,
        0,
        0, /* extra callback item */
        g_igContextList_callbackList /* callback list */
    );
}

void igContextList_GetMetaObjectFunction(void) {
    igContextList_GetMetaObject();
}

