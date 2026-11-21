igMetaObject *g_beDataObjIntList_metaObject;
igMetaField *g_beDataObjIntList_dataMetaField;

beDataObjIntList *beDataObjIntList_Create(int allocator) {
    beDataObjIntList_EnsureRegistered();
    return (beDataObjIntList *)igMetaObject_CreateInstance(g_beDataObjIntList_metaObject, (igMemoryPoolView *)allocator);
}

void *beDataObjIntList_GetMetaObject(void) {
    igMetaObject *g = g_beDataObjIntList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDataObjIntList_EnsureRegistered();
    }
    return g_beDataObjIntList_metaObject;
}

int beDataObjIntList_GetVTable(void) {
    beDataObjIntList obj;
    int vtable;
    igObject **dataSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beDataObjIntList_vtable[0];
    dataSlot = (igObject **)&obj._data;
    *dataSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beDataObjIntList_vtable[0];
    igObjectRef_Release(dataSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beDataObjIntList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjIntList_Register);
}

static igMetaObjectCallback g_beDataObjIntList_callbackList[] = { Gap::Core::igIntList::arkRegister, 0 };

CallbackArray *beDataObjIntList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjIntList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjIntList_GetMetaObjectFunction,
        "beDataObjIntList",
        0x10, /* instance size */
        beDataObjIntList_GetVTable,
        beDataObjIntList_InitFields,
        0, /* extra callback item */
        g_beDataObjIntList_callbackList /* callback list */
    );
}

void beDataObjIntList_GetMetaObjectFunction(void)
{
    beDataObjIntList_GetMetaObject();
}

static FieldFactory g_beDataObjIntList_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beDataObjIntList_fieldTable[] = {
    "_data",
};
static igMetaField **g_beDataObjIntList_fieldHandles[] = {
    &g_beDataObjIntList_dataMetaField,
};
static int g_beDataObjIntList_fieldOffsets[] = {
    12,
};

void beDataObjIntList_InitFields(void) {
    int base;
    void *data;
    igMetaObject *meta;

    meta = g_beDataObjIntList_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDataObjIntList_ctorTable, 1);
    data = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)data)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igRefMetaField *)data)->_construct = 1;
    igMetaObject_NameFields(meta, g_beDataObjIntList_fieldTable, g_beDataObjIntList_fieldHandles, g_beDataObjIntList_fieldOffsets, base);
}

