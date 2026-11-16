igMetaObject *g_beModelCtrlNode2_metaObject;
igMetaField *g_beModelCtrlNode2_timeMetaField;
igMetaField *g_beModelCtrlNode2_timeScaleMetaField;
igMetaField *g_beModelCtrlNode2_timeBiasMetaField;
igMetaField *g_beModelCtrlNode2_overrideAttrListMetaField;

void beModelCtrlNode2_Create(int allocator) {
    beModelCtrlNode2_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588860, allocator);
}

igMetaObject *beModelCtrlNode2_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlNode2_metaObject == 0) {
        g_beModelCtrlNode2_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beModelCtrlNode2_metaObject;
}

void *beModelCtrlNode2_ResolveMetaObject(void) {
    bool ok;
    if (g_beModelCtrlNode2_metaObject == 0) goto make;
    ok = !!(g_beModelCtrlNode2_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beModelCtrlNode2_EnsureRegistered();
done:;
    return g_beModelCtrlNode2_metaObject;
}

int beModelCtrlNode2_GetVTable(void) {
    ModelCtrlNode2View node;
    return *(int *)((char *)&node + *(int *)((char *)g_objectSystem[0] + 916));
}

void beModelCtrlNode2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlNode2_Register);
}

static igMetaObjectCallback g_beModelCtrlNode2_callbackList[] = { igAttrList_EnsureRegistered, 0 };

void *beModelCtrlNode2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlNode2_metaObject,
        igTransform_Register,
        igTransform_GetPublishedMetaObject,
        beModelCtrlNode2_GetMetaObject,
        "beModelCtrlNode2",
        0x90, /* instance size */
        beModelCtrlNode2_GetVTable,
        beModelCtrlNode2_InitFields,
        beModelCtrlNode2_StaticInitCallback, /* extra callback item */
        g_beModelCtrlNode2_callbackList /* callback list */
    );
}

void beModelCtrlNode2_GetMetaObject(void)
{
    beModelCtrlNode2_ResolveMetaObject();
}

static FieldFactory g_beModelCtrlNode2_ctorTable[] = {
    igLongMetaField_Create,
    igFloatMetaField_Create,
    igLongMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beModelCtrlNode2_fieldTable[] = {
    "_time",
    "_timeScale",
    "_timeBias",
    "_overrideAttrList",
};
static igMetaField **g_beModelCtrlNode2_fieldHandles[] = {
    &g_beModelCtrlNode2_timeMetaField,
    &g_beModelCtrlNode2_timeScaleMetaField,
    &g_beModelCtrlNode2_timeBiasMetaField,
    &g_beModelCtrlNode2_overrideAttrListMetaField,
};
static int g_beModelCtrlNode2_fieldOffsets[] = {
    112,
    120,
    128,
    136,
};

void beModelCtrlNode2_InitFields(void) {
    int base;
    void *overrideAttrList;
    void *meta;

    meta = (void *)g_beModelCtrlNode2_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlNode2_ctorTable, 4);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 1), 1.0f);
    overrideAttrList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)overrideAttrList)->_metaObject = igAttrList_GetOrCreateMetaObject();
    ((igRefMetaField *)overrideAttrList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beModelCtrlNode2_fieldTable, g_beModelCtrlNode2_fieldHandles, g_beModelCtrlNode2_fieldOffsets, base);
}

void beModelCtrlNode2_StaticInitCallback(void)
{
    beModelCtrlNode2_RegisterTraversalFunction();
}

