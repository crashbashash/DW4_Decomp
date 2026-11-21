igMetaObject *g_beLayerInfo_metaObject;
igMetaField *g_beLayerInfo_groupsMetaField;

void *beLayerInfo_GetMetaObject(void) {
    igMetaObject *g = g_beLayerInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLayerInfo_EnsureRegistered();
    }
    return g_beLayerInfo_metaObject;
}

int beLayerInfo_GetVTable(void) {
    beLayerInfo obj;
    int vtable;
    char *groupsSlot;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beLayerInfo_vtable[0];
    groupsSlot = (char *)&obj._groups;
    *(int *)groupsSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beLayerInfo_vtable[0];
    igSmartPointer_beLayerGroupList_Destruct((igSmartPointer<igObject> *)groupsSlot, -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beLayerGroupList_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beLayerInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLayerInfo_Register);
}

static igMetaObjectCallback g_beLayerInfo_callbackList[] = { beLayerGroupList_EnsureRegistered, 0 };

CallbackArray *beLayerInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLayerInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beLayerInfo_GetMetaObjectFunction,
        "beLayerInfo",
        0x20, /* instance size */
        beLayerInfo_GetVTable,
        beLayerInfo_InitFields,
        0, /* extra callback item */
        g_beLayerInfo_callbackList /* callback list */
    );
}

void beLayerInfo_GetMetaObjectFunction(void)
{
    beLayerInfo_GetMetaObject();
}

static FieldFactory g_beLayerInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beLayerInfo_fieldTable[] = {
    "_groups",
};
static igMetaField **g_beLayerInfo_fieldHandles[] = {
    &g_beLayerInfo_groupsMetaField,
};
static int g_beLayerInfo_fieldOffsets[] = {
    28,
};

void beLayerInfo_InitFields(void) {
    int base;
    void *groups;
    igMetaObject *meta;

    meta = g_beLayerInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beLayerInfo_ctorTable, 1);
    groups = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)groups)->_metaObject = (int)beLayerGroupList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beLayerInfo_fieldTable, g_beLayerInfo_fieldHandles, g_beLayerInfo_fieldOffsets, base);
}

