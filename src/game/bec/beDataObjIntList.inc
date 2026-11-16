igMetaObject *g_beDataObjIntList_metaObject;
igMetaField *g_beDataObjIntList_dataMetaField;

void beDataObjIntList_Create(int allocator) {
    beDataObjIntList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5898A8, allocator);
}

void *beDataObjIntList_GetMetaObject(void) {
    igMetaObject *g = g_beDataObjIntList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDataObjIntList_EnsureRegistered();
    }
    return g_beDataObjIntList_metaObject;
}

int beDataObjIntList_GetVTable(void) {
    Obj_3652d0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m8 = 0;
    obj.vt = &g_beDataObjIntList_vtable[0];
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beDataObjIntList_vtable[0];
    obj.rel12();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel8();
    return r;
}

void beDataObjIntList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjIntList_Register);
}

static igMetaObjectCallback g_beDataObjIntList_callbackList[] = { igIntList_EnsureRegistered, 0 };

void *beDataObjIntList_Register(void) {
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
    void *meta;

    meta = (void *)g_beDataObjIntList_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDataObjIntList_ctorTable, 1);
    data = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)data)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)data)->_construct = 1;
    igMetaObject_NameFields(meta, g_beDataObjIntList_fieldTable, g_beDataObjIntList_fieldHandles, g_beDataObjIntList_fieldOffsets, base);
}

