igMetaObject *g_beModelCtrlHITBOX_metaObject;
igMetaField *g_beModelCtrlHITBOX_kindMetaField;
igMetaField *g_beModelCtrlHITBOX_startMetaField;
igMetaField *g_beModelCtrlHITBOX_lengthMetaField;
igMetaField *g_beModelCtrlHITBOX_offsetMetaField;
igMetaField *g_beModelCtrlHITBOX_boxSizeMetaField;

beModelCtrlHITBOX *beModelCtrlHITBOX_Create(int allocator) {
    beModelCtrlHITBOX_EnsureRegistered();
    return (beModelCtrlHITBOX *)igMetaObject_CreateInstance(*(int *)0x588D20, allocator);
}

igMetaObject *beModelCtrlHITBOX_GetMetaObject(void)
{
    igMetaObject *g = g_beModelCtrlHITBOX_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beModelCtrlHITBOX_EnsureRegistered();
    return g_beModelCtrlHITBOX_metaObject;
}

int beModelCtrlHITBOX_GetVTable(void) {
    beModelCtrlHITBOX obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beModelCtrlHITBOX_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlHITBOX_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlHITBOX_Register);
}

void *beModelCtrlHITBOX_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlHITBOX_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlHITBOX_GetMetaObjectFunction,
        "beModelCtrlHITBOX",
        0x30, /* instance size */
        beModelCtrlHITBOX_GetVTable,
        beModelCtrlHITBOX_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlHITBOX_GetMetaObjectFunction(void)
{
    beModelCtrlHITBOX_GetMetaObject();
}

static FieldFactory g_beModelCtrlHITBOX_ctorTable[] = {
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igVec3fMetaField_CreateInstance,
    igVec3fMetaField_CreateInstance,
};
static const char *g_beModelCtrlHITBOX_fieldTable[] = {
    "_kind",
    "_start",
    "_length",
    "_offset",
    "_boxSize",
};
static igMetaField **g_beModelCtrlHITBOX_fieldHandles[] = {
    &g_beModelCtrlHITBOX_kindMetaField,
    &g_beModelCtrlHITBOX_startMetaField,
    &g_beModelCtrlHITBOX_lengthMetaField,
    &g_beModelCtrlHITBOX_offsetMetaField,
    &g_beModelCtrlHITBOX_boxSizeMetaField,
};
static int g_beModelCtrlHITBOX_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    36,
};

void beModelCtrlHITBOX_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beModelCtrlHITBOX_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlHITBOX_ctorTable, 5);
    igMetaObject_NameFields(meta, g_beModelCtrlHITBOX_fieldTable, g_beModelCtrlHITBOX_fieldHandles, g_beModelCtrlHITBOX_fieldOffsets, base);
}

