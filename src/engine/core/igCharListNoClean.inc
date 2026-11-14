igMetaObject *FUN_002cace0(void) {
    if (g_igCharListNoClean_metaObject[0] == 0) {
        g_igCharListNoClean_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igCharListNoClean_metaObject[0];
}

igMetaObject *igCharListNoClean_GetMetaObject(void)
{
    igMetaObject *g = g_igCharListNoClean_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cadc0();
    return g_igCharListNoClean_metaObject[0];
}

int igCharListNoClean_GetVTable(void) {
    igCharListNoClean list;

    igObject_InitHeader((struct ObjectHeader *)&list);
    list._vtable = (int)&DAT_00531a50[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002cadc0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCharListNoClean_Register);
}

void igCharListNoClean_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igCharListNoClean_metaObject),
        igCharList_Register,
        igCharList_GetPublishedMetaObject,
        thunk_igCharListNoClean_GetMetaObject,
        igCharListNoClean_className,
        0x14, /* instance size */
        igCharListNoClean_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igCharListNoClean_GetMetaObject(void) {
    igCharListNoClean_GetMetaObject();
}

