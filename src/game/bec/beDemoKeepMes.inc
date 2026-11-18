igMetaObject *g_beDemoKeepMes_metaObject;
igMetaField *g_beDemoKeepMes_kindMetaField;
igMetaField *g_beDemoKeepMes_sendTimeMetaField;
igMetaField *g_beDemoKeepMes_groupNameMetaField;
igMetaField *g_beDemoKeepMes_infoNameMetaField;
igMetaField *g_beDemoKeepMes_ramNoMetaField;
igMetaField *g_beDemoKeepMes_messageMetaField;
igMetaField *g_beDemoKeepMes_mesParamMetaField;

beDemoKeepMes *beDemoKeepMes_CreateInstance(int allocator) {
    beDemoKeepMes_EnsureRegistered();
    return (beDemoKeepMes *)igMetaObject_CreateInstance(g_beDemoKeepMes_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beDemoKeepMes_GetMetaObject(void) {
    igMetaObject *g = g_beDemoKeepMes_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beDemoKeepMes_EnsureRegistered();
    return g_beDemoKeepMes_metaObject;
}

int beDemoKeepMes_GetVTable(void) {
    beDemoKeepMes obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beDemoKeepMes_vtable[0];
    obj._groupName = 0;
    obj._infoName = 0;
    obj._message = 0;
    obj._mesParam = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beDemoKeepMes_vtable[0];
    igStringRef_Destruct((igStringRef *)&obj._mesParam, -1);
    igStringRef_Destruct((igStringRef *)&obj._message, -1);
    igStringRef_Destruct((igStringRef *)&obj._infoName, -1);
    igStringRef_Destruct((igStringRef *)&obj._groupName, -1);
    return vtable;
}

void beDemoKeepMes_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDemoKeepMes_Register);
}

CallbackArray *beDemoKeepMes_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDemoKeepMes_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beDemoKeepMes_GetMetaObjectFunction,
        "beDemoKeepMes",
        0x30, /* instance size */
        beDemoKeepMes_GetVTable,
        beDemoKeepMes_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beDemoKeepMes_GetMetaObjectFunction(void)
{
    beDemoKeepMes_GetMetaObject();
}

static FieldFactory g_beDemoKeepMes_ctorTable[] = {
    igIntMetaField_Create,
    igLongMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igIntMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_beDemoKeepMes_fieldTable[] = {
    "_kind",
    "_sendTime",
    "_groupName",
    "_infoName",
    "_ramNo",
    "_message",
    "_mesParam",
};
static igMetaField **g_beDemoKeepMes_fieldHandles[] = {
    &g_beDemoKeepMes_kindMetaField,
    &g_beDemoKeepMes_sendTimeMetaField,
    &g_beDemoKeepMes_groupNameMetaField,
    &g_beDemoKeepMes_infoNameMetaField,
    &g_beDemoKeepMes_ramNoMetaField,
    &g_beDemoKeepMes_messageMetaField,
    &g_beDemoKeepMes_mesParamMetaField,
};
static int g_beDemoKeepMes_fieldOffsets[] = {
    8,
    16,
    24,
    28,
    32,
    36,
    40,
};

void beDemoKeepMes_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beDemoKeepMes_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDemoKeepMes_ctorTable, 7);
    igMetaObject_NameFields(meta, g_beDemoKeepMes_fieldTable, g_beDemoKeepMes_fieldHandles, g_beDemoKeepMes_fieldOffsets, base);
}

