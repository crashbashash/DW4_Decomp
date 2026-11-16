igMetaObject *g_beActionStarterData_metaObject;
igMetaField *g_beActionStarterData_messageMetaField;
igMetaField *g_beActionStarterData_delayMetaField;
igMetaField *g_beActionStarterData_offsetMetaField;
igMetaField *g_beActionStarterData_isSeqDeadMetaField;
igMetaField *g_beActionStarterData_isPositionLockMetaField;

void *beActionStarterData_GetMetaObject(void) {
    igMetaObject *g = g_beActionStarterData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beActionStarterData_EnsureRegistered();
    }
    return g_beActionStarterData_metaObject;
}

int beActionStarterData_GetVTable(void) {
    Obj_36be40 obj;
    int r;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beActionStarterData_vtable[0];
    obj._message = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beActionStarterData_vtable[0];
    obj.rel12();
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj.rel8();
    return r;
}

void beActionStarterData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beActionStarterData_Register);
}

void *beActionStarterData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beActionStarterData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beActionStarterData_GetMetaObjectFunction,
        "beActionStarterData",
        0x24, /* instance size */
        beActionStarterData_GetVTable,
        beActionStarterData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beActionStarterData_GetMetaObjectFunction(void)
{
    beActionStarterData_GetMetaObject();
}

static FieldFactory g_beActionStarterData_ctorTable[] = {
    igStringMetaField_Create,
    igIntMetaField_Create,
    FUN_00187890,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beActionStarterData_fieldTable[] = {
    "_message",
    "_delay",
    "_offset",
    "_isSeqDead",
    "_isPositionLock",
};
static igMetaField **g_beActionStarterData_fieldHandles[] = {
    &g_beActionStarterData_messageMetaField,
    &g_beActionStarterData_delayMetaField,
    &g_beActionStarterData_offsetMetaField,
    &g_beActionStarterData_isSeqDeadMetaField,
    &g_beActionStarterData_isPositionLockMetaField,
};
static int g_beActionStarterData_fieldOffsets[] = {
    12,
    16,
    20,
    32,
    33,
};

void beActionStarterData_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beActionStarterData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beActionStarterData_ctorTable, 5);
    igMetaObject_NameFields(meta, g_beActionStarterData_fieldTable, g_beActionStarterData_fieldHandles, g_beActionStarterData_fieldOffsets, base);
}

