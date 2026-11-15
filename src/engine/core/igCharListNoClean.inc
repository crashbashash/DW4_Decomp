igMetaObject *g_igCharListNoClean_metaObject;

igMetaObject *igCharListNoClean_GetOrCreateMetaObject(void) {
    if (g_igCharListNoClean_metaObject == 0) {
        g_igCharListNoClean_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igCharListNoClean_metaObject;
}

igMetaObject *igCharListNoClean_GetMetaObject(void)
{
    igMetaObject *g = g_igCharListNoClean_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharListNoClean_EnsureRegistered();
    return g_igCharListNoClean_metaObject;
}

int igCharListNoClean_GetVTable(void) {
    igCharListNoClean list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igCharListNoClean_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igCharListNoClean_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCharListNoClean_Register);
}

void igCharListNoClean_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igCharListNoClean_metaObject,
        (igMetaObjectRegisterFunction)igCharList_Register,
        igCharList_GetPublishedMetaObject,
        igCharListNoClean_GetMetaObjectFunction,
        "igCharListNoClean",
        0x14,
        igCharListNoClean_GetVTable,
        0,
        0,
        0
    );
}

void igCharListNoClean_GetMetaObjectFunction(void) {
    igCharListNoClean_GetMetaObject();
}

