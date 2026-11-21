igMetaObject *g_beModelCtrlSCHitBox_metaObject;
igMetaField *g_beModelCtrlSCHitBox_kindMetaField;
igMetaField *g_beModelCtrlSCHitBox_bulletModeMetaField;
igMetaField *g_beModelCtrlSCHitBox_endFrameMetaField;
igMetaField *g_beModelCtrlSCHitBox_offsetMetaField;
igMetaField *g_beModelCtrlSCHitBox_boxSizeMetaField;
igMetaField *g_beModelCtrlSCHitBox_isPositionLockMetaField;

beModelCtrlSCHitBox *beModelCtrlSCHitBox_Create(int allocator) {
    beModelCtrlSCHitBox_EnsureRegistered();
    return (beModelCtrlSCHitBox *)igMetaObject_CreateInstance(g_beModelCtrlSCHitBox_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beModelCtrlSCHitBox_GetMetaObject(void) {
    if (g_beModelCtrlSCHitBox_metaObject == 0 || !isValid(g_beModelCtrlSCHitBox_metaObject)) beModelCtrlSCHitBox_EnsureRegistered();
    return g_beModelCtrlSCHitBox_metaObject;
}

int beModelCtrlSCHitBox_GetVTable(void) {
    beModelCtrlSCHitBox obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beModelCtrlSCHitBox_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlSCHitBox_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSCHitBox_Register);
}

CallbackArray *beModelCtrlSCHitBox_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlSCHitBox_metaObject,
        beModelCtrlSubComBase_Register,
        beModelCtrlSubComBase_GetPublishedMetaObject,
        beModelCtrlSCHitBox_GetMetaObjectFunction,
        "beModelCtrlSCHitBox",
        0x3c, /* instance size */
        beModelCtrlSCHitBox_GetVTable,
        beModelCtrlSCHitBox_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlSCHitBox_GetMetaObjectFunction(void)
{
    beModelCtrlSCHitBox_GetMetaObject();
}

static FieldFactory g_beModelCtrlSCHitBox_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    igBoolMetaField_Create,
};
static const char *g_beModelCtrlSCHitBox_fieldTable[] = {
    "_kind",
    "_bulletMode",
    "_endFrame",
    "_offset",
    "_boxSize",
    "_isPositionLock",
};
static igMetaField **g_beModelCtrlSCHitBox_fieldHandles[] = {
    &g_beModelCtrlSCHitBox_kindMetaField,
    &g_beModelCtrlSCHitBox_bulletModeMetaField,
    &g_beModelCtrlSCHitBox_endFrameMetaField,
    &g_beModelCtrlSCHitBox_offsetMetaField,
    &g_beModelCtrlSCHitBox_boxSizeMetaField,
    &g_beModelCtrlSCHitBox_isPositionLockMetaField,
};
static int g_beModelCtrlSCHitBox_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    44,
    56,
};

void beModelCtrlSCHitBox_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beModelCtrlSCHitBox_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlSCHitBox_ctorTable, 6);
    igMetaObject_NameFields(meta, g_beModelCtrlSCHitBox_fieldTable, g_beModelCtrlSCHitBox_fieldHandles, g_beModelCtrlSCHitBox_fieldOffsets, base);
}

