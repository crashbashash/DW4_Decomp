igMetaObject *g_beResetNode_metaObject;
igMetaField *g_beResetNode_isResetTimeMetaField;
igMetaField *g_beResetNode_isResetRotAndScaleMetaField;

igMetaObject *beResetNode_GetMetaObject(void) {
    igMetaObject *g = g_beResetNode_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beResetNode_EnsureRegistered();
    }
    return g_beResetNode_metaObject;
}

int beResetNode_GetVTable(void) {
    beResetNode obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._bound = 0;
    obj._parentList = 0;
    obj._childList = 0;
    obj._vtable = (int)&g_beResetNode_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beResetNode_vtable[0];
    igGroup_Destroy((igGroup *)&obj, 0);
    return vtable;
}

void beResetNode_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beResetNode_Register);
}

CallbackArray *beResetNode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beResetNode_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beResetNode_GetMetaObjectFunction,
        "beResetNode",
        0x24, /* instance size */
        beResetNode_GetVTable,
        beResetNode_InitFields,
        beResetNode_StaticInitCallback, /* extra callback item */
        0 /* callback list */
    );
}

void beResetNode_GetMetaObjectFunction(void)
{
    beResetNode_GetMetaObject();
}

static FieldFactory g_beResetNode_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beResetNode_fieldTable[] = {
    "_isResetTime",
    "_isResetRotAndScale",
};
static igMetaField **g_beResetNode_fieldHandles[] = {
    &g_beResetNode_isResetTimeMetaField,
    &g_beResetNode_isResetRotAndScaleMetaField,
};
static int g_beResetNode_fieldOffsets[] = {
    32,
    33,
};

void beResetNode_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beResetNode_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beResetNode_ctorTable, 2);
    igMetaObject_NameFields(meta, g_beResetNode_fieldTable, g_beResetNode_fieldHandles, g_beResetNode_fieldOffsets, base);
}

void beResetNode_StaticInitCallback(void)
{
    beResetNode_RegisterTraversal();
}

