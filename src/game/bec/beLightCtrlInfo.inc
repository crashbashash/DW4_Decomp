igMetaObject *g_beLightCtrlInfo_metaObject;
igMetaField *g_beLightCtrlInfo_lightSetListMetaField;

void *beLightCtrlInfo_GetMetaObject(void) {
    igMetaObject *g = g_beLightCtrlInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLightCtrlInfo_EnsureRegistered();
    }
    return g_beLightCtrlInfo_metaObject;
}

int beLightCtrlInfo_GetVTable(void) {
    struct W_35bd50 o;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    o.vt = g_beLightCtrlInfo_vtable;
    o.f[6] = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beLightCtrlInfo_vtable;
    FUN_0035bdd0((igSmartPointer<igObject> *)(&o.f[6]), (short)(-1));
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

igSmartPointer<igObject> *FUN_0035bdd0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beLightCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLightCtrlInfo_Register);
}

static igMetaObjectCallback g_beLightCtrlInfo_callbackList[] = { igLightSetList_EnsureRegistered, 0 };

void *beLightCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLightCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beLightCtrlInfo_GetMetaObjectFunction,
        "beLightCtrlInfo",
        0x20, /* instance size */
        beLightCtrlInfo_GetVTable,
        beLightCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beLightCtrlInfo_callbackList /* callback list */
    );
}

void beLightCtrlInfo_GetMetaObjectFunction(void)
{
    beLightCtrlInfo_GetMetaObject();
}

static FieldFactory g_beLightCtrlInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beLightCtrlInfo_fieldTable[] = {
    "_lightSetList",
};
static igMetaField **g_beLightCtrlInfo_fieldHandles[] = {
    &g_beLightCtrlInfo_lightSetListMetaField,
};
static int g_beLightCtrlInfo_fieldOffsets[] = {
    28,
};

void beLightCtrlInfo_InitFields(void) {
    int base;
    void *lightSetList;
    void *meta;

    meta = (void *)g_beLightCtrlInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beLightCtrlInfo_ctorTable, 1);
    lightSetList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)lightSetList)->_metaObject = (int)igLightSetList_GetOrCreateMetaObject();
    ((igRefMetaField *)lightSetList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beLightCtrlInfo_fieldTable, g_beLightCtrlInfo_fieldHandles, g_beLightCtrlInfo_fieldOffsets, base);
}

igMetaEnum *g_beLightCtrlInfo_msgActionMetaEnum;
static const char *g_beLightCtrlInfo_msgActionNames[] = {
    "SETCOLOR",
};
static int g_beLightCtrlInfo_msgActionValues[] = {
    0,
};

igMetaEnum *FUN_0035bfb0(void) {
    if (g_beLightCtrlInfo_msgActionMetaEnum == 0) {
        g_beLightCtrlInfo_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beLightCtrlInfo_msgActionNames, g_beLightCtrlInfo_msgActionValues, 1);
    }
    return g_beLightCtrlInfo_msgActionMetaEnum;
}

