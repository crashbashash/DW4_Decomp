igMetaObject *g_beModelCtrlNode2_metaObject;
igMetaField *g_beModelCtrlNode2_timeMetaField;
igMetaField *g_beModelCtrlNode2_timeScaleMetaField;
igMetaField *g_beModelCtrlNode2_timeBiasMetaField;
igMetaField *g_beModelCtrlNode2_overrideAttrListMetaField;

void beModelCtrlNode2_Create(int arg0) {
    FUN_0034fe80();
    igMetaObject_CreateInstance(*(int *)0x588860, arg0);
}

igMetaObject *FUN_0034fd40(void) {
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
    FUN_0034fe80();
done:;
    return g_beModelCtrlNode2_metaObject;
}

int beModelCtrlNode2_GetVTable(void) {
    ModelCtrlNode2View node;
    return *(int *)((char *)&node + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_0034fe80(void)
{
    igMetaObject_RunStaticInit(beModelCtrlNode2_Register);
}

static igMetaObjectCallback g_beModelCtrlNode2_callbackList[] = { FUN_0013afe0, 0 };

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
        FUN_00350000, /* extra callback item */
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
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlNode2_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beModelCtrlNode2_ctorTable, 4);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1.0f);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    *(int *)((char *)(temp_s1) + 56) = FUN_0013af00();
    *(char *)((char *)(temp_s1) + 52) = 1;
    igMetaObject_NameFields(temp_s0, g_beModelCtrlNode2_fieldTable, g_beModelCtrlNode2_fieldHandles, g_beModelCtrlNode2_fieldOffsets, temp_s2);
}

void FUN_00350000(void)
{
    beModelCtrlNode2_RegisterTraversalFunction();
}

