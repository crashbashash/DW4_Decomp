igMetaObject *g_beSaveDataDeliver_metaObject;
igMetaField *g_beSaveDataDeliver_sizeMetaField;
igMetaField *g_beSaveDataDeliver_dataMetaField;

igMetaObject *beSaveDataDeliver_GetOrCreateMetaObject(void) {
    if (g_beSaveDataDeliver_metaObject == 0) {
        g_beSaveDataDeliver_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSaveDataDeliver_metaObject;
}

igMetaObject *beSaveDataDeliver_GetMetaObject(void) {
    igMetaObject *g = g_beSaveDataDeliver_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beSaveDataDeliver_EnsureRegistered();
done:
    return g_beSaveDataDeliver_metaObject;
}

int beSaveDataDeliver_GetVTable(void) {
    struct Obj_34af50 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beSaveDataDeliver_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beSaveDataDeliver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSaveDataDeliver_Register);
}

void *beSaveDataDeliver_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSaveDataDeliver_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveDataDeliver_GetMetaObjectFunction,
        "beSaveDataDeliver",
        0x10, /* instance size */
        beSaveDataDeliver_GetVTable,
        beSaveDataDeliver_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSaveDataDeliver_GetMetaObjectFunction(void)
{
    beSaveDataDeliver_GetMetaObject();
}

static FieldFactory g_beSaveDataDeliver_ctorTable[] = {
    igIntMetaField_Create,
    igMemoryRefMetaField_Create,
};
static const char *g_beSaveDataDeliver_fieldTable[] = {
    "_size",
    "_data",
};
static igMetaField **g_beSaveDataDeliver_fieldHandles[] = {
    &g_beSaveDataDeliver_sizeMetaField,
    &g_beSaveDataDeliver_dataMetaField,
};
static int g_beSaveDataDeliver_fieldOffsets[] = {
    12,
    8,
};

void beSaveDataDeliver_InitFields(void) {
    int base;
    void *data;
    void *meta;

    meta = (void *)g_beSaveDataDeliver_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSaveDataDeliver_ctorTable, 2);
    data = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igMemoryRefMetaField *)data)->_memType = igCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(meta, g_beSaveDataDeliver_fieldTable, g_beSaveDataDeliver_fieldHandles, g_beSaveDataDeliver_fieldOffsets, base);
}

