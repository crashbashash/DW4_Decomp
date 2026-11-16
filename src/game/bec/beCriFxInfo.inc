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
    beCriFxInfo obj;
    int vtable;
    int *xbFxParamSlot;
    int *targetSlot;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beCriFxInfo_vtable[0];
    targetSlot = &obj._target;
    *targetSlot = 0;
    xbFxParamSlot = &obj._xbFxParam;
    *xbFxParamSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beCriFxInfo_vtable[0];
    igSmartPointer_beCriFxXbData_Destruct((igSmartPointer<igObject> *)xbFxParamSlot, -1);
    igStringRef_Destruct(targetSlot, -1);
    igInfo_Destroy(&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beCriFxXbData_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

CallbackArray *beCriFxInfo_Register(void) {
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
    igMetaObject *meta;

    meta = g_beCriFxInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCriFxInfo_ctorTable, 4);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base), 0);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 1), -1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 2), -1);
    xbFxParam = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)xbFxParam)->_metaObject = (int)beCriFxXbData_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beCriFxInfo_fieldTable, g_beCriFxInfo_fieldHandles, g_beCriFxInfo_fieldOffsets, base);
}

