igMetaObject *g_beSvPlatBaseData_metaObject;
igMetaField *g_beSvPlatBaseData_connectMaxMetaField;
igMetaField *g_beSvPlatBaseData_slotListMetaField;
igMetaField *g_beSvPlatBaseData_dataSizeMetaField;
igMetaField *g_beSvPlatBaseData_memNeedMetaField;

igMetaObject *beSvPlatBaseData_GetOrCreateMetaObject(void) {
    if (g_beSvPlatBaseData_metaObject == 0) {
        g_beSvPlatBaseData_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beSvPlatBaseData_metaObject;
}

void *beSvPlatBaseData_GetMetaObject(void) {
    igMetaObject *g = g_beSvPlatBaseData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvPlatBaseData_EnsureRegistered();
    }
    return g_beSvPlatBaseData_metaObject;
}

int beSvPlatBaseData_GetVTable(void) {
    beSvPlatBaseData obj;
    int vtable;
    igObject **slotListSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beSvPlatBaseData_vtable[0];
    slotListSlot = (igObject **)&obj._slotList;
    *slotListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSvPlatBaseData_vtable[0];
    igObjectRef_Release(slotListSlot);
    return vtable;
}

void beSvPlatBaseData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvPlatBaseData_Register);
}

static igMetaObjectCallback g_beSvPlatBaseData_callbackList[] = { beSvSlotDataList_EnsureRegistered, 0 };

CallbackArray *beSvPlatBaseData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvPlatBaseData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSvPlatBaseData_GetMetaObjectFunction,
        "beSvPlatBaseData",
        0x18, /* instance size */
        beSvPlatBaseData_GetVTable,
        beSvPlatBaseData_InitFields,
        0, /* extra callback item */
        g_beSvPlatBaseData_callbackList /* callback list */
    );
}

void beSvPlatBaseData_GetMetaObjectFunction(void)
{
    beSvPlatBaseData_GetMetaObject();
}

static FieldFactory g_beSvPlatBaseData_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igUnsignedIntMetaField_Create,
    igUnsignedIntMetaField_Create,
};
static const char *g_beSvPlatBaseData_fieldTable[] = {
    "_connectMax",
    "_slotList",
    "_dataSize",
    "_memNeed",
};
static igMetaField **g_beSvPlatBaseData_fieldHandles[] = {
    &g_beSvPlatBaseData_connectMaxMetaField,
    &g_beSvPlatBaseData_slotListMetaField,
    &g_beSvPlatBaseData_dataSizeMetaField,
    &g_beSvPlatBaseData_memNeedMetaField,
};
static int g_beSvPlatBaseData_fieldOffsets[] = {
    8,
    12,
    16,
    20,
};

void beSvPlatBaseData_InitFields(void) {
    int base;
    void *slotList;
    igMetaObject *meta;

    meta = g_beSvPlatBaseData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSvPlatBaseData_ctorTable, 4);
    slotList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)slotList)->_metaObject = (int)beSvSlotDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)slotList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beSvPlatBaseData_fieldTable, g_beSvPlatBaseData_fieldHandles, g_beSvPlatBaseData_fieldOffsets, base);
}

