igMetaObject *g_beNDMWStatusInfoRam_metaObject;
igMetaField *g_beNDMWStatusInfoRam_workMetaField;

void *beNDMWStatusInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusInfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusInfoRam_EnsureRegistered();
    }
    return g_beNDMWStatusInfoRam_metaObject;
}

int beNDMWStatusInfoRam_GetVTable(void) {
    beNDMWStatusInfoRam obj;
    int vtable;
    int *dataListRef;
    int *workRef;

    igObject_InitHeader(&obj);
    dataListRef = &obj._dataList;
    *dataListRef = 0;
    *(int **)&obj._vtable = &g_beNDMWStatusInfoRam_vtable[0];
    workRef = &obj._work;
    *workRef = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWStatusInfoRam_vtable[0];
    if (workRef != 0) {
        igRelease((igObject *)*workRef);
    }
    *(int **)&obj._vtable = &g_beBaseInfoRam_vtable[0];
    if (dataListRef != 0) {
        igRelease((igObject *)*dataListRef);
    }
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWStatusInfoWork_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beNDMWStatusInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusInfoRam_Register);
}

static igMetaObjectCallback g_beNDMWStatusInfoRam_callbackList[] = { beNDMWStatusInfoWork_EnsureRegistered, 0 };

CallbackArray *beNDMWStatusInfoRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNDMWStatusInfoRam_GetMetaObjectFunction,
        "beNDMWStatusInfoRam",
        0x30, /* instance size */
        beNDMWStatusInfoRam_GetVTable,
        beNDMWStatusInfoRam_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusInfoRam_callbackList /* callback list */
    );
}

void beNDMWStatusInfoRam_GetMetaObjectFunction(void)
{
    beNDMWStatusInfoRam_GetMetaObject();
}

static FieldFactory g_beNDMWStatusInfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWStatusInfoRam_fieldTable[] = {
    "_work",
};
static igMetaField **g_beNDMWStatusInfoRam_fieldHandles[] = {
    &g_beNDMWStatusInfoRam_workMetaField,
};
static int g_beNDMWStatusInfoRam_fieldOffsets[] = {
    44,
};

void beNDMWStatusInfoRam_InitFields(void) {
    int base;
    void *work;
    igMetaObject *meta;

    meta = g_beNDMWStatusInfoRam_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStatusInfoRam_ctorTable, 1);
    work = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)work)->_metaObject = (int)beNDMWStatusInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWStatusInfoRam_fieldTable, g_beNDMWStatusInfoRam_fieldHandles, g_beNDMWStatusInfoRam_fieldOffsets, base);
}

