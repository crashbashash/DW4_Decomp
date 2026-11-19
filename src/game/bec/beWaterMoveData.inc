igMetaObject *g_beWaterMoveData_metaObject;
igMetaField *g_beWaterMoveData_timeMetaField;
igMetaField *g_beWaterMoveData_powerMetaField;
igMetaField *g_beWaterMoveData_posListMetaField;

void *beWaterMoveData_GetMetaObject(void) {
    igMetaObject *g = g_beWaterMoveData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beWaterMoveData_EnsureRegistered();
    }
    return g_beWaterMoveData_metaObject;
}

int beWaterMoveData_GetVTable(void) {
    beWaterMoveData obj;
    int vtable;
    igObject **posListSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beWaterMoveData_vtable[0];
    posListSlot = (igObject **)&obj._posList;
    *posListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beWaterMoveData_vtable[0];
    igObjectRef_Release(posListSlot);
    return vtable;
}

void beWaterMoveData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWaterMoveData_Register);
}

static igMetaObjectCallback g_beWaterMoveData_callbackList[] = { igVec3fList_EnsureRegistered, 0 };

CallbackArray *beWaterMoveData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWaterMoveData_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beWaterMoveData_GetMetaObjectFunction,
        "beWaterMoveData",
        0x18, /* instance size */
        beWaterMoveData_GetVTable,
        beWaterMoveData_InitFields,
        0, /* extra callback item */
        g_beWaterMoveData_callbackList /* callback list */
    );
}

void beWaterMoveData_GetMetaObjectFunction(void)
{
    beWaterMoveData_GetMetaObject();
}

static FieldFactory g_beWaterMoveData_ctorTable[] = {
    igLongMetaField_Create,
    igFloatMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beWaterMoveData_fieldTable[] = {
    "_time",
    "_power",
    "_posList",
};
static igMetaField **g_beWaterMoveData_fieldHandles[] = {
    &g_beWaterMoveData_timeMetaField,
    &g_beWaterMoveData_powerMetaField,
    &g_beWaterMoveData_posListMetaField,
};
static int g_beWaterMoveData_fieldOffsets[] = {
    8,
    16,
    20,
};

void beWaterMoveData_InitFields(void) {
    int base;
    void *posList;
    igMetaObject *meta;

    meta = g_beWaterMoveData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beWaterMoveData_ctorTable, 3);
    posList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)posList)->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    ((igRefMetaField *)posList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beWaterMoveData_fieldTable, g_beWaterMoveData_fieldHandles, g_beWaterMoveData_fieldOffsets, base);
}

