igMetaObject *g_beNDMWMdlItemInfoWork_metaObject;
igMetaField *g_beNDMWMdlItemInfoWork_dbIdMetaField;
igMetaField *g_beNDMWMdlItemInfoWork_itemObjectMetaField;
igMetaField *g_beNDMWMdlItemInfoWork_kindMetaField;
igMetaField *g_beNDMWMdlItemInfoWork_isNamedMetaField;
igMetaField *g_beNDMWMdlItemInfoWork_dispPlayerRamNoMetaField;
igMetaField *g_beNDMWMdlItemInfoWork_isDispNameMetaField;
igMetaField *g_beNDMWMdlItemInfoWork_fontTypeMetaField;
igMetaField *g_beNDMWMdlItemInfoWork_isColorLightMetaField;

beNDMWMdlItemInfoWork *beNDMWMdlItemInfoWork_Create(int allocator) {
    beNDMWMdlItemInfoWork_EnsureRegistered();
    return (beNDMWMdlItemInfoWork *)igMetaObject_CreateInstance(g_beNDMWMdlItemInfoWork_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWMdlItemInfoWork_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlItemInfoWork_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWMdlItemInfoWork_EnsureRegistered();
done:
    return g_beNDMWMdlItemInfoWork_metaObject;
}

int beNDMWMdlItemInfoWork_GetVTable(void) {
    ItemInfoWork work;
    return *(int *)((char *)&work + g_objectSystem->vtableProbeOffset);
}

igSmartPointer<igObject> *igSmartPointer_beNDMWItemBase_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWItemBase_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

void beNDMWMdlItemInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlItemInfoWork_Register);
}

static igMetaObjectCallback g_beNDMWMdlItemInfoWork_callbackList[] = { beNDMWItemBase_EnsureRegistered, 0 };

CallbackArray *beNDMWMdlItemInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlItemInfoWork_metaObject,
        beModelCtrlInfoWork_Register,
        beModelCtrlInfoWork_GetPublishedMetaObject,
        beNDMWMdlItemInfoWork_GetMetaObject,
        "beNDMWMdlItemInfoWork",
        0x10c, /* instance size */
        beNDMWMdlItemInfoWork_GetVTable,
        beNDMWMdlItemInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlItemInfoWork_callbackList /* callback list */
    );
}

void beNDMWMdlItemInfoWork_GetMetaObject(void)
{
    beNDMWMdlItemInfoWork_GetReadyMetaObject();
}

static FieldFactory g_beNDMWMdlItemInfoWork_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igStringMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beNDMWMdlItemInfoWork_fieldTable[] = {
    "_dbId",
    "_itemObject",
    "_kind",
    "_isNamed",
    "_dispPlayerRamNo",
    "_isDispName",
    "_fontType",
    "_isColorLight",
};
static igMetaField **g_beNDMWMdlItemInfoWork_fieldHandles[] = {
    &g_beNDMWMdlItemInfoWork_dbIdMetaField,
    &g_beNDMWMdlItemInfoWork_itemObjectMetaField,
    &g_beNDMWMdlItemInfoWork_kindMetaField,
    &g_beNDMWMdlItemInfoWork_isNamedMetaField,
    &g_beNDMWMdlItemInfoWork_dispPlayerRamNoMetaField,
    &g_beNDMWMdlItemInfoWork_isDispNameMetaField,
    &g_beNDMWMdlItemInfoWork_fontTypeMetaField,
    &g_beNDMWMdlItemInfoWork_isColorLightMetaField,
};
static int g_beNDMWMdlItemInfoWork_fieldOffsets[] = {
    236,
    240,
    244,
    248,
    252,
    256,
    260,
    264,
};

void beNDMWMdlItemInfoWork_InitFields(void) {
    int base;
    void *itemObject;
    igMetaObject *meta;

    meta = g_beNDMWMdlItemInfoWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWMdlItemInfoWork_ctorTable, 8);
    itemObject = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)itemObject)->_metaObject = (int)beNDMWItemBase_GetOrCreateMetaObject();
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt(meta, base + 4)))->setDefault(-1);
    igMetaObject_NameFields(meta, g_beNDMWMdlItemInfoWork_fieldTable, g_beNDMWMdlItemInfoWork_fieldHandles, g_beNDMWMdlItemInfoWork_fieldOffsets, base);
}

