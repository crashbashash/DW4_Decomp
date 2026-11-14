igMetaObject *igCharListNoClean_GetOrCreateMetaObject(void) {
    if (g_igCharListNoClean_metaObject[0] == 0) {
        g_igCharListNoClean_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igCharListNoClean_metaObject[0];
}

igMetaObject *igCharListNoClean_GetMetaObject(void)
{
    igMetaObject *g = g_igCharListNoClean_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharListNoClean_EnsureRegistered();
    return g_igCharListNoClean_metaObject[0];
}

int igCharListNoClean_GetVTable(void) {
    igCharListNoClean list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00531a50[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igCharListNoClean_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCharListNoClean_Register);
}

void igCharListNoClean_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igCharListNoClean_metaObject),
        igCharList_Register,
        igCharList_GetPublishedMetaObject,
        igCharListNoClean_GetMetaObjectFunction,
        igCharListNoClean_className,
        0x14, /* instance size */
        igCharListNoClean_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igCharListNoClean_GetMetaObjectFunction(void) {
    igCharListNoClean_GetMetaObject();
}

