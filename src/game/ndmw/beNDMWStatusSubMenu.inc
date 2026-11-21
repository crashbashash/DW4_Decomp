igMetaObject *g_beNDMWStatusSubMenu_metaObject;
igMetaField *g_beNDMWStatusSubMenu_selectDeviceMetaField;
igMetaField *g_beNDMWStatusSubMenu_deviceFolderListMetaField;
igMetaField *g_beNDMWStatusSubMenu_receiptMetaField;
igMetaField *g_beNDMWStatusSubMenu_playerNoListMetaField;
igMetaField *g_beNDMWStatusSubMenu_playerDeviceCntMetaField;

beNDMWStatusSubMenu *beNDMWStatusSubMenu_Create(int allocator) {
    beNDMWStatusSubMenu_EnsureRegistered();
    return (beNDMWStatusSubMenu *)igMetaObject_CreateInstance(g_beNDMWStatusSubMenu_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWStatusSubMenu_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusSubMenu_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusSubMenu_EnsureRegistered();
    }
    return g_beNDMWStatusSubMenu_metaObject;
}

int beNDMWStatusSubMenu_GetVTable(void) {
    beNDMWStatusSubMenu obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWStatusSubMenu_vtable[0];
    obj._deviceFolderList = 0;
    obj._playerNoList = 0;
    obj._playerDeviceCnt = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWStatusSubMenu_vtable[0];
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._playerDeviceCnt, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._playerNoList, -1);
    beNDMWStatusSubMenu_igSmartPointer_beNDMWWindow_Destruct((igSmartPointer<igObject> *)&obj._deviceFolderList, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
}

igSmartPointer<igObject> *beNDMWStatusSubMenu_igSmartPointer_beNDMWWindow_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beNDMWStatusSubMenu_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSubMenu_Register);
}

static igMetaObjectCallback g_beNDMWStatusSubMenu_callbackList[] = { beNDMWWindowCtrl_EnsureRegistered, Gap::Core::igIntList::arkRegister, 0 };

CallbackArray *beNDMWStatusSubMenu_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusSubMenu_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusSubMenu_GetMetaObjectFunction,
        "beNDMWStatusSubMenu",
        0x68, /* instance size */
        beNDMWStatusSubMenu_GetVTable,
        beNDMWStatusSubMenu_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusSubMenu_callbackList /* callback list */
    );
}

void beNDMWStatusSubMenu_GetMetaObjectFunction(void)
{
    beNDMWStatusSubMenu_GetMetaObject();
}

static FieldFactory g_beNDMWStatusSubMenu_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWStatusSubMenu_fieldTable[] = {
    "_selectDevice",
    "_deviceFolderList",
    "_receipt",
    "_playerNoList",
    "_playerDeviceCnt",
};
static igMetaField **g_beNDMWStatusSubMenu_fieldHandles[] = {
    &g_beNDMWStatusSubMenu_selectDeviceMetaField,
    &g_beNDMWStatusSubMenu_deviceFolderListMetaField,
    &g_beNDMWStatusSubMenu_receiptMetaField,
    &g_beNDMWStatusSubMenu_playerNoListMetaField,
    &g_beNDMWStatusSubMenu_playerDeviceCntMetaField,
};
static int g_beNDMWStatusSubMenu_fieldOffsets[] = {
    84,
    88,
    92,
    96,
    100,
};

void beNDMWStatusSubMenu_InitFields(void) {
    int base;
    void *deviceFolderList;
    void *playerNoList;
    void *playerDeviceCnt;
    igMetaObject *meta;

    meta = g_beNDMWStatusSubMenu_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStatusSubMenu_ctorTable, 5);
    deviceFolderList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)deviceFolderList)->_metaObject = (int)beNDMWWindowCtrl_GetOrCreateMetaObject();
    playerNoList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)playerNoList)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igRefMetaField *)playerNoList)->_construct = 1;
    playerDeviceCnt = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)playerDeviceCnt)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igRefMetaField *)playerDeviceCnt)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWStatusSubMenu_fieldTable, g_beNDMWStatusSubMenu_fieldHandles, g_beNDMWStatusSubMenu_fieldOffsets, base);
}

