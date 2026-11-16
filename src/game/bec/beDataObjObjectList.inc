igMetaObject *g_beDataObjObjectList_metaObject;
igMetaField *g_beDataObjObjectList_dataMetaField;

beDataObjObjectList *beDataObjObjectList_Create(int allocator) {
    beDataObjObjectList_EnsureRegistered();
    return (beDataObjObjectList *)igMetaObject_CreateInstance(*(int *)0x589858, allocator);
}

void *beDataObjObjectList_GetMetaObject(void) {
    igMetaObject *g = g_beDataObjObjectList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDataObjObjectList_EnsureRegistered();
    }
    return g_beDataObjObjectList_metaObject;
}

int beDataObjObjectList_GetVTable(void) {
    beDataObjObjectList obj;
    int vtable;
    igObject **dataSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beDataObjObjectList_vtable[0];
    dataSlot = (igObject **)&obj._data;
    *dataSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beDataObjObjectList_vtable[0];
    igObjectRef_Release(dataSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beDataObjObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjObjectList_Register);
}

static igMetaObjectCallback g_beDataObjObjectList_callbackList[] = { igObjectList_EnsureRegistered, 0 };

void *beDataObjObjectList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjObjectList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjObjectList_GetMetaObjectFunction,
        "beDataObjObjectList",
        0x10, /* instance size */
        beDataObjObjectList_GetVTable,
        beDataObjObjectList_InitFields,
        0, /* extra callback item */
        g_beDataObjObjectList_callbackList /* callback list */
    );
}

void beDataObjObjectList_GetMetaObjectFunction(void)
{
    beDataObjObjectList_GetMetaObject();
}

static FieldFactory g_beDataObjObjectList_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beDataObjObjectList_fieldTable[] = {
    "_data",
};
static igMetaField **g_beDataObjObjectList_fieldHandles[] = {
    &g_beDataObjObjectList_dataMetaField,
};
static int g_beDataObjObjectList_fieldOffsets[] = {
    12,
};

void beDataObjObjectList_InitFields(void) {
    int base;
    void *data;
    void *meta;

    meta = (void *)g_beDataObjObjectList_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDataObjObjectList_ctorTable, 1);
    data = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)data)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)data)->_construct = 1;
    igMetaObject_NameFields(meta, g_beDataObjObjectList_fieldTable, g_beDataObjObjectList_fieldHandles, g_beDataObjObjectList_fieldOffsets, base);
}

