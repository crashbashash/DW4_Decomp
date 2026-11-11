int FUN_002b8220(void) {
    if (DAT_00585820[0] == 0) {
        DAT_00585820[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_00585820[0];
}

igMetaObject *igNonRefCountedThreadList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedThreadList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b8300();
    return g_igNonRefCountedThreadList_metaObject[0];
}

int igNonRefCountedThreadList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((ObjectHeader *)obj);
    obj[0] = (int)&DAT_005333c0[0];
    return *(int *)((char *)obj + *(int *)((char *)((void * *)DAT_00586dc8)[0] + 916));
}

void FUN_002b8300(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igNonRefCountedThreadList_Register);
}

void igNonRefCountedThreadList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igNonRefCountedThreadList_metaObject),
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedThreadList_GetMetaObject,
        igNonRefCountedThreadList_className,
        0x14, /* instance size */
        igNonRefCountedThreadList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedThreadList_callbackList /* callback list */
    );
}

void thunk_igNonRefCountedThreadList_GetMetaObject(void) {
    igNonRefCountedThreadList_GetMetaObject();
}

