igMetaObject *g_beGeneraterInfoRam_metaObject;
igMetaField *g_beGeneraterInfoRam_workMetaField;

igMetaObject *beGeneraterInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beGeneraterInfoRam_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beGeneraterInfoRam_EnsureRegistered();
    return g_beGeneraterInfoRam_metaObject;
}

int beGeneraterInfoRam_GetVTable(void) {
    beGeneraterInfoRam obj;
    int vtable;
    igObject **workSlot;
    igObject **dataListSlot;

    igObject_InitHeader(&obj);
    dataListSlot = (igObject **)&obj._dataList;
    *dataListSlot = 0;
    obj._vtable = (int)&g_beGeneraterInfoRam_vtable[0];
    workSlot = (igObject **)&obj._work;
    *workSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beGeneraterInfoRam_vtable[0];
    igObjectRef_Release(workSlot);
    obj._vtable = (int)&g_beBaseInfoRam_vtable[0];
    igObjectRef_Release(dataListSlot);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beGeneraterInfoWork_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

void beGeneraterInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterInfoRam_Register);
}

static igMetaObjectCallback g_beGeneraterInfoRam_callbackList[] = { beGeneraterInfoWork_EnsureRegistered, 0 };

CallbackArray *beGeneraterInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beGeneraterInfoRam_GetMetaObjectFunction,
        "beGeneraterInfoRam",
        0x30, /* instance size */
        beGeneraterInfoRam_GetVTable,
        beGeneraterInfoRam_InitFields,
        0, /* extra callback item */
        g_beGeneraterInfoRam_callbackList /* callback list */
    );
}

void beGeneraterInfoRam_GetMetaObjectFunction(void)
{
    beGeneraterInfoRam_GetMetaObject();
}

static FieldFactory g_beGeneraterInfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beGeneraterInfoRam_fieldTable[] = {
    "_work",
};
static igMetaField **g_beGeneraterInfoRam_fieldHandles[] = {
    &g_beGeneraterInfoRam_workMetaField,
};
static int g_beGeneraterInfoRam_fieldOffsets[] = {
    44,
};

void beGeneraterInfoRam_InitFields(void) {
    int base;
    void *work;
    igMetaObject *meta;

    meta = g_beGeneraterInfoRam_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beGeneraterInfoRam_ctorTable, 1);
    work = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)work)->_metaObject = (int)beGeneraterInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beGeneraterInfoRam_fieldTable, g_beGeneraterInfoRam_fieldHandles, g_beGeneraterInfoRam_fieldOffsets, base);
}

