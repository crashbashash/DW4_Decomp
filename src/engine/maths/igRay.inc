igMetaObject *g_igRay_metaObject;
igMetaField *g_igRay_posMetaField;
igMetaField *g_igRay_dirMetaField;
igMetaField *g_igRay_lenMetaField;

igRay *igRay_CreateInstance(int allocator) {
    igRay_EnsureRegistered();
    return (igRay *)igMetaObject_CreateInstance((igMetaObject *)g_igRay_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igRay_GetOrCreateMetaObject(void) {
    if (g_igRay_metaObject == 0) {
        g_igRay_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRay_metaObject;
}

igMetaObject *igRay_GetMetaObject(void)
{
    igMetaObject *g = g_igRay_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRay_EnsureRegistered();
    return g_igRay_metaObject;
}

int igRay_GetVTable(void) {
    struct Obj7 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igRay_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igRay_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRay_Register);
}

CallbackArray *igRay_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRay_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igRay_GetMetaObjectFunction,
        "igRay",
        0x24, /* instance size */
        igRay_GetVTable,
        &igRay_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igRay_GetMetaObjectFunction(void) {
    igRay_GetMetaObject();
}

static FieldFactory g_igRay_ctorTable[] = {
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)igFloatMetaField_Create,
};

static const char *g_igRay_fieldTable[] = {
    "_pos",
    "_dir",
    "_len",
};

static igMetaField **g_igRay_fieldHandles[] = {
    &g_igRay_posMetaField,
    &g_igRay_dirMetaField,
    &g_igRay_lenMetaField,
};

static int g_igRay_fieldOffsets[] = {
    8,
    20,
    32,
};

void igRay_InitFields(void) {
    int base;
    void *meta;
    int field;
    int field2;
    int value[4];
    int value2[4];

    meta = (void *)g_igRay_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (FieldFactory *)g_igRay_ctorTable, 3);
    field2 = (int)igMetaObject_GetFieldAt((igMetaObject *)meta, base);
    value[0] = 0;
    value[1] = 0;
    value[2] = 0;
    ((Gap::Math::igVec3fMetaField *)field2)->setDefault(*(const igVec3f *)&value[0]);
    field = (int)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1);
    value2[0] = 0;
    value2[1] = 0x3F800000;
    value2[2] = 0;
    ((Gap::Math::igVec3fMetaField *)field)->setDefault(*(const igVec3f *)&value2[0]);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)g_igRay_fieldTable, (igMetaField ***)g_igRay_fieldHandles, (int *)g_igRay_fieldOffsets, base);
}

