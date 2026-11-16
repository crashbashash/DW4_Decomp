igMetaObject *g_beCriFxInfo_metaObject;
igMetaField *g_beCriFxInfo_targetMetaField;
igMetaField *g_beCriFxInfo_reverbMetaField;
igMetaField *g_beCriFxInfo_delayMetaField;
igMetaField *g_beCriFxInfo_xbFxParamMetaField;

void *beCriFxInfo_GetMetaObject(void) {
    bool ok;
    if (g_beCriFxInfo_metaObject == 0) goto make;
    ok = !!(g_beCriFxInfo_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beCriFxInfo_EnsureRegistered();
done:;
    return g_beCriFxInfo_metaObject;
}

int beCriFxInfo_GetVTable(void) {
    struct Obj obj;
    int r;
    int *pb;
    int *pa;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.vt = &g_beCriFxInfo_vtable[0];
    pa = &obj.f14;
    *pa = 0;
    pb = &obj.f20;
    *pb = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beCriFxInfo_vtable[0];
    FUN_00366d80((igSmartPointer<igObject> *)pb, -1);
    igStringRef_Destruct(pa, -1);
    igInfo_Destroy(&obj, 0);
    return r;
}

igSmartPointer<igObject> *FUN_00366d80(igSmartPointer<igObject> *self, int delete_storage) {
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

void beCriFxInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCriFxInfo_Register);
}

static igMetaObjectCallback g_beCriFxInfo_callbackList[] = { beCriFxXbData_EnsureRegistered, 0 };

void *beCriFxInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCriFxInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beCriFxInfo_GetMetaObjectFunction,
        "beCriFxInfo",
        0x24, /* instance size */
        beCriFxInfo_GetVTable,
        beCriFxInfo_InitFields,
        0, /* extra callback item */
        g_beCriFxInfo_callbackList /* callback list */
    );
}

void beCriFxInfo_GetMetaObjectFunction(void)
{
    beCriFxInfo_GetMetaObject();
}

static FieldFactory g_beCriFxInfo_ctorTable[] = {
    igStringMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beCriFxInfo_fieldTable[] = {
    "_target",
    "_reverb",
    "_delay",
    "_xbFxParam",
};
static igMetaField **g_beCriFxInfo_fieldHandles[] = {
    &g_beCriFxInfo_targetMetaField,
    &g_beCriFxInfo_reverbMetaField,
    &g_beCriFxInfo_delayMetaField,
    &g_beCriFxInfo_xbFxParamMetaField,
};
static int g_beCriFxInfo_fieldOffsets[] = {
    20,
    24,
    28,
    32,
};

void beCriFxInfo_InitFields(void) {
    int base;
    void *xbFxParam;
    void *meta;

    meta = (void *)g_beCriFxInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCriFxInfo_ctorTable, 4);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base), 0);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 1), -1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 2), -1);
    xbFxParam = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)xbFxParam)->_metaObject = (int)beCriFxXbData_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beCriFxInfo_fieldTable, g_beCriFxInfo_fieldHandles, g_beCriFxInfo_fieldOffsets, base);
}

