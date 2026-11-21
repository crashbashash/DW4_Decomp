igMetaObject *g_beBkColorInfo_metaObject;
igMetaField *g_beBkColorInfo_rgbaMetaField;

void *beBkColorInfo_GetMetaObject(void) {
    igMetaObject *g = g_beBkColorInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beBkColorInfo_EnsureRegistered();
    }
    return g_beBkColorInfo_metaObject;
}

int beBkColorInfo_GetVTable(void) {
    beBkColorInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beBkColorInfo_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beBkColorInfo_vtable[0];
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

void beBkColorInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBkColorInfo_Register);
}

CallbackArray *beBkColorInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beBkColorInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beBkColorInfo_GetMetaObjectFunction,
        "beBkColorInfo",
        0x2c, /* instance size */
        beBkColorInfo_GetVTable,
        beBkColorInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beBkColorInfo_GetMetaObjectFunction(void)
{
    beBkColorInfo_GetMetaObject();
}

static FieldFactory g_beBkColorInfo_ctorTable[] = {
    (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool,
};
static const char *g_beBkColorInfo_fieldTable[] = {
    "_rgba",
};
static igMetaField **g_beBkColorInfo_fieldHandles[] = {
    &g_beBkColorInfo_rgbaMetaField,
};
static int g_beBkColorInfo_fieldOffsets[] = {
    28,
};

void beBkColorInfo_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beBkColorInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beBkColorInfo_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beBkColorInfo_fieldTable, g_beBkColorInfo_fieldHandles, g_beBkColorInfo_fieldOffsets, base);
}

