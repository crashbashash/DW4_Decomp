igMetaObject *g_igIterateGraph_metaObject;
igMetaField *g_igIterateGraph_currentPathMetaField;
igMetaField *g_igIterateGraph_currentIndicesMetaField;
igMetaField *g_igIterateGraph_actorSkinIterationStateMetaField;

igObject *igIterateGraph_Create(igMemoryPoolView *pool) {
    igIterateGraph_EnsureRegistered();
    return igMetaObject_CreateInstance(g_igIterateGraph_metaObject, pool);
}

igMetaObject *igIterateGraph_GetOrCreateMetaObject(void) {
    if (g_igIterateGraph_metaObject == 0) {
        g_igIterateGraph_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igIterateGraph_metaObject;
}

igMetaObject *igIterateGraph_GetMetaObject(void)
{
    igMetaObject *g = g_igIterateGraph_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igIterateGraph_EnsureRegistered();
    return g_igIterateGraph_metaObject;
}

extern "C" int igIterateGraph_GetVTable(void) {
    Obj_6 obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igIterateGraph_vtable[0];
    obj.m12 = 0;
    obj.m16 = 0;
    r = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igIterateGraph_vtable[0];
    obj.rel16();
    obj.rel12();
    return r;
}

void igIterateGraph_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igIterateGraph_Register);
}

static igMetaObjectCallback g_igIterateGraph_callbackList[] = { Gap::Sg::igNonRefCountedNodeList::arkRegister, Gap::Core::igIntList::arkRegister, 0 };

CallbackArray *igIterateGraph_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igIterateGraph_metaObject,
        (igMetaObjectRegisterFunction)igIterator_Register,
        (igMetaObjectGetFunction)igIterator_GetPublishedMetaObject,
        igIterateGraph_GetMetaObjectFunction,
        "igIterateGraph",
        0x14, /* instance size */
        igIterateGraph_GetVTable,
        &igIterateGraph_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igIterateGraph_callbackList /* callback list */
    );
}

void igIterateGraph_GetMetaObjectFunction(void) {
    igIterateGraph_GetMetaObject();
}

static FieldFactory g_igIterateGraph_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igIterateGraph_fieldTable[] = {
    "_currentPath",
    "_currentIndices",
    "_actorSkinIterationState",
};
static igMetaField **g_igIterateGraph_fieldHandles[] = {
    &g_igIterateGraph_currentPathMetaField,
    &g_igIterateGraph_currentIndicesMetaField,
    &g_igIterateGraph_actorSkinIterationStateMetaField,
};
static int g_igIterateGraph_fieldOffsets[] = {
    12,
    16,
    8,
};

void igIterateGraph_InitFields(void) {
    int base;
    void *field;
    void *field2;
    igMetaObject *meta;

    meta = g_igIterateGraph_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igIterateGraph_ctorTable, 3);
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)Gap::Sg::igNonRefCountedNodeList::getClassTypeLazy();
    ((igRefMetaField *)field2)->_construct = 1;
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)field)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igRefMetaField *)field)->_construct = 1;
    igMetaObject_NameFields(meta, g_igIterateGraph_fieldTable, g_igIterateGraph_fieldHandles, g_igIterateGraph_fieldOffsets, base);
}

