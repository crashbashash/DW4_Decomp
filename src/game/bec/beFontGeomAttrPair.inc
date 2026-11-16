igMetaObject *g_beFontGeomAttrPair_metaObject;
igMetaField *g_beFontGeomAttrPair_categoryMetaField;
igMetaField *g_beFontGeomAttrPair_panelMetaField;
igMetaField *g_beFontGeomAttrPair_geomAttrsMetaField;

void beFontGeomAttrPair_Create(int allocator) {
    beFontGeomAttrPair_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5896D8, allocator);
}

void *beFontGeomAttrPair_GetMetaObject(void) {
    bool ok;
    if (g_beFontGeomAttrPair_metaObject == 0) goto make;
    ok = !!(g_beFontGeomAttrPair_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beFontGeomAttrPair_EnsureRegistered();
done:;
    return g_beFontGeomAttrPair_metaObject;
}

int beFontGeomAttrPair_GetVTable(void) {
    beFontGeomAttrPair obj;
    int vtable;
    igObject **geomAttrsSlot;
    char **panelSlot;
    char **categorySlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beFontGeomAttrPair_vtable[0];
    categorySlot = (char **)&obj._category;
    *categorySlot = 0;
    panelSlot = (char **)&obj._panel;
    *panelSlot = 0;
    geomAttrsSlot = (igObject **)&obj._geomAttrs;
    *geomAttrsSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beFontGeomAttrPair_vtable[0];
    igObjectRef_Release(geomAttrsSlot);
    igStringRef_Release(panelSlot);
    igStringRef_Release(categorySlot);
    return vtable;
}

void beFontGeomAttrPair_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFontGeomAttrPair_Register);
}

static igMetaObjectCallback g_beFontGeomAttrPair_callbackList[] = { igGeometryAttrList_EnsureRegistered, 0 };

void *beFontGeomAttrPair_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFontGeomAttrPair_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beFontGeomAttrPair_GetMetaObjectFunction,
        "beFontGeomAttrPair",
        0x14, /* instance size */
        beFontGeomAttrPair_GetVTable,
        beFontGeomAttrPair_InitFields,
        0, /* extra callback item */
        g_beFontGeomAttrPair_callbackList /* callback list */
    );
}

void beFontGeomAttrPair_GetMetaObjectFunction(void)
{
    beFontGeomAttrPair_GetMetaObject();
}

static FieldFactory g_beFontGeomAttrPair_ctorTable[] = {
    igStringMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beFontGeomAttrPair_fieldTable[] = {
    "_category",
    "_panel",
    "_geomAttrs",
};
static igMetaField **g_beFontGeomAttrPair_fieldHandles[] = {
    &g_beFontGeomAttrPair_categoryMetaField,
    &g_beFontGeomAttrPair_panelMetaField,
    &g_beFontGeomAttrPair_geomAttrsMetaField,
};
static int g_beFontGeomAttrPair_fieldOffsets[] = {
    8,
    12,
    16,
};

void beFontGeomAttrPair_InitFields(void) {
    int base;
    void *geomAttrs;
    void *meta;

    meta = (void *)g_beFontGeomAttrPair_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beFontGeomAttrPair_ctorTable, 3);
    geomAttrs = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)geomAttrs)->_metaObject = igGeometryAttrList_GetOrCreateMetaObject();
    ((igRefMetaField *)geomAttrs)->_construct = 1;
    igMetaObject_NameFields(meta, g_beFontGeomAttrPair_fieldTable, g_beFontGeomAttrPair_fieldHandles, g_beFontGeomAttrPair_fieldOffsets, base);
}

