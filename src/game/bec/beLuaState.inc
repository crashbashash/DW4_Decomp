igMetaObject *g_beLuaState_metaObject;
igMetaField *g_beLuaState_lpMetaField;

beLuaState *beLuaState_Create(int allocator) {
    beLuaState_EnsureRegistered();
    return (beLuaState *)igMetaObject_CreateInstance(g_beLuaState_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beLuaState_GetOrCreateMetaObject(void) {
    if (g_beLuaState_metaObject == 0) {
        g_beLuaState_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beLuaState_metaObject;
}

void *beLuaState_GetMetaObject(void) {
    igMetaObject *g = g_beLuaState_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLuaState_EnsureRegistered();
    }
    return g_beLuaState_metaObject;
}

int beLuaState_GetVTable(void) {
    beLuaState obj;
    int vtable;
    igObject **memPoolSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_igLuaState_vtable[0];
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    memPoolSlot = (igObject **)&obj._memPool;
    *memPoolSlot = 0;
    obj._vtable = (int)&g_beLuaState_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_igLuaState_vtable[0];
    igObjectRef_Release(memPoolSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beLuaState_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLuaState_Register);
}

CallbackArray *beLuaState_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLuaState_metaObject,
        igLuaState_Register,
        igLuaState_GetPublishedMetaObject,
        beLuaState_GetMetaObjectFunction,
        "beLuaState",
        0x18, /* instance size */
        beLuaState_GetVTable,
        beLuaState_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLuaState_GetMetaObjectFunction(void)
{
    beLuaState_GetMetaObject();
}

igMetaObject *igLuaState_GetPublishedMetaObject(void) {
    return g_igLuaState_metaObject;
}

static FieldFactory g_beLuaState_ctorTable[] = {
    igRawRefMetaField_Create,
};
static const char *g_beLuaState_fieldTable[] = {
    "_lp",
};
static igMetaField **g_beLuaState_fieldHandles[] = {
    &g_beLuaState_lpMetaField,
};
static int g_beLuaState_fieldOffsets[] = {
    20,
};

void beLuaState_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beLuaState_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beLuaState_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beLuaState_fieldTable, g_beLuaState_fieldHandles, g_beLuaState_fieldOffsets, base);
}

