igMetaObject *igInterfaced_GetMetaObject(void)
{
    igMetaObject *g = g_igInterfaced_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228a20();
    return g_igInterfaced_metaObject[0];
}

void FUN_00228a20(void)
{
    igMetaObject_RunStaticInit(igInterfaced_Register);
}

void igInterfaced_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igInterfaced_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igInterfaced_GetMetaObject,
        igInterfaced_className,
        0x20, /* instance size */
        0,
        &igInterfaced_InitFields,
        0, /* extra callback item */
        g_igInterfaced_callbackList /* callback list */
    );
}

void thunk_igInterfaced_GetMetaObject(void) {
    igInterfaced_GetMetaObject();
}

void igInterfaced_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s1;

    temp_s1 = (void *)DAT_0056d9f0[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_00497e90[0], 6);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00225a40();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00227c20();
    ((igObjectRefMetaField *)temp_s2_2)->_refCounted = 0;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00226c60();
    ((igObjectRefMetaField *)temp_s2_3)->_refCounted = 0;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_002260d0();
    ((igObjectRefMetaField *)temp_s2_4)->_refCounted = 0;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_002267c0();
    ((igObjectRefMetaField *)temp_s2_5)->_refCounted = 0;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_002265e0();
    ((igObjectRefMetaField *)temp_s2_6)->_refCounted = 0;
    igMetaObject_NameFields(temp_s1, &DAT_00497eb0[0], &DAT_00497ed0[0], &DAT_00497ef0[0], temp_s0);
}

