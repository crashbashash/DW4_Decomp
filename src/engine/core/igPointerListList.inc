igMetaObject *igPointerListList_GetOrCreateMetaObject(void) {
    if (g_igPointerListList_metaObject[0] == 0) {
        g_igPointerListList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igPointerListList_metaObject[0];
}

igMetaObject *igPointerListList_GetMetaObject(void)
{
    igMetaObject *g = g_igPointerListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igPointerListList_EnsureRegistered();
    return g_igPointerListList_metaObject[0];
}

int igPointerListList_GetVTable(void) {
    igPointerListList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00531f50[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igPointerListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPointerListList_Register);
}

void igPointerListList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPointerListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igPointerListList_GetMetaObjectFunction,
        igPointerListList_className,
        0x14, /* instance size */
        igPointerListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igPointerListList_callbackList /* callback list */
    );
}

void igPointerListList_GetMetaObjectFunction(void) {
    igPointerListList_GetMetaObject();
}

