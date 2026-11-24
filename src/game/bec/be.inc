igMetaObject *g_be_metaObject;
igMetaField *g_be_stringRefListMetaField;

be *be_CreateInstance(int allocator) {
    be_EnsureRegistered();
    return (be *)igMetaObject_CreateInstance(g_be_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *be_GetOrCreateMetaObject(void) {
    if (g_be_metaObject == 0) {
        g_be_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_be_metaObject;
}

void *be_GetMetaObject(void) {
    igMetaObject *g = g_be_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        be_EnsureRegistered();
    }
    return g_be_metaObject;
}

int be_GetVTable(void) {
    be obj;
    int vtable;
    igObject **stringRefListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_be_vtable[0];
    stringRefListSlot = (igObject **)&obj._stringRefList;
    *stringRefListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_be_vtable[0];
    igObjectRef_Release(stringRefListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void be_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(be_Register);
}

static igMetaObjectCallback g_be_callbackList[] = { igStringRefList_EnsureRegistered, 0 };

CallbackArray *be_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_be_metaObject,
        Gap::Insight::igInfoManager::arkRegisterInternal,
        Gap::Insight::igInfoManager::getClassMeta,
        be_GetMetaObjectFunction,
        "be",
        0x14, /* instance size */
        be_GetVTable,
        be_InitFields,
        0, /* extra callback item */
        g_be_callbackList /* callback list */
    );
}

void be_GetMetaObjectFunction(void)
{
    be_GetMetaObject();
}

static FieldFactory g_be_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_be_fieldTable[] = {
    "_stringRefList",
};
static igMetaField **g_be_fieldHandles[] = {
    &g_be_stringRefListMetaField,
};
static int g_be_fieldOffsets[] = {
    16,
};

void be_InitFields(void) {
    int base;
    void *stringRefList;
    igMetaObject *meta;

    meta = g_be_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_be_ctorTable, 1);
    stringRefList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)stringRefList)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)stringRefList)->_construct = 1;
    igMetaObject_NameFields(meta, g_be_fieldTable, g_be_fieldHandles, g_be_fieldOffsets, base);
}

