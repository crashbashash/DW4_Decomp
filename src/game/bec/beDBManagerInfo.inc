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
    struct Obj_365e10 o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f20 = 0;
    o.f24 = 0;
    o.vt = &g_beDBManagerInfo_vtable[0];
    o.f28 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beDBManagerInfo_vtable[0];
    FUN_00365e90((igSmartPointer<igObject> *)&o.f28, (long long)(-1));
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

igSmartPointer<igObject> *FUN_00365e90(igSmartPointer<igObject> *self, long long delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beDBManagerInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDBManagerInfo_Register);
}

static igMetaObjectCallback g_beDBManagerInfo_callbackList[] = { beDataBase_EnsureRegistered, 0 };

void *beDBManagerInfo_Register(void) {
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
    void *meta;

    meta = (void *)g_beDBManagerInfo_metaObject;
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

igMetaEnum *FUN_00366070(void) {
    if (g_beDBManagerInfo_msgActionMetaEnum == 0) {
        g_beDBManagerInfo_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beDBManagerInfo_msgActionNames, g_beDBManagerInfo_msgActionValues, 1);
    }
    return g_beDBManagerInfo_msgActionMetaEnum;
}

