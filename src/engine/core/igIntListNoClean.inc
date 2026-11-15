igMetaObject *g_igIntListNoClean_metaObject;

void * igIntListNoClean_Create(int allocator) {
    igIntListNoClean_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igIntListNoClean_metaObject, (igMemoryPoolView *)allocator));
}

igMetaObject *igIntListNoClean_GetOrCreateMetaObject(void) {
    if (g_igIntListNoClean_metaObject == 0) {
        g_igIntListNoClean_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igIntListNoClean_metaObject;
}

igMetaObject *igIntListNoClean_GetMetaObject(void)
{
    igMetaObject *g = g_igIntListNoClean_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igIntListNoClean_EnsureRegistered();
    return g_igIntListNoClean_metaObject;
}

int igIntListNoClean_GetVTable(void) {
    igIntListNoClean list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igIntListNoClean_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igIntListNoClean_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igIntListNoClean_Register);
}

void igIntListNoClean_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igIntListNoClean_metaObject,
        (igMetaObjectRegisterFunction)igIntList_Register,
        igIntList_GetPublishedMetaObject,
        igIntListNoClean_GetMetaObjectFunction,
        "igIntListNoClean",
        0x14,
        igIntListNoClean_GetVTable,
        0,
        0,
        0
    );
}

void igIntListNoClean_GetMetaObjectFunction(void) {
    igIntListNoClean_GetMetaObject();
}

