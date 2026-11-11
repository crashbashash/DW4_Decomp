void FUN_002b79d0(int arg0) {
    FUN_002b7ab0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585788), (MemoryPool *)arg0);
}

int FUN_002b7a10(void) {
    if (DAT_00585788[0] == 0) {
        DAT_00585788[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_00585788[0];
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
    *(int *)((char *)(((void * *)DAT_00585788)[0]) + 60) = (int)(&thunk_FUN_002c1860);
}

void thunk_FUN_002c1860(void) {
    FUN_002c1860();
}

