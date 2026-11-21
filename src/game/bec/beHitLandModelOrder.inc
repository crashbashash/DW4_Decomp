igMetaObject *g_beHitLandModelOrder_metaObject;
igMetaField *g_beHitLandModelOrder_infoNameMetaField;
igMetaField *g_beHitLandModelOrder_ramNoMetaField;
igMetaField *g_beHitLandModelOrder_kindMetaField;
igMetaField *g_beHitLandModelOrder_raymaxMetaField;
igMetaField *g_beHitLandModelOrder_rayminMetaField;
igMetaField *g_beHitLandModelOrder_rayCountMetaField;
igMetaField *g_beHitLandModelOrder_rayListMetaField;
igMetaField *g_beHitLandModelOrder_hitdataCountMetaField;
igMetaField *g_beHitLandModelOrder_hitdataListMetaField;

beHitLandModelOrder *beHitLandModelOrder_Create(int allocator) {
    beHitLandModelOrder_EnsureRegistered();
    return (beHitLandModelOrder *)igMetaObject_CreateInstance(g_beHitLandModelOrder_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beHitLandModelOrder_GetOrCreateMetaObject(void) {
    if (g_beHitLandModelOrder_metaObject == 0) {
        g_beHitLandModelOrder_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beHitLandModelOrder_metaObject;
}

void *beHitLandModelOrder_GetMetaObject(void) {
    bool ok;
    if (g_beHitLandModelOrder_metaObject == 0) goto make;
    ok = !!(g_beHitLandModelOrder_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beHitLandModelOrder_EnsureRegistered();
done:;
    return g_beHitLandModelOrder_metaObject;
}

int beHitLandModelOrder_GetVTable(void) {
    beHitLandModelOrder obj;
    int vtable;
    igObject **hitdataListSlot;
    igObject **rayListSlot;
    char **infoNameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beHitLandModelOrder_vtable[0];
    infoNameSlot = (char **)&obj._infoName;
    *infoNameSlot = 0;
    rayListSlot = (igObject **)&obj._rayList;
    *rayListSlot = 0;
    hitdataListSlot = (igObject **)&obj._hitdataList;
    *hitdataListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beHitLandModelOrder_vtable[0];
    igObjectRef_Release(hitdataListSlot);
    igObjectRef_Release(rayListSlot);
    igStringRef_Release(infoNameSlot);
    return vtable;
}

void beHitLandModelOrder_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beHitLandModelOrder_Register);
}

static igMetaObjectCallback g_beHitLandModelOrder_callbackList[] = { igRayList_EnsureRegistered, beHitLandResultDataList_EnsureRegistered, 0 };

CallbackArray *beHitLandModelOrder_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandModelOrder_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beHitLandModelOrder_GetMetaObjectFunction,
        "beHitLandModelOrder",
        0x3c, /* instance size */
        beHitLandModelOrder_GetVTable,
        beHitLandModelOrder_InitFields,
        0, /* extra callback item */
        g_beHitLandModelOrder_callbackList /* callback list */
    );
}

void beHitLandModelOrder_GetMetaObjectFunction(void)
{
    beHitLandModelOrder_GetMetaObject();
}

static FieldFactory g_beHitLandModelOrder_ctorTable[] = {
    igStringMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igVec3fMetaField_CreateInstance,
    igVec3fMetaField_CreateInstance,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beHitLandModelOrder_fieldTable[] = {
    "_infoName",
    "_ramNo",
    "_kind",
    "_raymax",
    "_raymin",
    "_rayCount",
    "_rayList",
    "_hitdataCount",
    "_hitdataList",
};
static igMetaField **g_beHitLandModelOrder_fieldHandles[] = {
    &g_beHitLandModelOrder_infoNameMetaField,
    &g_beHitLandModelOrder_ramNoMetaField,
    &g_beHitLandModelOrder_kindMetaField,
    &g_beHitLandModelOrder_raymaxMetaField,
    &g_beHitLandModelOrder_rayminMetaField,
    &g_beHitLandModelOrder_rayCountMetaField,
    &g_beHitLandModelOrder_rayListMetaField,
    &g_beHitLandModelOrder_hitdataCountMetaField,
    &g_beHitLandModelOrder_hitdataListMetaField,
};
static int g_beHitLandModelOrder_fieldOffsets[] = {
    32,
    36,
    40,
    8,
    20,
    44,
    48,
    52,
    56,
};

void beHitLandModelOrder_InitFields(void) {
    void *raymax;
    void *raymin;
    void *rayList;
    int base;
    void *hitdataList;
    igMetaObject *meta;
    int rayMaxDefault[3];
    int rayMinDefault[3];

    meta = g_beHitLandModelOrder_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beHitLandModelOrder_ctorTable, 9);
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt(meta, base)))->setDefault("");
    raymax = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    rayMaxDefault[0] = 0;
    rayMaxDefault[1] = 0;
    rayMaxDefault[2] = 0;
    igVec3fMetaField_SetDefault((igMetaField *)raymax, (const float *)rayMaxDefault);
    raymin = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    rayMinDefault[0] = 0;
    rayMinDefault[1] = 0;
    rayMinDefault[2] = 0;
    igVec3fMetaField_SetDefault((igMetaField *)raymin, (const float *)rayMinDefault);
    rayList = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)rayList)->_metaObject = (int)igRayList_GetOrCreateMetaObject();
    ((igRefMetaField *)rayList)->_construct = 1;
    hitdataList = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)hitdataList)->_metaObject = (int)beHitLandResultDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)hitdataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beHitLandModelOrder_fieldTable, g_beHitLandModelOrder_fieldHandles, g_beHitLandModelOrder_fieldOffsets, base);
}

