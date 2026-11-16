igMetaObject *g_beCriSndf_metaObject;
igMetaField *g_beCriSndf_reqMetaField;
igMetaField *g_beCriSndf_seqMetaField;
igMetaField *g_beCriSndf_isPlayingMetaField;

beCriSndf *beCriSndf_Create(int allocator) {
    beCriSndf_EnsureRegistered();
    return (beCriSndf *)igMetaObject_CreateInstance(g_beCriSndf_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beCriSndf_GetOrCreateMetaObject(void) {
    if (g_beCriSndf_metaObject == 0) {
        g_beCriSndf_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beCriSndf_metaObject;
}

void *beCriSndf_GetMetaObject(void) {
    igMetaObject *g = g_beCriSndf_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCriSndf_EnsureRegistered();
    }
    return g_beCriSndf_metaObject;
}

int beCriSndf_GetVTable(void) {
    beCriSndf obj;
    int off;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beCriSndf_vtable[0];
    off = *(int *)((char *)g_objectSystem + 916);
    return *(int *)((char *)&obj + off);
}

void beCriSndf_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCriSndf_Register);
}

CallbackArray *beCriSndf_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCriSndf_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCriSndf_GetMetaObjectFunction,
        "beCriSndf",
        0x20, /* instance size */
        beCriSndf_GetVTable,
        beCriSndf_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beCriSndf_GetMetaObjectFunction(void)
{
    beCriSndf_GetMetaObject();
}

static FieldFactory g_beCriSndf_ctorTable[] = {
    igIntMetaField_Create,
    igLongMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beCriSndf_fieldTable[] = {
    "_req",
    "_seq",
    "_isPlaying",
};
static igMetaField **g_beCriSndf_fieldHandles[] = {
    &g_beCriSndf_reqMetaField,
    &g_beCriSndf_seqMetaField,
    &g_beCriSndf_isPlayingMetaField,
};
static int g_beCriSndf_fieldOffsets[] = {
    8,
    16,
    24,
};

void beCriSndf_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beCriSndf_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCriSndf_ctorTable, 3);
    igMetaObject_NameFields(meta, g_beCriSndf_fieldTable, g_beCriSndf_fieldHandles, g_beCriSndf_fieldOffsets, base);
}

