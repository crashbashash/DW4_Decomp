igMetaObject *g_beDemoManagerWork_metaObject;
igMetaField *g_beDemoManagerWork_advancecMetaField;
igMetaField *g_beDemoManagerWork_keepMesListMetaField;

beDemoManagerWork *beDemoManagerWork_CreateInstance(int allocator) {
    beDemoManagerWork_EnsureRegistered();
    return (beDemoManagerWork *)igMetaObject_CreateInstance(*(int *)0x5897D8, allocator);
}

igMetaObject *beDemoManagerWork_GetOrCreateMetaObject(void) {
    if (g_beDemoManagerWork_metaObject == 0) {
        g_beDemoManagerWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beDemoManagerWork_metaObject;
}

void *beDemoManagerWork_GetMetaObject(void) {
    igMetaObject *g = g_beDemoManagerWork_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDemoManagerWork_EnsureRegistered();
    }
    return g_beDemoManagerWork_metaObject;
}

int beDemoManagerWork_GetVTable(void) {
    beDemoManagerWork obj;
    int vtable;
    igObject **keepMesListSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beDemoManagerWork_vtable[0];
    keepMesListSlot = (igObject **)&obj._keepMesList;
    *keepMesListSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beDemoManagerWork_vtable[0];
    igObjectRef_Release(keepMesListSlot);
    return vtable;
}

void beDemoManagerWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDemoManagerWork_Register);
}

static igMetaObjectCallback g_beDemoManagerWork_callbackList[] = { beDemoKeepMesList_EnsureRegistered, 0 };

void *beDemoManagerWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDemoManagerWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beDemoManagerWork_GetMetaObjectFunction,
        "beDemoManagerWork",
        0x10, /* instance size */
        beDemoManagerWork_GetVTable,
        beDemoManagerWork_InitFields,
        0, /* extra callback item */
        g_beDemoManagerWork_callbackList /* callback list */
    );
}

void beDemoManagerWork_GetMetaObjectFunction(void)
{
    beDemoManagerWork_GetMetaObject();
}

static FieldFactory g_beDemoManagerWork_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beDemoManagerWork_fieldTable[] = {
    "_advancec",
    "_keepMesList",
};
static igMetaField **g_beDemoManagerWork_fieldHandles[] = {
    &g_beDemoManagerWork_advancecMetaField,
    &g_beDemoManagerWork_keepMesListMetaField,
};
static int g_beDemoManagerWork_fieldOffsets[] = {
    8,
    12,
};

void beDemoManagerWork_InitFields(void) {
    int base;
    void *keepMesList;
    void *meta;

    meta = (void *)g_beDemoManagerWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDemoManagerWork_ctorTable, 2);
    keepMesList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)keepMesList)->_metaObject = (int)beDemoKeepMesList_GetOrCreateMetaObject();
    ((igRefMetaField *)keepMesList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beDemoManagerWork_fieldTable, g_beDemoManagerWork_fieldHandles, g_beDemoManagerWork_fieldOffsets, base);
}

