igMetaObject *igNonRefCountedThreadList_GetOrCreateMetaObject(void) {
    if (g_igNonRefCountedThreadList_metaObject[0] == 0) {
        g_igNonRefCountedThreadList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igNonRefCountedThreadList_metaObject[0];
}

igMetaObject *igNonRefCountedThreadList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedThreadList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igNonRefCountedThreadList_EnsureRegistered();
    return g_igNonRefCountedThreadList_metaObject[0];
}

int igNonRefCountedThreadList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&DAT_005333c0[0];
    return *(int *)((char *)obj + *(int *)((char *)((void * *)g_objectSystem)[0] + 916));
}

void igNonRefCountedThreadList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igNonRefCountedThreadList_Register);
}

void igNonRefCountedThreadList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igNonRefCountedThreadList_metaObject),
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        igNonRefCountedThreadList_GetMetaObjectFunction,
        igNonRefCountedThreadList_className,
        0x14, /* instance size */
        igNonRefCountedThreadList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedThreadList_callbackList /* callback list */
    );
}

void igNonRefCountedThreadList_GetMetaObjectFunction(void) {
    igNonRefCountedThreadList_GetMetaObject();
}

