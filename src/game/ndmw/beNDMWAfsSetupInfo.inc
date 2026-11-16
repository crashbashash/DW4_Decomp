igMetaObject *g_beNDMWAfsSetupInfo_metaObject;
igMetaField *g_beNDMWAfsSetupInfo_insideFilesMetaField;
igMetaField *g_beNDMWAfsSetupInfo_dataListMetaField;

void *beNDMWAfsSetupInfo_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWAfsSetupInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWAfsSetupInfo_EnsureRegistered();
    }
    return g_beNDMWAfsSetupInfo_metaObject;
}

int beNDMWAfsSetupInfo_GetVTable(void) {
    struct W_3ca580 o;
    int r;
    igObject_InitHeader(&o);
    o.vt = g_beNDMWAfsSetupInfo_vtable;
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beNDMWAfsSetupInfo_vtable;
    FUN_003ca610((igSmartPointer<igObject> *)(&o.f[5]), -1);
    igSmartPointer_igAdxAfsFileList_Destruct(&o.f[4], -1);
    igInfo_Destroy(&o, 0);
    return r;
}

igSmartPointer<igObject> *FUN_003ca610(igSmartPointer<igObject> *self,int delete_storage) {
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

void beNDMWAfsSetupInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetupInfo_Register);
}

static igMetaObjectCallback g_beNDMWAfsSetupInfo_callbackList[] = { igAdxAfsFileList_EnsureRegistered, beNDMWAfsSetupDataList_EnsureRegistered, 0 };

void *beNDMWAfsSetupInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWAfsSetupInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beNDMWAfsSetupInfo_GetMetaObject,
        "beNDMWAfsSetupInfo",
        0x1c, /* instance size */
        beNDMWAfsSetupInfo_GetVTable,
        beNDMWAfsSetupInfo_InitFields,
        0, /* extra callback item */
        g_beNDMWAfsSetupInfo_callbackList /* callback list */
    );
}

void beNDMWAfsSetupInfo_GetMetaObject(void)
{
    beNDMWAfsSetupInfo_ResolveMetaObject();
}

static FieldFactory g_beNDMWAfsSetupInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWAfsSetupInfo_fieldTable[] = {
    "_insideFiles",
    "_dataList",
};
static igMetaField **g_beNDMWAfsSetupInfo_fieldHandles[] = {
    &g_beNDMWAfsSetupInfo_insideFilesMetaField,
    &g_beNDMWAfsSetupInfo_dataListMetaField,
};
static int g_beNDMWAfsSetupInfo_fieldOffsets[] = {
    20,
    24,
};

void beNDMWAfsSetupInfo_InitFields(void) {
    int base;
    void *dataList;
    void *insideFiles;
    igMetaObject *meta;

    meta = g_beNDMWAfsSetupInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWAfsSetupInfo_ctorTable, 2);
    insideFiles = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)insideFiles)->_metaObject = igAdxAfsFileList_GetOrCreateMetaObject();
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beNDMWAfsSetupDataList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWAfsSetupInfo_fieldTable, g_beNDMWAfsSetupInfo_fieldHandles, g_beNDMWAfsSetupInfo_fieldOffsets, base);
}

