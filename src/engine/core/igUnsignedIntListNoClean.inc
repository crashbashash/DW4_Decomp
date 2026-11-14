void * igUnsignedIntListNoClean_Create(int pool) {
    igUnsignedIntListNoClean_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586850), (igMemoryPoolView *)pool));
}

igMetaObject *igUnsignedIntListNoClean_GetOrCreateMetaObject(void) {
    if (g_igUnsignedIntListNoClean_metaObject[0] == 0) {
        g_igUnsignedIntListNoClean_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igUnsignedIntListNoClean_metaObject[0];
}

igMetaObject *igUnsignedIntListNoClean_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntListNoClean_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedIntListNoClean_EnsureRegistered();
    return g_igUnsignedIntListNoClean_metaObject[0];
}

int igUnsignedIntListNoClean_GetVTable(void) {
    igUnsignedIntListNoClean list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igUnsignedIntListNoClean_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igUnsignedIntListNoClean_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedIntListNoClean_Register);
}

void igUnsignedIntListNoClean_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igUnsignedIntListNoClean_metaObject,
        (igMetaObjectRegisterFunction)igUnsignedIntList_Register,
        (igMetaObjectGetFunction)igUnsignedIntList_GetPublishedMetaObject,
        igUnsignedIntListNoClean_GetMetaObjectFunction,
        igUnsignedIntListNoClean_className,
        0x14,
        igUnsignedIntListNoClean_GetVTable,
        0,
        0,
        0
    );
}

void igUnsignedIntListNoClean_GetMetaObjectFunction(void) {
    igUnsignedIntListNoClean_GetMetaObject();
}

