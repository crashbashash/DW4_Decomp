void igContextList_Create(int pool) {
    igContextList_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5868F0), (igMemoryPoolView *)pool);
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
    list._vtable = (int)&g_igContextList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igContextList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContextList_Register);
}

void igContextList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igContextList_metaObject,
        (igMetaObjectRegisterFunction)igNonRefCountedObjectList_Register,
        (igMetaObjectGetFunction)igNonRefCountedObjectList_GetPublishedMetaObject,
        igContextList_GetMetaObjectFunction,
        igContextList_className,
        0x14,
        igContextList_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igContextList_callbackList
    );
}

void igContextList_GetMetaObjectFunction(void) {
    igContextList_GetMetaObject();
}

