void * FUN_002b7b70(int arg0) {
    FUN_002b7c00();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585790), (MemoryPool *)arg0));
}

igMetaObject *igThreadManager_GetMetaObject(void)
{
    igMetaObject *g = g_igThreadManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b7c00();
    return g_igThreadManager_metaObject[0];
}

void FUN_002b7c00(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igThreadManager_Register);
}

void igThreadManager_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igThreadManager_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igThreadManager_GetMetaObject,
        igThreadManager_className,
        0x10, /* instance size */
        0,
        &igThreadManager_InitFields,
        thunk_FUN_0030e480, /* extra callback item */
        g_igThreadManager_callbackList /* callback list */
    );
}

void thunk_igThreadManager_GetMetaObject(void) {
    igThreadManager_GetMetaObject();
}

void igThreadManager_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    ((igMetaObject *)(g_igThreadManager_metaObject[0]))->_volatile = 1;
    temp_s0 = (void *)(g_igThreadManager_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igThreadManager_ctorTable[0], 2);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002b8220();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_002ba690();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igThreadManager_fieldTable[0], (igMetaField ***)&DAT_004bf388[0], &DAT_004bf390[0], temp_s2);
    ((igMetaObject *)(g_igThreadManager_metaObject[0]))->_abstractProxy = (int)thunk_igPsx2ThreadManager_GetMetaObject;
    FUN_002fe480((int)thunk_FUN_0030e540);
}

