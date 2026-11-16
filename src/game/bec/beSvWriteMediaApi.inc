igMetaObject *g_beSvWriteMediaApi_metaObject;
igMetaField *g_beSvWriteMediaApi_nowGamedataMetaField;
igMetaField *g_beSvWriteMediaApi_saveWorkMetaField;

void beSvWriteMediaApi_Create(int allocator) {
    beSvWriteMediaApi_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588220, allocator);
}

igMetaObject *beSvWriteMediaApi_GetMetaObject(void) {
    igMetaObject *g = g_beSvWriteMediaApi_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beSvWriteMediaApi_EnsureRegistered();
done:
    return g_beSvWriteMediaApi_metaObject;
}

int beSvWriteMediaApi_GetVTable(void) {
    beSvWriteMediaApi obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._imageWork = 0;
    obj._mountWork = 0;
    obj._iconWork = 0;
    obj._vtable = (int)&g_beSvWriteMediaApi_vtable[0];
    obj._nowGamedata = 0;
    obj._saveWork = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beSvWriteMediaApi_vtable[0];
    igSmartPointer_beSaveMemoryObj_Destruct((igSmartPointer<igObject> *)&obj._saveWork, (short)(-1));
    igSmartPointer_beSvPlatBaseData_Destruct((igSmartPointer<igObject> *)&obj._nowGamedata, (long long)(-1));
    beSaveApi_Destroy((beSaveApi *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beSvPlatBaseData_Destruct(igSmartPointer<igObject> *self, long long delete_storage) {
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

void beSvWriteMediaApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvWriteMediaApi_Register);
}

static igMetaObjectCallback g_beSvWriteMediaApi_callbackList[] = { beSvPlatBaseData_EnsureRegistered, beSaveMemoryObj_EnsureRegistered, 0 };

void *beSvWriteMediaApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvWriteMediaApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvWriteMediaApi_GetMetaObjectFunction,
        "beSvWriteMediaApi",
        0x4c, /* instance size */
        beSvWriteMediaApi_GetVTable,
        beSvWriteMediaApi_InitFields,
        0, /* extra callback item */
        g_beSvWriteMediaApi_callbackList /* callback list */
    );
}

void beSvWriteMediaApi_GetMetaObjectFunction(void)
{
    beSvWriteMediaApi_GetMetaObject();
}

static FieldFactory g_beSvWriteMediaApi_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSvWriteMediaApi_fieldTable[] = {
    "_nowGamedata",
    "_saveWork",
};
static igMetaField **g_beSvWriteMediaApi_fieldHandles[] = {
    &g_beSvWriteMediaApi_nowGamedataMetaField,
    &g_beSvWriteMediaApi_saveWorkMetaField,
};
static int g_beSvWriteMediaApi_fieldOffsets[] = {
    64,
    68,
};

void beSvWriteMediaApi_InitFields(void) {
    int base;
    void *nowGamedata;
    void *saveWork;
    void *meta;

    meta = (void *)g_beSvWriteMediaApi_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSvWriteMediaApi_ctorTable, 2);
    nowGamedata = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)nowGamedata)->_metaObject = (int)beSvPlatBaseData_GetOrCreateMetaObject();
    saveWork = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)saveWork)->_metaObject = (int)beSaveMemoryObj_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beSvWriteMediaApi_fieldTable, g_beSvWriteMediaApi_fieldHandles, g_beSvWriteMediaApi_fieldOffsets, base);
}

