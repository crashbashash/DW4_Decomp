igMetaObject *g_beNumberCtrlInfoWork_metaObject;
igMetaField *g_beNumberCtrlInfoWork_dispNumMetaField;
igMetaField *g_beNumberCtrlInfoWork_realNumMetaField;
igMetaField *g_beNumberCtrlInfoWork_changeNumMetaField;

beNumberCtrlInfoWork *beNumberCtrlInfoWork_Create(int allocator) {
    beNumberCtrlInfoWork_EnsureRegistered();
    return (beNumberCtrlInfoWork *)igMetaObject_CreateInstance(*(int *)0x588630, allocator);
}

igMetaObject *beNumberCtrlInfoWork_GetOrCreateMetaObject(void) {
    if (g_beNumberCtrlInfoWork_metaObject == 0) {
        g_beNumberCtrlInfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNumberCtrlInfoWork_metaObject;
}

igMetaObject *beNumberCtrlInfoWork_GetMetaObject(void) {
    igMetaObject *g = g_beNumberCtrlInfoWork_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNumberCtrlInfoWork_EnsureRegistered();
    return g_beNumberCtrlInfoWork_metaObject;
}

int beNumberCtrlInfoWork_GetVTable(void) {
    beNumberCtrlInfoWork obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beNumberCtrlInfoWork_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void beNumberCtrlInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNumberCtrlInfoWork_Register);
}

void *beNumberCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumberCtrlInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNumberCtrlInfoWork_GetMetaObjectFunction,
        "beNumberCtrlInfoWork",
        0x14, /* instance size */
        beNumberCtrlInfoWork_GetVTable,
        beNumberCtrlInfoWork_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNumberCtrlInfoWork_GetMetaObjectFunction(void)
{
    beNumberCtrlInfoWork_GetMetaObject();
}

static FieldFactory g_beNumberCtrlInfoWork_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNumberCtrlInfoWork_fieldTable[] = {
    "_dispNum",
    "_realNum",
    "_changeNum",
};
static igMetaField **g_beNumberCtrlInfoWork_fieldHandles[] = {
    &g_beNumberCtrlInfoWork_dispNumMetaField,
    &g_beNumberCtrlInfoWork_realNumMetaField,
    &g_beNumberCtrlInfoWork_changeNumMetaField,
};
static int g_beNumberCtrlInfoWork_fieldOffsets[] = {
    8,
    12,
    16,
};

void beNumberCtrlInfoWork_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beNumberCtrlInfoWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNumberCtrlInfoWork_ctorTable, 3);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(meta, base)), -1);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(meta, base + 1)), -1);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(meta, base + 2)), -1);
    igMetaObject_NameFields(meta, g_beNumberCtrlInfoWork_fieldTable, g_beNumberCtrlInfoWork_fieldHandles, g_beNumberCtrlInfoWork_fieldOffsets, base);
}

