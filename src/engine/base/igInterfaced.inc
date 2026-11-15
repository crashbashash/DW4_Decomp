igMetaObject *g_igInterfaced_metaObject;
igMetaField *g_igInterfaced_optInterfaceMetaField;
igMetaField *g_igInterfaced_itemInterfaceMetaField;
igMetaField *g_igInterfaced_listenerInterfaceMetaField;
igMetaField *g_igInterfaced_messageInterfaceMetaField;
igMetaField *g_igInterfaced_lockInterfaceMetaField;
igMetaField *g_igInterfaced_logInterfaceMetaField;

igMetaObject *igInterfaced_GetMetaObject(void)
{
    igMetaObject *g = g_igInterfaced_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228a20();
    return g_igInterfaced_metaObject;
}

void FUN_00228a20(void)
{
    igMetaObject_RunStaticInit(igInterfaced_Register);
}

static igMetaObjectCallback g_igInterfaced_callbackList[] = { FUN_00225c10, FUN_00227ef0, FUN_00226e30, FUN_00226200, FUN_00226a10, FUN_002266c0, 0 };

void igInterfaced_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igInterfaced_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igInterfaced_GetMetaObject,
        "igInterfaced",
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

static FieldFactory g_igInterfaced_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igInterfaced_fieldTable[] = {
    "_optInterface",
    "_itemInterface",
    "_listenerInterface",
    "_messageInterface",
    "_lockInterface",
    "_logInterface",
};
static igMetaField **g_igInterfaced_fieldHandles[] = {
    &g_igInterfaced_optInterfaceMetaField,
    &g_igInterfaced_itemInterfaceMetaField,
    &g_igInterfaced_listenerInterfaceMetaField,
    &g_igInterfaced_messageInterfaceMetaField,
    &g_igInterfaced_lockInterfaceMetaField,
    &g_igInterfaced_logInterfaceMetaField,
};
static int g_igInterfaced_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
};

void igInterfaced_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    igMetaObject *temp_s1;

    temp_s1 = g_igInterfaced_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_igInterfaced_ctorTable, 6);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_00225a40();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_00227c20();
    ((igObjectRefMetaField *)temp_s2_2)->_refCounted = 0;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_00226c60();
    ((igObjectRefMetaField *)temp_s2_3)->_refCounted = 0;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_002260d0();
    ((igObjectRefMetaField *)temp_s2_4)->_refCounted = 0;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_002267c0();
    ((igObjectRefMetaField *)temp_s2_5)->_refCounted = 0;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_002265e0();
    ((igObjectRefMetaField *)temp_s2_6)->_refCounted = 0;
    igMetaObject_NameFields(temp_s1, g_igInterfaced_fieldTable, g_igInterfaced_fieldHandles, g_igInterfaced_fieldOffsets, temp_s0);
}

