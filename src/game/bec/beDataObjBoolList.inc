igMetaObject *g_beDataObjBoolList_metaObject;
igMetaField *g_beDataObjBoolList_dataMetaField;

void beDataObjBoolList_Create(int allocator) {
    beDataObjBoolList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589888, allocator);
}

void *beDataObjBoolList_GetMetaObject(void) {
    unsigned char b;
    if (g_beDataObjBoolList_metaObject != 0) {
        b = (g_beDataObjBoolList_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beDataObjBoolList_EnsureRegistered();
done:
    return g_beDataObjBoolList_metaObject;
}

int beDataObjBoolList_GetVTable(void) {
    beDataObjBoolList obj;
    int vtable;
    igObject **dataSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beDataObjBoolList_vtable[0];
    dataSlot = (igObject **)&obj._data;
    *dataSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beDataObjBoolList_vtable[0];
    igObjectRef_Release(dataSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beDataObjBoolList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjBoolList_Register);
}

static igMetaObjectCallback g_beDataObjBoolList_callbackList[] = { igBoolList_EnsureRegistered, 0 };

void *beDataObjBoolList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjBoolList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjBoolList_GetMetaObjectFunction,
        "beDataObjBoolList",
        0x10, /* instance size */
        beDataObjBoolList_GetVTable,
        beDataObjBoolList_InitFields,
        0, /* extra callback item */
        g_beDataObjBoolList_callbackList /* callback list */
    );
}

void beDataObjBoolList_GetMetaObjectFunction(void)
{
    beDataObjBoolList_GetMetaObject();
}

static FieldFactory g_beDataObjBoolList_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beDataObjBoolList_fieldTable[] = {
    "_data",
};
static igMetaField **g_beDataObjBoolList_fieldHandles[] = {
    &g_beDataObjBoolList_dataMetaField,
};
static int g_beDataObjBoolList_fieldOffsets[] = {
    12,
};

void beDataObjBoolList_InitFields(void) {
    int base;
    void *data;
    void *meta;

    meta = (void *)g_beDataObjBoolList_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDataObjBoolList_ctorTable, 1);
    data = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)data)->_metaObject = igBoolList_GetOrCreateMetaObject();
    ((igRefMetaField *)data)->_construct = 1;
    igMetaObject_NameFields(meta, g_beDataObjBoolList_fieldTable, g_beDataObjBoolList_fieldHandles, g_beDataObjBoolList_fieldOffsets, base);
}

