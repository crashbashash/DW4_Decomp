igMetaObject *g_beSwitchCtrlInfo_metaObject;
igMetaField *g_beSwitchCtrlInfo_switchNodeMetaField;

void *beSwitchCtrlInfo_GetMetaObject(void) {
    igMetaObject *g = g_beSwitchCtrlInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSwitchCtrlInfo_EnsureRegistered();
    }
    return g_beSwitchCtrlInfo_metaObject;
}

int beSwitchCtrlInfo_GetVTable(void) {
    beSwitchCtrlInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beSwitchCtrlInfo_vtable[0];
    obj._switchNode = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSwitchCtrlInfo_vtable[0];
    igSmartPointer_igSwitch_Destruct((igSmartPointer<igObject> *)(&obj._switchNode), -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_igSwitch_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beSwitchCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSwitchCtrlInfo_Register);
}

static igMetaObjectCallback g_beSwitchCtrlInfo_callbackList[] = { igSwitch_EnsureRegistered, 0 };

CallbackArray *beSwitchCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSwitchCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSwitchCtrlInfo_GetMetaObjectFunction,
        "beSwitchCtrlInfo",
        0x20, /* instance size */
        beSwitchCtrlInfo_GetVTable,
        beSwitchCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beSwitchCtrlInfo_callbackList /* callback list */
    );
}

void beSwitchCtrlInfo_GetMetaObjectFunction(void)
{
    beSwitchCtrlInfo_GetMetaObject();
}

static FieldFactory g_beSwitchCtrlInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beSwitchCtrlInfo_fieldTable[] = {
    "_switchNode",
};
static igMetaField **g_beSwitchCtrlInfo_fieldHandles[] = {
    &g_beSwitchCtrlInfo_switchNodeMetaField,
};
static int g_beSwitchCtrlInfo_fieldOffsets[] = {
    28,
};

void beSwitchCtrlInfo_InitFields(void) {
    int base;
    void *switchNode;
    igMetaObject *meta;

    meta = g_beSwitchCtrlInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSwitchCtrlInfo_ctorTable, 1);
    switchNode = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)switchNode)->_metaObject = (int)igSwitch_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beSwitchCtrlInfo_fieldTable, g_beSwitchCtrlInfo_fieldHandles, g_beSwitchCtrlInfo_fieldOffsets, base);
}

igMetaEnum *g_beSwitchCtrlInfo_msgActionMetaEnum;
static const char *g_beSwitchCtrlInfo_msgActionNames[] = {
    "ALLON", "ALLOF",
};
static int g_beSwitchCtrlInfo_msgActionValues[] = {
    0, 1,
};

igMetaEnum *beSwitchCtrl_GetMessageEnum(void) {
    if (g_beSwitchCtrlInfo_msgActionMetaEnum == 0) {
        g_beSwitchCtrlInfo_msgActionMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("MsgAction", g_beSwitchCtrlInfo_msgActionNames, g_beSwitchCtrlInfo_msgActionValues, 2);
    }
    return g_beSwitchCtrlInfo_msgActionMetaEnum;
}

