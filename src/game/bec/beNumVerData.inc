igMetaObject *g_beNumVerData_metaObject;
igMetaField *g_beNumVerData_dispMetaField;
igMetaField *g_beNumVerData_verDataListMetaField;

void *beNumVerData_GetMetaObject(void) {
    igMetaObject *g = g_beNumVerData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNumVerData_EnsureRegistered();
    }
    return g_beNumVerData_metaObject;
}

int beNumVerData_GetVTable(void) {
    beNumVerData obj;
    int vtable;
    igObject **verDataListSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beNumVerData_vtable[0];
    verDataListSlot = (igObject **)&obj._verDataList;
    *verDataListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beNumVerData_vtable[0];
    igObjectRef_Release(verDataListSlot);
    return vtable;
}

void beNumVerData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNumVerData_Register);
}

static igMetaObjectCallback g_beNumVerData_callbackList[] = { beNumVerInsideDataList_EnsureRegistered, 0 };

CallbackArray *beNumVerData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumVerData_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beNumVerData_GetMetaObjectFunction,
        "beNumVerData",
        0x10, /* instance size */
        beNumVerData_GetVTable,
        beNumVerData_InitFields,
        0, /* extra callback item */
        g_beNumVerData_callbackList /* callback list */
    );
}

void beNumVerData_GetMetaObjectFunction(void)
{
    beNumVerData_GetMetaObject();
}

static FieldFactory g_beNumVerData_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNumVerData_fieldTable[] = {
    "_disp",
    "_verDataList",
};
static igMetaField **g_beNumVerData_fieldHandles[] = {
    &g_beNumVerData_dispMetaField,
    &g_beNumVerData_verDataListMetaField,
};
static int g_beNumVerData_fieldOffsets[] = {
    8,
    12,
};

void beNumVerData_InitFields(void) {
    int base;
    void *verDataList;
    igMetaObject *meta;

    meta = g_beNumVerData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNumVerData_ctorTable, 2);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt(meta, base)))->setDefault(-1);
    verDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)verDataList)->_metaObject = (int)beNumVerInsideDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)verDataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNumVerData_fieldTable, g_beNumVerData_fieldHandles, g_beNumVerData_fieldOffsets, base);
}

