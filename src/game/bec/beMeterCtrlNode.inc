igMetaObject *g_beMeterCtrlNode_metaObject;
igMetaField *g_beMeterCtrlNode_isMeterMetaField;
igMetaField *g_beMeterCtrlNode_timeListMetaField;
igMetaField *g_beMeterCtrlNode_numberOffsetMetaField;

igMetaObject *beMeterCtrlNode_GetOrCreateMetaObject(void) {
    if (g_beMeterCtrlNode_metaObject == 0) {
        g_beMeterCtrlNode_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beMeterCtrlNode_metaObject;
}

igMetaObject *beMeterCtrlNode_ResolveMetaObject(void) {
    igMetaObject *g = g_beMeterCtrlNode_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMeterCtrlNode_EnsureRegistered();
    }
    return g_beMeterCtrlNode_metaObject;
}

int beMeterCtrlNode_GetVTable(void) {
    beMeterCtrlNode obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._bound = 0;
    obj._parentList = 0;
    obj._childList = 0;
    obj._vtable = (int)&g_beMeterCtrlNode_vtable[0];
    obj._timeList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beMeterCtrlNode_vtable[0];
    igSmartPointer_igLongList_Destruct((igSmartPointer<igObject> *)&obj._timeList, -1);
    igGroup_Destroy((igGroup *)&obj, 0);
    return vtable;
}

void beMeterCtrlNode_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMeterCtrlNode_Register);
}

static igMetaObjectCallback g_beMeterCtrlNode_callbackList[] = { igLongList_EnsureRegistered, 0 };

CallbackArray *beMeterCtrlNode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMeterCtrlNode_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beMeterCtrlNode_GetMetaObject,
        "beMeterCtrlNode",
        0x34, /* instance size */
        beMeterCtrlNode_GetVTable,
        beMeterCtrlNode_InitFields,
        beMeterCtrlNode_StaticInitCallback, /* extra callback item */
        g_beMeterCtrlNode_callbackList /* callback list */
    );
}

void beMeterCtrlNode_GetMetaObject(void)
{
    beMeterCtrlNode_ResolveMetaObject();
}

static FieldFactory g_beMeterCtrlNode_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
};
static const char *g_beMeterCtrlNode_fieldTable[] = {
    "_isMeter",
    "_timeList",
    "_numberOffset",
};
static igMetaField **g_beMeterCtrlNode_fieldHandles[] = {
    &g_beMeterCtrlNode_isMeterMetaField,
    &g_beMeterCtrlNode_timeListMetaField,
    &g_beMeterCtrlNode_numberOffsetMetaField,
};
static int g_beMeterCtrlNode_fieldOffsets[] = {
    32,
    36,
    40,
};

void beMeterCtrlNode_InitFields(void) {
    int base;
    void *timeList;
    igMetaObject *meta;

    meta = g_beMeterCtrlNode_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMeterCtrlNode_ctorTable, 3);
    timeList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)timeList)->_metaObject = (int)igLongList_GetOrCreateMetaObject();
    ((igRefMetaField *)timeList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beMeterCtrlNode_fieldTable, g_beMeterCtrlNode_fieldHandles, g_beMeterCtrlNode_fieldOffsets, base);
}

void beMeterCtrlNode_StaticInitCallback(void)
{
    beMeterCtrlNode_RegisterTraversalFunction();
}

