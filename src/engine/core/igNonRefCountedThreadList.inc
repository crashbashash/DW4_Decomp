igMetaObject *g_igNonRefCountedThreadList_metaObject;

igMetaObject *igNonRefCountedThreadList_GetOrCreateMetaObject(void) {
    if (g_igNonRefCountedThreadList_metaObject == 0) {
        g_igNonRefCountedThreadList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igNonRefCountedThreadList_metaObject;
}

igMetaObject *igNonRefCountedThreadList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedThreadList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNonRefCountedThreadList_EnsureRegistered();
    return g_igNonRefCountedThreadList_metaObject;
}

int igNonRefCountedThreadList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igNonRefCountedThreadList_vtable[0];
    return *(int *)((char *)obj + *(int *)((char *)(*(void * *)&g_objectSystem) + 916));
}

void igNonRefCountedThreadList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igNonRefCountedThreadList_Register);
}

static igMetaObjectCallback g_igNonRefCountedThreadList_callbackList[] = { igThread_EnsureRegistered, 0 };

void igNonRefCountedThreadList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igNonRefCountedThreadList_metaObject,
        (igMetaObjectRegisterFunction)igNonRefCountedObjectList_Register,
        (igMetaObjectGetFunction)igNonRefCountedObjectList_GetPublishedMetaObject,
        igNonRefCountedThreadList_GetMetaObjectFunction,
        "igNonRefCountedThreadList",
        0x14,
        igNonRefCountedThreadList_GetVTable,
        0,
        0,
        g_igNonRefCountedThreadList_callbackList
    );
}

void igNonRefCountedThreadList_GetMetaObjectFunction(void) {
    igNonRefCountedThreadList_GetMetaObject();
}

