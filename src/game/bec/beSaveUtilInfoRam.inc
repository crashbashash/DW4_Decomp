igMetaObject *g_beSaveUtilInfoRam_metaObject;
igMetaField *g_beSaveUtilInfoRam_isRdyMetaField;
igMetaField *g_beSaveUtilInfoRam_deliverMetaField;

igMetaObject *beSaveUtilInfoRam_GetMetaObject(void) {
    if (g_beSaveUtilInfoRam_metaObject == 0 || !isValid(g_beSaveUtilInfoRam_metaObject)) beSaveUtilInfoRam_EnsureRegistered();
    return g_beSaveUtilInfoRam_metaObject;
}

int beSaveUtilInfoRam_GetVTable(void) {
    beSaveUtilInfoRam obj;
    int vtable;
    igObject **dataListSlot;
    igObject **deliverSlot;

    igObject_InitHeader(&obj);
    dataListSlot = (igObject **)&obj._dataList;
    *dataListSlot = 0;
    obj._vtable = (int)&g_beSaveUtilInfoRam_vtable[0];
    deliverSlot = (igObject **)&obj._deliver;
    *deliverSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSaveUtilInfoRam_vtable[0];
    igObjectRef_Release(deliverSlot);
    obj._vtable = (int)&g_beBaseInfoRam_vtable[0];
    igObjectRef_Release(dataListSlot);
    return vtable;
}

void beSaveUtilInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSaveUtilInfoRam_Register);
}

static igMetaObjectCallback g_beSaveUtilInfoRam_callbackList[] = { Gap::Bec::beSvDeliver::arkRegister, 0 };

CallbackArray *beSaveUtilInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSaveUtilInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beSaveUtilInfoRam_GetMetaObjectFunction,
        "beSaveUtilInfoRam",
        0x34, /* instance size */
        beSaveUtilInfoRam_GetVTable,
        beSaveUtilInfoRam_InitFields,
        0, /* extra callback item */
        g_beSaveUtilInfoRam_callbackList /* callback list */
    );
}

void beSaveUtilInfoRam_GetMetaObjectFunction(void)
{
    beSaveUtilInfoRam_GetMetaObject();
}

static FieldFactory g_beSaveUtilInfoRam_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSaveUtilInfoRam_fieldTable[] = {
    "_isRdy",
    "_deliver",
};
static igMetaField **g_beSaveUtilInfoRam_fieldHandles[] = {
    &g_beSaveUtilInfoRam_isRdyMetaField,
    &g_beSaveUtilInfoRam_deliverMetaField,
};
static int g_beSaveUtilInfoRam_fieldOffsets[] = {
    44,
    48,
};

void beSaveUtilInfoRam_InitFields(void) {
    int base;
    void *deliver;
    igMetaObject *meta;

    meta = g_beSaveUtilInfoRam_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSaveUtilInfoRam_ctorTable, 2);
    deliver = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)deliver)->_metaObject = (int)Gap::Bec::beSvDeliver::getClassTypeLazy();
    ((igRefMetaField *)deliver)->_construct = 1;
    igMetaObject_NameFields(meta, g_beSaveUtilInfoRam_fieldTable, g_beSaveUtilInfoRam_fieldHandles, g_beSaveUtilInfoRam_fieldOffsets, base);
}

