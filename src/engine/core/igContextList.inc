igMetaObject *g_igContextList_metaObject;

void igContextList_Create(int pool) {
    igContextList_EnsureRegistered();
    igMetaObject_CreateInstance(g_igContextList_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igContextList_GetMetaObject(void)
{
    igMetaObject *g = g_igContextList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igContextList_EnsureRegistered();
    return g_igContextList_metaObject;
}

int igContextList_GetVTable(void) {
    igContextList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igContextList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igContextList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContextList_Register);
}

static igMetaObjectCallback g_igContextList_callbackList[] = { igContext_EnsureRegistered, 0 };

void igContextList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igContextList_metaObject,
        (igMetaObjectRegisterFunction)igNonRefCountedObjectList_Register,
        (igMetaObjectGetFunction)igNonRefCountedObjectList_GetPublishedMetaObject,
        igContextList_GetMetaObjectFunction,
        "igContextList",
        0x14,
        igContextList_GetVTable,
        0,
        0,
        g_igContextList_callbackList
    );
}

void igContextList_GetMetaObjectFunction(void) {
    igContextList_GetMetaObject();
}

