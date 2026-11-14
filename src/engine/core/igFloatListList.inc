igMetaObject *igFloatListList_GetOrCreateMetaObject(void) {
    if (g_igFloatListList_metaObject[0] == 0) {
        g_igFloatListList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igFloatListList_metaObject[0];
}

igMetaObject *igFloatListList_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFloatListList_EnsureRegistered();
    return g_igFloatListList_metaObject[0];
}

int igFloatListList_GetVTable(void) {
    igFloatListList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00531e80[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igFloatListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igFloatListList_Register);
}

void igFloatListList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igFloatListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igFloatListList_GetMetaObjectFunction,
        igFloatListList_className,
        0x14, /* instance size */
        igFloatListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igFloatListList_callbackList /* callback list */
    );
}

void igFloatListList_GetMetaObjectFunction(void) {
    igFloatListList_GetMetaObject();
}

