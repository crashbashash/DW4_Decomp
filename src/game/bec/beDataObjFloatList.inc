igMetaObject *g_beDataObjFloatList_metaObject;
igMetaField *g_beDataObjFloatList_dataMetaField;

void beDataObjFloatList_Create(int allocator) {
    beDataObjFloatList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589848, allocator);
}

void *beDataObjFloatList_GetMetaObject(void) {
    igMetaObject *g = g_beDataObjFloatList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDataObjFloatList_EnsureRegistered();
    }
    return g_beDataObjFloatList_metaObject;
}

int beDataObjFloatList_GetVTable(void) {
    beDataObjFloatList obj;
    int vtable;
    igObject **dataSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beDataObjFloatList_vtable[0];
    dataSlot = (igObject **)&obj._data;
    *dataSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beDataObjFloatList_vtable[0];
    igObjectRef_Release(dataSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beDataObjFloatList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjFloatList_Register);
}

static igMetaObjectCallback g_beDataObjFloatList_callbackList[] = { igFloatList_EnsureRegistered, 0 };

void *beDataObjFloatList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjFloatList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjFloatList_GetMetaObjectFunction,
        "beDataObjFloatList",
        0x10, /* instance size */
        beDataObjFloatList_GetVTable,
        beDataObjFloatList_InitFields,
        0, /* extra callback item */
        g_beDataObjFloatList_callbackList /* callback list */
    );
}

void beDataObjFloatList_GetMetaObjectFunction(void)
{
    beDataObjFloatList_GetMetaObject();
}

static FieldFactory g_beDataObjFloatList_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beDataObjFloatList_fieldTable[] = {
    "_data",
};
static igMetaField **g_beDataObjFloatList_fieldHandles[] = {
    &g_beDataObjFloatList_dataMetaField,
};
static int g_beDataObjFloatList_fieldOffsets[] = {
    12,
};

void beDataObjFloatList_InitFields(void) {
    int base;
    void *data;
    void *meta;

    meta = (void *)g_beDataObjFloatList_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDataObjFloatList_ctorTable, 1);
    data = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)data)->_metaObject = igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)data)->_construct = 1;
    igMetaObject_NameFields(meta, g_beDataObjFloatList_fieldTable, g_beDataObjFloatList_fieldHandles, g_beDataObjFloatList_fieldOffsets, base);
}

