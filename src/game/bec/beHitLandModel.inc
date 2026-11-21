igMetaObject *g_beHitLandModel_metaObject;
igMetaField *g_beHitLandModel_orderMetaField;
igMetaField *g_beHitLandModel_hitTraversalMetaField;
igMetaField *g_beHitLandModel_probeMetaField;
igMetaField *g_beHitLandModel_isHitWallMetaField;
igMetaField *g_beHitLandModel_mat90MetaField;

beHitLandModel *beHitLandModel_CreateInstance(int allocator) {
    beHitLandModel_EnsureRegistered();
    return (beHitLandModel *)igMetaObject_CreateInstance(g_beHitLandModel_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beHitLandModel_GetOrCreateMetaObject(void) {
    if (g_beHitLandModel_metaObject == 0) {
        g_beHitLandModel_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beHitLandModel_metaObject;
}

void *beHitLandModel_GetMetaObject(void) {
    igMetaObject *g = g_beHitLandModel_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beHitLandModel_EnsureRegistered();
    }
    return g_beHitLandModel_metaObject;
}

int beHitLandModel_GetVTable(void) {
    HitLandModelView model;
    return *(int *)((char *)&model + g_objectSystem->vtableProbeOffset);
}

igSmartPointer<igObject> *igSmartPointer_beHitLandModelOrder_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beHitLandModelTraversal_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void beHitLandModel_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beHitLandModel_Register);
}

static igMetaObjectCallback g_beHitLandModel_callbackList[] = { beHitLandModelOrder_EnsureRegistered, beHitLandModelTraversal_EnsureRegistered, igProbe_EnsureRegistered, 0 };

CallbackArray *beHitLandModel_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandModel_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beHitLandModel_GetMetaObjectFunction,
        "beHitLandModel",
        0x70, /* instance size */
        beHitLandModel_GetVTable,
        beHitLandModel_InitFields,
        0, /* extra callback item */
        g_beHitLandModel_callbackList /* callback list */
    );
}

void beHitLandModel_GetMetaObjectFunction(void)
{
    beHitLandModel_GetMetaObject();
}

static FieldFactory g_beHitLandModel_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
};
static const char *g_beHitLandModel_fieldTable[] = {
    "_order",
    "_hitTraversal",
    "_probe",
    "_isHitWall",
    "_mat90",
};
static igMetaField **g_beHitLandModel_fieldHandles[] = {
    &g_beHitLandModel_orderMetaField,
    &g_beHitLandModel_hitTraversalMetaField,
    &g_beHitLandModel_probeMetaField,
    &g_beHitLandModel_isHitWallMetaField,
    &g_beHitLandModel_mat90MetaField,
};
static int g_beHitLandModel_fieldOffsets[] = {
    32,
    36,
    40,
    44,
    48,
};

void beHitLandModel_InitFields(void) {
    int base;
    void *order;
    void *hitTraversal;
    void *probe;
    igMetaObject *meta;

    meta = g_beHitLandModel_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beHitLandModel_ctorTable, 5);
    order = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)order)->_metaObject = (int)beHitLandModelOrder_GetOrCreateMetaObject();
    hitTraversal = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)hitTraversal)->_metaObject = (int)beHitLandModelTraversal_GetOrCreateMetaObject();
    probe = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)probe)->_metaObject = (int)igProbe_GetOrCreateMetaObject();
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base + 3)))->setDefault(1);
    igMetaObject_NameFields(meta, g_beHitLandModel_fieldTable, g_beHitLandModel_fieldHandles, g_beHitLandModel_fieldOffsets, base);
}

