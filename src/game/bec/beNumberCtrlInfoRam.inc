igMetaObject *g_beNumberCtrlInfoRam_metaObject;
igMetaField *g_beNumberCtrlInfoRam_geometryMetaField;
igMetaField *g_beNumberCtrlInfoRam_offsetNextMetaField;
igMetaField *g_beNumberCtrlInfoRam_maxValueMetaField;
igMetaField *g_beNumberCtrlInfoRam_modeMetaField;
igMetaField *g_beNumberCtrlInfoRam_numListMetaField;
igMetaField *g_beNumberCtrlInfoRam_workMetaField;

igMetaObject *beNumberCtrlInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beNumberCtrlInfoRam_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNumberCtrlInfoRam_EnsureRegistered();
done:
    return g_beNumberCtrlInfoRam_metaObject;
}

int beNumberCtrlInfoRam_GetVTable(void) {
    beNumberCtrlInfoRam obj;
    int *geometrySlot;
    int vtable;
    int *numListSlot;

    igObject_InitHeader(&obj);
    obj._dataList = 0;
    obj._vtable = (int)&g_beNumberCtrlInfoRam_vtable[0];
    geometrySlot = &obj._geometry;
    *geometrySlot = 0;
    numListSlot = &obj._numList;
    *numListSlot = 0;
    obj._work = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beNumberCtrlInfoRam_vtable[0];
    igSmartPointer_beNumberCtrlInfoWork_Destruct((igSmartPointer<igObject> *)(&obj._work), -1);
    igSmartPointer_beNumVerDataList_Destruct((igSmartPointer<igObject> *)numListSlot, (long long)(-1));
    igSmartPointer_igGeometry_Destruct((igSmartPointer<igObject> *)geometrySlot, -1);
    beBaseInfoRam_Destroy((beBaseInfoRam *)&obj, (long long)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beNumVerDataList_Destruct(igSmartPointer<igObject> *self, long long delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNumberCtrlInfoWork_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beNumberCtrlInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNumberCtrlInfoRam_Register);
}

static igMetaObjectCallback g_beNumberCtrlInfoRam_callbackList[] = { igGeometry_EnsureRegistered, beNumVerDataList_EnsureRegistered, beNumberCtrlInfoWork_EnsureRegistered, 0 };

CallbackArray *beNumberCtrlInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumberCtrlInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNumberCtrlInfoRam_GetMetaObjectFunction,
        "beNumberCtrlInfoRam",
        0x44, /* instance size */
        beNumberCtrlInfoRam_GetVTable,
        beNumberCtrlInfoRam_InitFields,
        0, /* extra callback item */
        g_beNumberCtrlInfoRam_callbackList /* callback list */
    );
}

void beNumberCtrlInfoRam_GetMetaObjectFunction(void)
{
    beNumberCtrlInfoRam_GetMetaObject();
}

static FieldFactory g_beNumberCtrlInfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNumberCtrlInfoRam_fieldTable[] = {
    "_geometry",
    "_offsetNext",
    "_maxValue",
    "_mode",
    "_numList",
    "_work",
};
static igMetaField **g_beNumberCtrlInfoRam_fieldHandles[] = {
    &g_beNumberCtrlInfoRam_geometryMetaField,
    &g_beNumberCtrlInfoRam_offsetNextMetaField,
    &g_beNumberCtrlInfoRam_maxValueMetaField,
    &g_beNumberCtrlInfoRam_modeMetaField,
    &g_beNumberCtrlInfoRam_numListMetaField,
    &g_beNumberCtrlInfoRam_workMetaField,
};
static int g_beNumberCtrlInfoRam_fieldOffsets[] = {
    44,
    48,
    52,
    56,
    60,
    64,
};

void beNumberCtrlInfoRam_InitFields(void) {
    int base;
    void *geometry;
    void *numList;
    void *work;
    igMetaObject *meta;

    meta = g_beNumberCtrlInfoRam_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNumberCtrlInfoRam_ctorTable, 6);
    geometry = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)geometry)->_metaObject = (int)igGeometry_GetOrCreateMetaObject();
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt(meta, base + 1)))->setDefault(0.09375f);
    numList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)numList)->_metaObject = (int)beNumVerDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)numList)->_construct = 1;
    work = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)work)->_metaObject = (int)beNumberCtrlInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNumberCtrlInfoRam_fieldTable, g_beNumberCtrlInfoRam_fieldHandles, g_beNumberCtrlInfoRam_fieldOffsets, base);
}

