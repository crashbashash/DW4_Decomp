igMetaObject *igStringRefListList_GetOrCreateMetaObject(void) {
    if (g_igStringRefListList_metaObject[0] == 0) {
        g_igStringRefListList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igStringRefListList_metaObject[0];
}

igMetaObject *igStringRefListList_GetMetaObject(void)
{
    igMetaObject *g = g_igStringRefListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igStringRefListList_EnsureRegistered();
    return g_igStringRefListList_metaObject[0];
}

int igStringRefListList_GetVTable(void) {
    igStringRefListList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_005321f0[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igStringRefListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringRefListList_Register);
}

void igStringRefListList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igStringRefListList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
        igStringRefListList_GetMetaObjectFunction,
        igStringRefListList_className,
        0x14,
        igStringRefListList_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igStringRefListList_callbackList
    );
}

void igStringRefListList_GetMetaObjectFunction(void) {
    igStringRefListList_GetMetaObject();
}

