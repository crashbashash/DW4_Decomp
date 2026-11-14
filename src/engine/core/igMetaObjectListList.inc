igMetaObject *igMetaObjectListList_GetOrCreateMetaObject(void) {
    if (g_igMetaObjectListList_metaObject[0] == 0) {
        g_igMetaObjectListList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMetaObjectListList_metaObject[0];
}

igMetaObject *igMetaObjectListList_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaObjectListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaObjectListList_EnsureRegistered();
    return g_igMetaObjectListList_metaObject[0];
}

int igMetaObjectListList_GetVTable(void) {
    igMetaObjectListList obj;

    igObject_InitHeader((igObject *)&obj);
    obj._vtable = (int)&DAT_00532030[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igMetaObjectListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaObjectListList_Register);
}

void igMetaObjectListList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMetaObjectListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMetaObjectListList_GetMetaObjectFunction,
        igMetaObjectListList_className,
        0x14, /* instance size */
        igMetaObjectListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMetaObjectListList_callbackList /* callback list */
    );
}

void igMetaObjectListList_GetMetaObjectFunction(void) {
    igMetaObjectListList_GetMetaObject();
}

