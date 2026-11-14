void * igContextExtInfoList_Create(int arg0) {
    igContextExtInfoList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5868C0), (igMemoryPoolView *)arg0));
}

igMetaObject *igContextExtInfoList_GetOrCreateMetaObject(void) {
    if (g_igContextExtInfoList_metaObject[0] == 0) {
        g_igContextExtInfoList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igContextExtInfoList_metaObject[0];
}

igMetaObject *igContextExtInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExtInfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igContextExtInfoList_EnsureRegistered();
    return g_igContextExtInfoList_metaObject[0];
}

int igContextExtInfoList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&DAT_00531910[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void igContextExtInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContextExtInfoList_Register);
}

void igContextExtInfoList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igContextExtInfoList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igContextExtInfoList_GetMetaObjectFunction,
        igContextExtInfoList_className,
        0x14, /* instance size */
        igContextExtInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igContextExtInfoList_callbackList /* callback list */
    );
}

void igContextExtInfoList_GetMetaObjectFunction(void) {
    igContextExtInfoList_GetMetaObject();
}

