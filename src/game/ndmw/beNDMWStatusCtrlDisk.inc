igMetaObject *g_beNDMWStatusCtrlDisk_metaObject;
igMetaField *g_beNDMWStatusCtrlDisk_cursorMetaField;
igMetaField *g_beNDMWStatusCtrlDisk_playerNoListMetaField;
igMetaField *g_beNDMWStatusCtrlDisk_receiptMetaField;
igMetaField *g_beNDMWStatusCtrlDisk_diskListMetaField;
igMetaField *g_beNDMWStatusCtrlDisk_sendDiskMetaField;
igMetaField *g_beNDMWStatusCtrlDisk_sendMaxMetaField;

void beNDMWStatusCtrlDisk_Create(int allocator) {
    beNDMWStatusCtrlDisk_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusCtrlDisk_metaObject, allocator);
}

igMetaObject *beNDMWStatusCtrlDisk_GetMetaObject(void)
{
    igMetaObject *g = g_beNDMWStatusCtrlDisk_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWStatusCtrlDisk_EnsureRegistered();
    return g_beNDMWStatusCtrlDisk_metaObject;
}

int beNDMWStatusCtrlDisk_GetVTable(void) {
    struct Obj_3b9ae0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w[12] = 0;
    obj.w[13] = 0;
    obj.w[14] = 0;
    obj.w[15] = 0;
    obj.w[16] = 0;
    obj.w[17] = 0;
    obj.w[18] = 0;
    obj.vt = &g_beNDMWStatusCtrlDisk_vtable[0];
    obj.w[21] = 0;
    obj.w[23] = 0;
    obj.w[24] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWStatusCtrlDisk_vtable[0];
    FUN_003b9ba0((igSmartPointer<igObject> *)(&obj.w[24]), -1);
    igSmartPointer_beNDMWItemBaseList_Destruct((igSmartPointer<igObject> *)(&obj.w[23]), -1);
    igSmartPointer_igIntList_Destruct(&obj.w[21], -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)((int *)&obj), (long long)0);
    return t;
}

igSmartPointer<igObject> *FUN_003b9ba0(igSmartPointer<igObject> *self,int delete_storage) {
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

void beNDMWStatusCtrlDisk_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlDisk_Register);
}

static igMetaObjectCallback g_beNDMWStatusCtrlDisk_callbackList[] = { igIntList_EnsureRegistered, beNDMWItemBaseList_EnsureRegistered, beNDMWItemDisk_EnsureRegistered, 0 };

void *beNDMWStatusCtrlDisk_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusCtrlDisk_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlDisk_GetMetaObjectFunction,
        "beNDMWStatusCtrlDisk",
        0x6c, /* instance size */
        beNDMWStatusCtrlDisk_GetVTable,
        beNDMWStatusCtrlDisk_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlDisk_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlDisk_GetMetaObjectFunction(void)
{
    beNDMWStatusCtrlDisk_GetMetaObject();
}

static FieldFactory g_beNDMWStatusCtrlDisk_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWStatusCtrlDisk_fieldTable[] = {
    "_cursor",
    "_playerNoList",
    "_receipt",
    "_diskList",
    "_sendDisk",
    "_sendMax",
};
static igMetaField **g_beNDMWStatusCtrlDisk_fieldHandles[] = {
    &g_beNDMWStatusCtrlDisk_cursorMetaField,
    &g_beNDMWStatusCtrlDisk_playerNoListMetaField,
    &g_beNDMWStatusCtrlDisk_receiptMetaField,
    &g_beNDMWStatusCtrlDisk_diskListMetaField,
    &g_beNDMWStatusCtrlDisk_sendDiskMetaField,
    &g_beNDMWStatusCtrlDisk_sendMaxMetaField,
};
static int g_beNDMWStatusCtrlDisk_fieldOffsets[] = {
    84,
    88,
    92,
    96,
    100,
    104,
};

void beNDMWStatusCtrlDisk_InitFields(void) {
    int base;
    void *playerNoList;
    void *diskList;
    void *sendDisk;
    igMetaObject *meta;

    meta = g_beNDMWStatusCtrlDisk_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStatusCtrlDisk_ctorTable, 6);
    playerNoList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)playerNoList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)playerNoList)->_construct = 1;
    diskList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)diskList)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    ((igRefMetaField *)diskList)->_construct = 1;
    sendDisk = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)sendDisk)->_metaObject = (int)beNDMWItemDisk_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWStatusCtrlDisk_fieldTable, g_beNDMWStatusCtrlDisk_fieldHandles, g_beNDMWStatusCtrlDisk_fieldOffsets, base);
}

