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
    beLightCtrlInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beLightCtrlInfo_vtable[0];
    obj._lightSetList = 0;
    vtable = *(int *)((char *)&obj + *(int *)(((char * *)g_objectSystem)[0] + 916));
    obj._vtable = (int)&g_beLightCtrlInfo_vtable[0];
    igSmartPointer_igLightSetList_Destruct((igSmartPointer<igObject> *)(&obj._lightSetList), (short)(-1));
    beBaseInfo_Destroy((struct S_33ec80 *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_igLightSetList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igMetaEnum *beLightCtrl_GetMsgActionEnum(void) {
    if (g_beLightCtrlInfo_msgActionMetaEnum == 0) {
        g_beLightCtrlInfo_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beLightCtrlInfo_msgActionNames, g_beLightCtrlInfo_msgActionValues, 1);
    }
    return g_beLightCtrlInfo_msgActionMetaEnum;
}

