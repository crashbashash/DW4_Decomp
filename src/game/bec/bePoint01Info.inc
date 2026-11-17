igMetaObject *g_bePoint01Info_metaObject;
igMetaField *g_bePoint01Info_switchMetaField;
igMetaField *g_bePoint01Info_dataListMetaField;

void *bePoint01Info_GetMetaObject(void) {
    igMetaObject *g = g_bePoint01Info_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        bePoint01Info_EnsureRegistered();
    }
    return g_bePoint01Info_metaObject;
}

int bePoint01Info_GetVTable(void) {
    bePoint01Info obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_bePoint01Info_vtable[0];
    obj._switch = 0;
    obj._dataList_ = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_bePoint01Info_vtable[0];
    igSmartPointer_beGroupKeepList_Destruct((igSmartPointer<igObject> *)&obj._dataList_, -1);
    igSmartPointer_igSwitch_Destruct((igSmartPointer<igObject> *)&obj._switch, -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beGroupKeepList_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void bePoint01Info_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(bePoint01Info_Register);
}

static igMetaObjectCallback g_bePoint01Info_callbackList[] = { igSwitch_EnsureRegistered, beGroupKeepList_EnsureRegistered, 0 };

CallbackArray *bePoint01Info_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_bePoint01Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        bePoint01Info_GetMetaObjectFunction,
        "bePoint01Info",
        0x24, /* instance size */
        bePoint01Info_GetVTable,
        bePoint01Info_InitFields,
        0, /* extra callback item */
        g_bePoint01Info_callbackList /* callback list */
    );
}

void bePoint01Info_GetMetaObjectFunction(void)
{
    bePoint01Info_GetMetaObject();
}

static FieldFactory g_bePoint01Info_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_bePoint01Info_fieldTable[] = {
    "_switch",
    "_dataList",
};
static igMetaField **g_bePoint01Info_fieldHandles[] = {
    &g_bePoint01Info_switchMetaField,
    &g_bePoint01Info_dataListMetaField,
};
static int g_bePoint01Info_fieldOffsets[] = {
    28,
    32,
};

void bePoint01Info_InitFields(void) {
    int base;
    void *switchField;
    void *dataList;
    igMetaObject *meta;

    meta = g_bePoint01Info_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_bePoint01Info_ctorTable, 2);
    switchField = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)switchField)->_metaObject = (int)igSwitch_GetOrCreateMetaObject();
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beGroupKeepList_GetOrCreateMetaObject();
    ((igRefMetaField *)dataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_bePoint01Info_fieldTable, g_bePoint01Info_fieldHandles, g_bePoint01Info_fieldOffsets, base);
}

igMetaEnum *g_bePoint01Info_msgActionMetaEnum;
static const char *g_bePoint01Info_msgActionNames[] = {
    "SHOWPOLYGON", "HIDEPOLYGON", "GETMATRIX", "GETMATRIXDIRECT",
    "GETPOINTNAME", "SETGENERATEPOS", "GETGENERATEPOS",
};
static int g_bePoint01Info_msgActionValues[] = {
    0, 1, 2, 3, 4, 5, 6,
};

igMetaEnum *bePoint01_GetMsgActionEnum(void) {
    if (g_bePoint01Info_msgActionMetaEnum == 0) {
        g_bePoint01Info_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_bePoint01Info_msgActionNames, g_bePoint01Info_msgActionValues, 7);
    }
    return g_bePoint01Info_msgActionMetaEnum;
}

