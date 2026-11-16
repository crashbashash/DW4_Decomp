igMetaObject *g_beDataObjString_metaObject;
igMetaField *g_beDataObjString_dataMetaField;

beDataObjString *beDataObjString_Create(int allocator) {
    beDataObjString_EnsureRegistered();
    return (beDataObjString *)igMetaObject_CreateInstance(*(int *)0x589878, allocator);
}

void *beDataObjString_GetMetaObject(void) {
    igMetaObject *g = g_beDataObjString_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDataObjString_EnsureRegistered();
    }
    return g_beDataObjString_metaObject;
}

int beDataObjString_GetVTable(void) {
    beDataObjString obj;
    int vtable;
    char **dataSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)(&g_beDataObjString_vtable[0]);
    dataSlot = (char **)&obj._data;
    *dataSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)(&g_beDataObjString_vtable[0]);
    igStringRef_Release(dataSlot);
    obj._vtable = (int)(&g_igNamedObject_vtable[0]);
    igStringRef_Release(nameSlot);
    return vtable;
}

void beDataObjString_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjString_Register);
}

void *beDataObjString_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjString_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjString_GetMetaObjectFunction,
        "beDataObjString",
        0x10, /* instance size */
        beDataObjString_GetVTable,
        beDataObjString_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beDataObjString_GetMetaObjectFunction(void)
{
    beDataObjString_GetMetaObject();
}

static FieldFactory g_beDataObjString_ctorTable[] = {
    igStringMetaField_Create,
};
static const char *g_beDataObjString_fieldTable[] = {
    "_data",
};
static igMetaField **g_beDataObjString_fieldHandles[] = {
    &g_beDataObjString_dataMetaField,
};
static int g_beDataObjString_fieldOffsets[] = {
    12,
};

void beDataObjString_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beDataObjString_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDataObjString_ctorTable, 1);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(meta, base)), 0);
    igMetaObject_NameFields(meta, g_beDataObjString_fieldTable, g_beDataObjString_fieldHandles, g_beDataObjString_fieldOffsets, base);
}

