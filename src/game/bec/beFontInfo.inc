igMetaObject *g_beFontInfo_metaObject;
igMetaField *g_beFontInfo_unicodeListMetaField;

void *beFontInfo_GetMetaObject(void) {
    igMetaObject *g = g_beFontInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beFontInfo_EnsureRegistered();
    }
    return g_beFontInfo_metaObject;
}

int beFontInfo_GetVTable(void) {
    beFontInfo obj;
    int vtable;
    char *unicodeListSlot;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beFontInfo_vtable[0];
    unicodeListSlot = (char *)&obj._unicodeList;
    *(int *)unicodeListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beFontInfo_vtable[0];
    igSmartPointer_beUnicodeObjList_Destruct((igSmartPointer<igObject> *)unicodeListSlot, -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beUnicodeObjList_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beFontInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFontInfo_Register);
}

static igMetaObjectCallback g_beFontInfo_callbackList[] = { Gap::Bec::beUnicodeObjList::arkRegister, 0 };

CallbackArray *beFontInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFontInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beFontInfo_GetMetaObjectFunction,
        "beFontInfo",
        0x20, /* instance size */
        beFontInfo_GetVTable,
        beFontInfo_InitFields,
        0, /* extra callback item */
        g_beFontInfo_callbackList /* callback list */
    );
}

void beFontInfo_GetMetaObjectFunction(void)
{
    beFontInfo_GetMetaObject();
}

static FieldFactory g_beFontInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beFontInfo_fieldTable[] = {
    "_unicodeList",
};
static igMetaField **g_beFontInfo_fieldHandles[] = {
    &g_beFontInfo_unicodeListMetaField,
};
static int g_beFontInfo_fieldOffsets[] = {
    28,
};

void beFontInfo_InitFields(void) {
    int base;
    void *unicodeList;
    igMetaObject *meta;

    meta = g_beFontInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beFontInfo_ctorTable, 1);
    unicodeList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)unicodeList)->_metaObject = (int)Gap::Bec::beUnicodeObjList::getClassTypeLazy();
    igMetaObject_NameFields(meta, g_beFontInfo_fieldTable, g_beFontInfo_fieldHandles, g_beFontInfo_fieldOffsets, base);
}

