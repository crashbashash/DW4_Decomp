igMetaObject *g_igIterateGraph_metaObject;
igMetaField *g_igIterateGraph_currentPathMetaField;
igMetaField *g_igIterateGraph_currentIndicesMetaField;
igMetaField *g_igIterateGraph_actorSkinIterationStateMetaField;

void *FUN_00227460(int arg0) {
    FUN_00227620();
    return igMetaObject_CreateInstance(g_igIterateGraph_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *FUN_002274a0(void) {
    if (g_igIterateGraph_metaObject == 0) {
        g_igIterateGraph_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igIterateGraph_metaObject;
}

igMetaObject *igIterateGraph_GetMetaObject(void)
{
    igMetaObject *g = g_igIterateGraph_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00227620();
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

void FUN_00227620(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igIterateGraph_Register);
}

static igMetaObjectCallback g_igIterateGraph_callbackList[] = { igNonRefCountedNodeList_EnsureRegistered, igIntList_EnsureRegistered, 0 };

CallbackArray *igIterateGraph_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igIterateGraph_metaObject,
        (igMetaObjectRegisterFunction)igIterator_Register,
        (igMetaObjectGetFunction)igIterator_GetPublishedMetaObject,
        thunk_igIterateGraph_GetMetaObject,
        "igIterateGraph",
        0x14, /* instance size */
        igIterateGraph_GetVTable,
        &igIterateGraph_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igIterateGraph_callbackList /* callback list */
    );
}

void thunk_igIterateGraph_GetMetaObject(void) {
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
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igIterateGraph_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igIterateGraph_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019c8c0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_igIterateGraph_fieldTable, g_igIterateGraph_fieldHandles, g_igIterateGraph_fieldOffsets, temp_s2);
}

