igMetaObject *g_beSaveMemoryObj_metaObject;
igMetaField *g_beSaveMemoryObj_memMetaField;

void beSaveMemoryObj_CreateInstance(int allocator) {
    beSaveMemoryObj_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5883A0, allocator);
}

igMetaObject *beSaveMemoryObj_GetOrCreateMetaObject(void) {
    if (g_beSaveMemoryObj_metaObject == 0) {
        g_beSaveMemoryObj_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSaveMemoryObj_metaObject;
}

igMetaObject *beSaveMemoryObj_GetMetaObject(void) {
    igMetaObject *g = g_beSaveMemoryObj_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beSaveMemoryObj_EnsureRegistered();
    return g_beSaveMemoryObj_metaObject;
}

int beSaveMemoryObj_GetVTable(void) {
    struct Obj_34ad30 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beSaveMemoryObj_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beSaveMemoryObj_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSaveMemoryObj_Register);
}

void *beSaveMemoryObj_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSaveMemoryObj_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveMemoryObj_GetMetaObjectFunction,
        "beSaveMemoryObj",
        0xc, /* instance size */
        beSaveMemoryObj_GetVTable,
        beSaveMemoryObj_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSaveMemoryObj_GetMetaObjectFunction(void)
{
    beSaveMemoryObj_GetMetaObject();
}

static FieldFactory g_beSaveMemoryObj_ctorTable[] = {
    igMemoryRefMetaField_Create,
};
static const char *g_beSaveMemoryObj_fieldTable[] = {
    "_mem",
};
static igMetaField **g_beSaveMemoryObj_fieldHandles[] = {
    &g_beSaveMemoryObj_memMetaField,
};
static int g_beSaveMemoryObj_fieldOffsets[] = {
    8,
};

void beSaveMemoryObj_InitFields(void) {
    int base;
    void *mem;
    void *meta;

    meta = (void *)g_beSaveMemoryObj_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSaveMemoryObj_ctorTable, 1);
    mem = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igMemoryRefMetaField *)mem)->_memType = igCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(meta, g_beSaveMemoryObj_fieldTable, g_beSaveMemoryObj_fieldHandles, g_beSaveMemoryObj_fieldOffsets, base);
}

