igMetaObject *g_beModelCtrlInfoHitBody_metaObject;
igMetaField *g_beModelCtrlInfoHitBody_isFirstMetaField;
igMetaField *g_beModelCtrlInfoHitBody_calcTimeMetaField;
igMetaField *g_beModelCtrlInfoHitBody_countMetaField;
igMetaField *g_beModelCtrlInfoHitBody_orgAABoxListMetaField;
igMetaField *g_beModelCtrlInfoHitBody_AABoxMinListMetaField;
igMetaField *g_beModelCtrlInfoHitBody_AABoxMaxListMetaField;
igMetaField *g_beModelCtrlInfoHitBody_AABoxListMetaField;

beModelCtrlInfoHitBody *beModelCtrlInfoHitBody_Create(int allocator) {
    beModelCtrlInfoHitBody_EnsureRegistered();
    return (beModelCtrlInfoHitBody *)igMetaObject_CreateInstance(g_beModelCtrlInfoHitBody_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beModelCtrlInfoHitBody_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlInfoHitBody_metaObject == 0) {
        g_beModelCtrlInfoHitBody_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beModelCtrlInfoHitBody_metaObject;
}

void *beModelCtrlInfoHitBody_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlInfoHitBody_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlInfoHitBody_EnsureRegistered();
    }
    return g_beModelCtrlInfoHitBody_metaObject;
}

int beModelCtrlInfoHitBody_GetVTable(void) {
    beModelCtrlInfoHitBody obj;
    int vtable;
    igObject **AABoxListSlot;
    igObject **AABoxMaxListSlot;
    igObject **AABoxMinListSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beModelCtrlInfoHitBody_vtable[0];
    AABoxMinListSlot = (igObject **)&obj._AABoxMinList;
    *AABoxMinListSlot = 0;
    AABoxMaxListSlot = (igObject **)&obj._AABoxMaxList;
    *AABoxMaxListSlot = 0;
    AABoxListSlot = (igObject **)&obj._AABoxList;
    *AABoxListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beModelCtrlInfoHitBody_vtable[0];
    igObjectRef_Release(AABoxListSlot);
    igObjectRef_Release(AABoxMaxListSlot);
    igObjectRef_Release(AABoxMinListSlot);
    return vtable;
}

void beModelCtrlInfoHitBody_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoHitBody_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoHitBody_callbackList[] = { igAABoxList_EnsureRegistered, igVec3fList_EnsureRegistered, 0 };

CallbackArray *beModelCtrlInfoHitBody_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoHitBody_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlInfoHitBody_GetMetaObjectFunction,
        "beModelCtrlInfoHitBody",
        0x30, /* instance size */
        beModelCtrlInfoHitBody_GetVTable,
        beModelCtrlInfoHitBody_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoHitBody_callbackList /* callback list */
    );
}

void beModelCtrlInfoHitBody_GetMetaObjectFunction(void)
{
    beModelCtrlInfoHitBody_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoHitBody_ctorTable[] = {
    igBoolMetaField_Create,
    igLongMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beModelCtrlInfoHitBody_fieldTable[] = {
    "_isFirst",
    "_calcTime",
    "_count",
    "_orgAABoxList",
    "_AABoxMinList",
    "_AABoxMaxList",
    "_AABoxList",
};
static igMetaField **g_beModelCtrlInfoHitBody_fieldHandles[] = {
    &g_beModelCtrlInfoHitBody_isFirstMetaField,
    &g_beModelCtrlInfoHitBody_calcTimeMetaField,
    &g_beModelCtrlInfoHitBody_countMetaField,
    &g_beModelCtrlInfoHitBody_orgAABoxListMetaField,
    &g_beModelCtrlInfoHitBody_AABoxMinListMetaField,
    &g_beModelCtrlInfoHitBody_AABoxMaxListMetaField,
    &g_beModelCtrlInfoHitBody_AABoxListMetaField,
};
static int g_beModelCtrlInfoHitBody_fieldOffsets[] = {
    8,
    16,
    24,
    28,
    32,
    36,
    40,
};

void beModelCtrlInfoHitBody_InitFields(void) {
    int base;
    void *orgAABoxList;
    void *AABoxMinList;
    void *AABoxMaxList;
    void *AABoxList;
    igMetaObject *meta;

    meta = g_beModelCtrlInfoHitBody_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlInfoHitBody_ctorTable, 7);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base)))->setDefault(1);
    orgAABoxList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)orgAABoxList)->_metaObject = (int)igAABoxList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)orgAABoxList)->_refCounted = 0;
    AABoxMinList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)AABoxMinList)->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    ((igRefMetaField *)AABoxMinList)->_construct = 1;
    AABoxMaxList = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)AABoxMaxList)->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    ((igRefMetaField *)AABoxMaxList)->_construct = 1;
    AABoxList = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)AABoxList)->_metaObject = (int)igAABoxList_GetOrCreateMetaObject();
    ((igRefMetaField *)AABoxList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beModelCtrlInfoHitBody_fieldTable, g_beModelCtrlInfoHitBody_fieldHandles, g_beModelCtrlInfoHitBody_fieldOffsets, base);
}

