igMetaObject *g_beGeneraterPlayerData_metaObject;
igMetaField *g_beGeneraterPlayerData_geneCountMetaField;
igMetaField *g_beGeneraterPlayerData_geneMaxCountMetaField;
igMetaField *g_beGeneraterPlayerData_itemDataListMetaField;
igMetaField *g_beGeneraterPlayerData_itemLastDataListMetaField;

void *beGeneraterPlayerData_GetMetaObject(void) {
    bool ok;
    if (g_beGeneraterPlayerData_metaObject == 0) goto make;
    ok = !!(g_beGeneraterPlayerData_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beGeneraterPlayerData_EnsureRegistered();
done:;
    return g_beGeneraterPlayerData_metaObject;
}

int beGeneraterPlayerData_GetVTable(void) {
    Obj_360100 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &g_beGeneraterPlayerData_vtable[0];
    obj.r3 = 0;
    obj.r4 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beGeneraterPlayerData_vtable[0];
    obj.rel4();
    obj.rel3();
    return r;
}

void beGeneraterPlayerData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterPlayerData_Register);
}

static igMetaObjectCallback g_beGeneraterPlayerData_callbackList[] = { beGeneraterItemDataList_EnsureRegistered, 0 };

void *beGeneraterPlayerData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterPlayerData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beGeneraterPlayerData_GetMetaObjectFunction,
        "beGeneraterPlayerData",
        0x18, /* instance size */
        beGeneraterPlayerData_GetVTable,
        beGeneraterPlayerData_InitFields,
        0, /* extra callback item */
        g_beGeneraterPlayerData_callbackList /* callback list */
    );
}

void beGeneraterPlayerData_GetMetaObjectFunction(void)
{
    beGeneraterPlayerData_GetMetaObject();
}

static FieldFactory g_beGeneraterPlayerData_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beGeneraterPlayerData_fieldTable[] = {
    "_geneCount",
    "_geneMaxCount",
    "_itemDataList",
    "_itemLastDataList",
};
static igMetaField **g_beGeneraterPlayerData_fieldHandles[] = {
    &g_beGeneraterPlayerData_geneCountMetaField,
    &g_beGeneraterPlayerData_geneMaxCountMetaField,
    &g_beGeneraterPlayerData_itemDataListMetaField,
    &g_beGeneraterPlayerData_itemLastDataListMetaField,
};
static int g_beGeneraterPlayerData_fieldOffsets[] = {
    8,
    12,
    16,
    20,
};

void beGeneraterPlayerData_InitFields(void) {
    int base;
    void *itemLastDataList;
    void *itemDataList;
    void *meta;

    meta = (void *)g_beGeneraterPlayerData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beGeneraterPlayerData_ctorTable, 4);
    itemDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)itemDataList)->_metaObject = (int)beGeneraterItemDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)itemDataList)->_construct = 1;
    itemLastDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)itemLastDataList)->_metaObject = (int)beGeneraterItemDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)itemLastDataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beGeneraterPlayerData_fieldTable, g_beGeneraterPlayerData_fieldHandles, g_beGeneraterPlayerData_fieldOffsets, base);
}

