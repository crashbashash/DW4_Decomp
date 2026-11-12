void FUN_002b79d0(int arg0) {
    FUN_002b7ab0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585788), (MemoryPool *)arg0);
}

igMetaObject *FUN_002b7a10(void) {
    if (g_igTimer_metaObject[0] == 0) {
        g_igTimer_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    }
    return g_igTimer_metaObject[0];
}

igMetaObject *igTimer_GetMetaObject(void)
{
    igMetaObject *g = g_igTimer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b7ab0();
    return g_igTimer_metaObject[0];
}

void FUN_002b7ab0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igTimer_Register);
}

void igTimer_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igTimer_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igTimer_GetMetaObject,
        igTimer_className,
        8, /* instance size */
        0,
        FUN_002b7b40,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTimer_GetMetaObject(void) {
    igTimer_GetMetaObject();
}

void FUN_002b7b40(void) {
    *(int *)((char *)(((void * *)g_igTimer_metaObject)[0]) + 60) = (int)(&thunk_FUN_002c1860);
}

void thunk_FUN_002c1860(void) {
    FUN_002c1860();
}

