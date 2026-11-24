igMetaObject *g_beModelCtrlAIMap_metaObject;
igMetaField *g_beModelCtrlAIMap_x1SquareMetaField;
igMetaField *g_beModelCtrlAIMap_x2SquareMetaField;
igMetaField *g_beModelCtrlAIMap_x3SquareMetaField;
igMetaField *g_beModelCtrlAIMap_rotLimiterMetaField;
igMetaField *g_beModelCtrlAIMap_zoneAMetaField;
igMetaField *g_beModelCtrlAIMap_zoneBMetaField;
igMetaField *g_beModelCtrlAIMap_zoneCMetaField;
igMetaField *g_beModelCtrlAIMap_zoneDMetaField;
igMetaField *g_beModelCtrlAIMap_targetTypeMetaField;
igMetaField *g_beModelCtrlAIMap_targetModeMetaField;

void *beModelCtrlAIMap_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlAIMap_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlAIMap_EnsureRegistered();
    }
    return g_beModelCtrlAIMap_metaObject;
}

int beModelCtrlAIMap_GetVTable(void) {
    beModelCtrlAIMap obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beModelCtrlAIMap_vtable[0];
    obj._zoneA = 0;
    obj._zoneB = 0;
    obj._zoneC = 0;
    obj._zoneD = 0;
    obj._targetType = 0;
    obj._targetMode = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beModelCtrlAIMap_vtable[0];
    igStringRef_Destruct((igStringRef *)&obj._targetMode, -1);
    igStringRef_Destruct((igStringRef *)&obj._targetType, -1);
    igSmartPointer_beModelCtrlAIDataList_Destruct((igSmartPointer<igObject> *)(&obj._zoneD), (short)(-1));
    igSmartPointer_beModelCtrlAIDataList_Destruct((igSmartPointer<igObject> *)(&obj._zoneC), (short)(-1));
    igSmartPointer_beModelCtrlAIDataList_Destruct((igSmartPointer<igObject> *)(&obj._zoneB), (short)(-1));
    igSmartPointer_beModelCtrlAIDataList_Destruct((igSmartPointer<igObject> *)(&obj._zoneA), (short)(-1));
    igNamedObject_Destroy((igNamedObject *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlAIDataList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void beModelCtrlAIMap_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIMap_Register);
}

static igMetaObjectCallback g_beModelCtrlAIMap_callbackList[] = { Gap::Bec::beModelCtrlAIDataList::arkRegister, 0 };

CallbackArray *beModelCtrlAIMap_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlAIMap_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlAIMap_GetMetaObjectFunction,
        "beModelCtrlAIMap",
        0x34, /* instance size */
        beModelCtrlAIMap_GetVTable,
        beModelCtrlAIMap_InitFields,
        0, /* extra callback item */
        g_beModelCtrlAIMap_callbackList /* callback list */
    );
}

void beModelCtrlAIMap_GetMetaObjectFunction(void)
{
    beModelCtrlAIMap_GetMetaObject();
}

static FieldFactory g_beModelCtrlAIMap_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_beModelCtrlAIMap_fieldTable[] = {
    "_x1Square",
    "_x2Square",
    "_x3Square",
    "_rotLimiter",
    "_zoneA",
    "_zoneB",
    "_zoneC",
    "_zoneD",
    "_targetType",
    "_targetMode",
};
static igMetaField **g_beModelCtrlAIMap_fieldHandles[] = {
    &g_beModelCtrlAIMap_x1SquareMetaField,
    &g_beModelCtrlAIMap_x2SquareMetaField,
    &g_beModelCtrlAIMap_x3SquareMetaField,
    &g_beModelCtrlAIMap_rotLimiterMetaField,
    &g_beModelCtrlAIMap_zoneAMetaField,
    &g_beModelCtrlAIMap_zoneBMetaField,
    &g_beModelCtrlAIMap_zoneCMetaField,
    &g_beModelCtrlAIMap_zoneDMetaField,
    &g_beModelCtrlAIMap_targetTypeMetaField,
    &g_beModelCtrlAIMap_targetModeMetaField,
};
static int g_beModelCtrlAIMap_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
};

void beModelCtrlAIMap_InitFields(void) {
    void *zoneA;
    void *zoneB;
    void *zoneC;
    void *zoneD;
    void *meta;
    int base;

    meta = (void *)g_beModelCtrlAIMap_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beModelCtrlAIMap_ctorTable, 0xA);
    zoneA = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4));
    ((igObjectRefMetaField *)zoneA)->_metaObject = (int)Gap::Bec::beModelCtrlAIDataList::getClassTypeLazy();
    ((igRefMetaField *)zoneA)->_construct = 1;
    zoneB = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5));
    ((igObjectRefMetaField *)zoneB)->_metaObject = (int)Gap::Bec::beModelCtrlAIDataList::getClassTypeLazy();
    ((igRefMetaField *)zoneB)->_construct = 1;
    zoneC = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6));
    ((igObjectRefMetaField *)zoneC)->_metaObject = (int)Gap::Bec::beModelCtrlAIDataList::getClassTypeLazy();
    ((igRefMetaField *)zoneC)->_construct = 1;
    zoneD = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7));
    ((igObjectRefMetaField *)zoneD)->_metaObject = (int)Gap::Bec::beModelCtrlAIDataList::getClassTypeLazy();
    ((igRefMetaField *)zoneD)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beModelCtrlAIMap_fieldTable, g_beModelCtrlAIMap_fieldHandles, g_beModelCtrlAIMap_fieldOffsets, base);
}

