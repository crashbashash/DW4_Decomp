igMetaObject *g_beHitLandDelivInfoRam_metaObject;
igMetaField *g_beHitLandDelivInfoRam_transformMetaField;
igMetaField *g_beHitLandDelivInfoRam_checkFlagMetaField;
igMetaField *g_beHitLandDelivInfoRam_halfWidthMetaField;
igMetaField *g_beHitLandDelivInfoRam_upRangeMetaField;
igMetaField *g_beHitLandDelivInfoRam_downRangeMetaField;
igMetaField *g_beHitLandDelivInfoRam_posMetaField;
igMetaField *g_beHitLandDelivInfoRam_oldPosMetaField;
igMetaField *g_beHitLandDelivInfoRam_landPosMetaField;
igMetaField *g_beHitLandDelivInfoRam_landPosOKMetaField;

void *beHitLandDelivInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beHitLandDelivInfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beHitLandDelivInfoRam_EnsureRegistered();
    }
    return g_beHitLandDelivInfoRam_metaObject;
}

int beHitLandDelivInfoRam_GetVTable(void) {
    beHitLandDelivInfoRam obj;
    int vtable;
    igObject **transformSlot;
    igObject **dataListSlot;

    igObject_InitHeader(&obj);
    dataListSlot = (igObject **)&obj._dataList;
    *dataListSlot = 0;
    obj._vtable = (int)&g_beHitLandDelivInfoRam_vtable[0];
    transformSlot = (igObject **)&obj._transform;
    *transformSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beHitLandDelivInfoRam_vtable[0];
    igObjectRef_Release(transformSlot);
    obj._vtable = (int)&g_beBaseInfoRam_vtable[0];
    igObjectRef_Release(dataListSlot);
    return vtable;
}

void beHitLandDelivInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beHitLandDelivInfoRam_Register);
}

static igMetaObjectCallback g_beHitLandDelivInfoRam_callbackList[] = { igTransform_EnsureRegistered, 0 };

CallbackArray *beHitLandDelivInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandDelivInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beHitLandDelivInfoRam_GetMetaObjectFunction,
        "beHitLandDelivInfoRam",
        0x68, /* instance size */
        beHitLandDelivInfoRam_GetVTable,
        beHitLandDelivInfoRam_InitFields,
        0, /* extra callback item */
        g_beHitLandDelivInfoRam_callbackList /* callback list */
    );
}

void beHitLandDelivInfoRam_GetMetaObjectFunction(void)
{
    beHitLandDelivInfoRam_GetMetaObject();
}

static FieldFactory g_beHitLandDelivInfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    igBoolMetaField_Create,
};
static const char *g_beHitLandDelivInfoRam_fieldTable[] = {
    "_transform",
    "_checkFlag",
    "_halfWidth",
    "_upRange",
    "_downRange",
    "_pos",
    "_oldPos",
    "_landPos",
    "_landPosOK",
};
static igMetaField **g_beHitLandDelivInfoRam_fieldHandles[] = {
    &g_beHitLandDelivInfoRam_transformMetaField,
    &g_beHitLandDelivInfoRam_checkFlagMetaField,
    &g_beHitLandDelivInfoRam_halfWidthMetaField,
    &g_beHitLandDelivInfoRam_upRangeMetaField,
    &g_beHitLandDelivInfoRam_downRangeMetaField,
    &g_beHitLandDelivInfoRam_posMetaField,
    &g_beHitLandDelivInfoRam_oldPosMetaField,
    &g_beHitLandDelivInfoRam_landPosMetaField,
    &g_beHitLandDelivInfoRam_landPosOKMetaField,
};
static int g_beHitLandDelivInfoRam_fieldOffsets[] = {
    44,
    48,
    52,
    56,
    60,
    64,
    76,
    88,
    100,
};

void beHitLandDelivInfoRam_InitFields(void) {
    void *pos;
    int base;
    void *transform;
    int va[3];
    int vb[3];
    int vc[3];
    void *landPos;
    void *oldPos;
    igMetaObject *meta;

    meta = g_beHitLandDelivInfoRam_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beHitLandDelivInfoRam_ctorTable, 9);
    transform = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)transform)->_metaObject = (int)igTransform_GetOrCreateMetaObject();
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt(meta, base + 2)))->setDefault(3.0f);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt(meta, 3 + base)))->setDefault(4.0f);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt(meta, 4 + base)))->setDefault(4.0f);
    pos = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    va[0] = 0;
    va[1] = 0;
    va[2] = 0;
    ((Gap::Math::igVec3fMetaField *)pos)->setDefault(*(const igVec3f *)va);
    oldPos = (void *)(igMetaObject_GetFieldAt(meta, 6 + base));
    vb[0] = 0;
    vb[1] = 0;
    vb[2] = 0;
    ((Gap::Math::igVec3fMetaField *)oldPos)->setDefault(*(const igVec3f *)vb);
    landPos = (void *)(igMetaObject_GetFieldAt(meta, 7 + base));
    vc[0] = 0;
    vc[1] = 0;
    vc[2] = 0;
    ((Gap::Math::igVec3fMetaField *)landPos)->setDefault(*(const igVec3f *)vc);
    igMetaObject_NameFields(meta, g_beHitLandDelivInfoRam_fieldTable, g_beHitLandDelivInfoRam_fieldHandles, g_beHitLandDelivInfoRam_fieldOffsets, base);
}

