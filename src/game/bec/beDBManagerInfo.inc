igMetaObject *g_beDBManagerInfo_metaObject;
igMetaField *g_beDBManagerInfo_dataBaseMetaField;

igMetaObject *beDBManagerInfo_GetMetaObject(void)
{
    igMetaObject *g = g_beDBManagerInfo_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beDBManagerInfo_EnsureRegistered();
    return g_beDBManagerInfo_metaObject;
}

int beDBManagerInfo_GetVTable(void) {
    beDBManagerInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beDBManagerInfo_vtable[0];
    obj._dataBase = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beDBManagerInfo_vtable[0];
    igSmartPointer_beDataBase_Destruct((igSmartPointer<igObject> *)&obj._dataBase, -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beDataBase_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

void beDBManagerInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDBManagerInfo_Register);
}

static igMetaObjectCallback g_beDBManagerInfo_callbackList[] = { beDataBase_EnsureRegistered, 0 };

CallbackArray *beDBManagerInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDBManagerInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beDBManagerInfo_GetMetaObjectFunction,
        "beDBManagerInfo",
        0x20, /* instance size */
        beDBManagerInfo_GetVTable,
        beDBManagerInfo_InitFields,
        0, /* extra callback item */
        g_beDBManagerInfo_callbackList /* callback list */
    );
}

void beDBManagerInfo_GetMetaObjectFunction(void)
{
    beDBManagerInfo_GetMetaObject();
}

static FieldFactory g_beDBManagerInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beDBManagerInfo_fieldTable[] = {
    "_dataBase",
};
static igMetaField **g_beDBManagerInfo_fieldHandles[] = {
    &g_beDBManagerInfo_dataBaseMetaField,
};
static int g_beDBManagerInfo_fieldOffsets[] = {
    28,
};

void beDBManagerInfo_InitFields(void) {
    int base;
    void *dataBase;
    igMetaObject *meta;

    meta = g_beDBManagerInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDBManagerInfo_ctorTable, 1);
    dataBase = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)dataBase)->_metaObject = (int)beDataBase_GetOrCreateMetaObject();
    ((igRefMetaField *)dataBase)->_construct = 1;
    igMetaObject_NameFields(meta, g_beDBManagerInfo_fieldTable, g_beDBManagerInfo_fieldHandles, g_beDBManagerInfo_fieldOffsets, base);
}

igMetaEnum *g_beDBManagerInfo_msgActionMetaEnum;
static const char *g_beDBManagerInfo_msgActionNames[] = {
    "GETDATABASE",
};
static int g_beDBManagerInfo_msgActionValues[] = {
    0,
};

igMetaEnum *beDBManager_GetMsgActionEnum(void) {
    if (g_beDBManagerInfo_msgActionMetaEnum == 0) {
        g_beDBManagerInfo_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beDBManagerInfo_msgActionNames, g_beDBManagerInfo_msgActionValues, 1);
    }
    return g_beDBManagerInfo_msgActionMetaEnum;
}

