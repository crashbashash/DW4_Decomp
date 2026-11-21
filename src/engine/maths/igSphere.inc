igMetaObject *g_igSphere_metaObject;
igMetaField *g_igSphere_centerMetaField;
igMetaField *g_igSphere_radiusMetaField;

void FUN_00187e10(int arg0) {
    igSphere_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)g_igSphere_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igSphere_GetOrCreateMetaObject(void) {
    if (g_igSphere_metaObject == 0) {
        g_igSphere_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igSphere_metaObject;
}

igMetaObject *igSphere_GetMetaObject(void)
{
    igMetaObject *g = g_igSphere_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSphere_EnsureRegistered();
    return g_igSphere_metaObject;
}

int igSphere_GetVTable(void) {
    union U2 u;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igSphere_vtable[0];
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void igSphere_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igSphere_Register);
}

CallbackArray *igSphere_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSphere_metaObject,
        igVolume_Register,
        (igMetaObjectGetFunction)igVolume_GetPublishedMetaObject,
        igSphere_GetMetaObjectFunction,
        "igSphere",
        0x18, /* instance size */
        igSphere_GetVTable,
        &igSphere_InitFields,
        thunk_FUN_0018d480, /* extra callback item */
        0 /* callback list */
    );
}

void igSphere_GetMetaObjectFunction(void) {
    igSphere_GetMetaObject();
}

igMetaObject *igVolume_GetPublishedMetaObject(void) {
    return g_igVolume_metaObject;
}

static FieldFactory g_igSphere_ctorTable[] = {
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)igFloatMetaField_Create,
};

static const char *g_igSphere_fieldTable[] = {
    "_center",
    "_radius",
};

static igMetaField **g_igSphere_fieldHandles[] = {
    &g_igSphere_centerMetaField,
    &g_igSphere_radiusMetaField,
};

static int g_igSphere_fieldOffsets[] = {
    8,
    20,
};

void igSphere_InitFields(void) {
    int base;
    void *meta;
    int v[3];
    int field;

    meta = (void *)g_igSphere_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (FieldFactory *)g_igSphere_ctorTable, 2);
    field = (int)igMetaObject_GetFieldAt((igMetaObject *)meta, base);
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
    ((Gap::Math::igVec3fMetaField *)field)->setDefault(*(const igVec3f *)v);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)))->setDefault(-1.0f);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)g_igSphere_fieldTable, (igMetaField ***)g_igSphere_fieldHandles, (int *)g_igSphere_fieldOffsets, base);
}

void thunk_FUN_0018d480(void) {
    FUN_0018d480();
}

