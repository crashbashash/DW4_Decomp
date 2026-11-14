void * igStringObjList_Create(int pool) {
    igStringObjList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5858E8), (igMemoryPoolView *)pool));
}

igMetaObject *igStringObjList_GetOrCreateMetaObject(void) {
    if (g_igStringObjList_metaObject[0] == 0) {
        g_igStringObjList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igStringObjList_metaObject[0];
}

igMetaObject *igStringObjList_GetMetaObject(void)
{
    igMetaObject *g = g_igStringObjList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igStringObjList_EnsureRegistered();
    return g_igStringObjList_metaObject[0];
}

int igStringObjList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&g_igStringObjList_vtable[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void igStringObjList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringObjList_Register);
}

void igStringObjList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igStringObjList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
        igStringObjList_GetMetaObjectFunction,
        igStringObjList_className,
        0x14,
        igStringObjList_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igStringObjList_callbackList
    );
}

void igStringObjList_GetMetaObjectFunction(void) {
    igStringObjList_GetMetaObject();
}

