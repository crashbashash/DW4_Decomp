igMetaObject *g_beMatCtrlInfoRam_metaObject;
igMetaField *g_beMatCtrlInfoRam_workMetaField;

void *beMatCtrlInfoRam_GetMetaObject(void) {
    bool ok;
    if (g_beMatCtrlInfoRam_metaObject == 0) goto make;
    ok = !!(g_beMatCtrlInfoRam_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beMatCtrlInfoRam_EnsureRegistered();
done:;
    return g_beMatCtrlInfoRam_metaObject;
}

int beMatCtrlInfoRam_GetVTable(void) {
    beMatCtrlInfoRam obj;
    int vtable;
    igObject **workSlot;
    igObject **dataListSlot;

    igObject_InitHeader(&obj);
    dataListSlot = (igObject **)&obj._dataList;
    *dataListSlot = 0;
    obj._vtable = (int)&g_beMatCtrlInfoRam_vtable[0];
    workSlot = (igObject **)&obj._work;
    *workSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beMatCtrlInfoRam_vtable[0];
    igObjectRef_Release(workSlot);
    obj._vtable = (int)&g_beBaseInfoRam_vtable[0];
    igObjectRef_Release(dataListSlot);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beMatCtrlInfoWork_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void beMatCtrlInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMatCtrlInfoRam_Register);
}

static igMetaObjectCallback g_beMatCtrlInfoRam_callbackList[] = { beMatCtrlInfoWork_EnsureRegistered, 0 };

CallbackArray *beMatCtrlInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMatCtrlInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beMatCtrlInfoRam_GetMetaObjectFunction,
        "beMatCtrlInfoRam",
        0x30, /* instance size */
        beMatCtrlInfoRam_GetVTable,
        beMatCtrlInfoRam_InitFields,
        0, /* extra callback item */
        g_beMatCtrlInfoRam_callbackList /* callback list */
    );
}

void beMatCtrlInfoRam_GetMetaObjectFunction(void)
{
    beMatCtrlInfoRam_GetMetaObject();
}

static FieldFactory g_beMatCtrlInfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beMatCtrlInfoRam_fieldTable[] = {
    "_work",
};
static igMetaField **g_beMatCtrlInfoRam_fieldHandles[] = {
    &g_beMatCtrlInfoRam_workMetaField,
};
static int g_beMatCtrlInfoRam_fieldOffsets[] = {
    44,
};

void beMatCtrlInfoRam_InitFields(void) {
    int base;
    void *work;
    igMetaObject *meta;

    meta = g_beMatCtrlInfoRam_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMatCtrlInfoRam_ctorTable, 1);
    work = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)work)->_metaObject = (int)beMatCtrlInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beMatCtrlInfoRam_fieldTable, g_beMatCtrlInfoRam_fieldHandles, g_beMatCtrlInfoRam_fieldOffsets, base);
}

