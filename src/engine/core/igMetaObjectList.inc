void * igMetaObjectList_Create(int arg0) {
    igMetaObjectList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5867D0), (igMemoryPoolView *)arg0));
}

igMetaObject *igMetaObjectList_GetOrCreateMetaObject(void) {
    if (g_igMetaObjectList_metaObject[0] == 0) {
        g_igMetaObjectList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMetaObjectList_metaObject[0];
}

igMetaObject *igMetaObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaObjectList_EnsureRegistered();
    return g_igMetaObjectList_metaObject[0];
}

int igMetaObjectList_GetVTable(void) {
    igMetaObjectList obj;

    igObject_InitHeader((igObject *)&obj);
    obj._vtable = (int)&DAT_00531fc0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igMetaObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaObjectList_Register);
}

void igMetaObjectList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMetaObjectList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMetaObjectList_GetMetaObjectFunction,
        igMetaObjectList_className,
        0x14, /* instance size */
        igMetaObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMetaObjectList_callbackList /* callback list */
    );
}

void igMetaObjectList_GetMetaObjectFunction(void) {
    igMetaObjectList_GetMetaObject();
}

