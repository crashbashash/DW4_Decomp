igMetaObject *g_beDataObjStringList_metaObject;
igMetaField *g_beDataObjStringList_dataMetaField;

beDataObjStringList *beDataObjStringList_Create(int allocator) {
    beDataObjStringList_EnsureRegistered();
    return (beDataObjStringList *)igMetaObject_CreateInstance(*(int *)0x589868, allocator);
}

void *beDataObjStringList_GetMetaObject(void) {
    bool ok;
    if (g_beDataObjStringList_metaObject == 0) goto make;
    ok = !!(g_beDataObjStringList_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beDataObjStringList_EnsureRegistered();
done:;
    return g_beDataObjStringList_metaObject;
}

int beDataObjStringList_GetVTable(void) {
    beDataObjStringList obj;
    int vtable;
    igObject **dataSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beDataObjStringList_vtable[0];
    dataSlot = (igObject **)&obj._data;
    *dataSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beDataObjStringList_vtable[0];
    igObjectRef_Release(dataSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beDataObjStringList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjStringList_Register);
}

static igMetaObjectCallback g_beDataObjStringList_callbackList[] = { igStringRefList_EnsureRegistered, 0 };

void *beDataObjStringList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjStringList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjStringList_GetMetaObjectFunction,
        "beDataObjStringList",
        0x10, /* instance size */
        beDataObjStringList_GetVTable,
        beDataObjStringList_InitFields,
        0, /* extra callback item */
        g_beDataObjStringList_callbackList /* callback list */
    );
}

void beDataObjStringList_GetMetaObjectFunction(void)
{
    beDataObjStringList_GetMetaObject();
}

static FieldFactory g_beDataObjStringList_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beDataObjStringList_fieldTable[] = {
    "_data",
};
static igMetaField **g_beDataObjStringList_fieldHandles[] = {
    &g_beDataObjStringList_dataMetaField,
};
static int g_beDataObjStringList_fieldOffsets[] = {
    12,
};

void beDataObjStringList_InitFields(void) {
    int base;
    void *data;
    void *meta;

    meta = (void *)g_beDataObjStringList_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDataObjStringList_ctorTable, 1);
    data = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)data)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)data)->_construct = 1;
    igMetaObject_NameFields(meta, g_beDataObjStringList_fieldTable, g_beDataObjStringList_fieldHandles, g_beDataObjStringList_fieldOffsets, base);
}

