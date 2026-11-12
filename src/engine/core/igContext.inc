igMetaObject *igContext_GetMetaObject(void)
{
    igMetaObject *g = g_igContext_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cbbb0();
    return g_igContext_metaObject[0];
}

void FUN_002cbbb0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContext_Register);
}

void igContext_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igContext_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igContext_GetMetaObject,
        igContext_className,
        0x14, /* instance size */
        0,
        &igContext_InitFields,
        0, /* extra callback item */
        g_igContext_callbackList /* callback list */
    );
}

void thunk_igContext_GetMetaObject(void) {
    igContext_GetMetaObject();
}

void igContext_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igContext_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c1478[0], 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002cb4f0();
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_002cb340();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c1488[0], (igMetaField ***)&DAT_004c1498[0], &DAT_004c14a8[0], temp_s2);
}

