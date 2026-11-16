igMetaObject *g_bePlaySE_metaObject;
igMetaField *g_bePlaySE_idMetaField;
igMetaField *g_bePlaySE_timeMetaField;

bePlaySE *bePlaySE_CreateInstance(int allocator) {
    bePlaySE_EnsureRegistered();
    return (bePlaySE *)igMetaObject_CreateInstance(*(int *)0x587ED0, allocator);
}

void *bePlaySE_GetMetaObject(void) {
    igMetaObject *g = g_bePlaySE_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        bePlaySE_EnsureRegistered();
    }
    return g_bePlaySE_metaObject;
}

int bePlaySE_GetVTable(void) {
    bePlaySE obj;
    int off;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_bePlaySE_vtable[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)&obj + off);
}

void bePlaySE_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(bePlaySE_Register);
}

void *bePlaySE_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_bePlaySE_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        bePlaySE_GetMetaObjectFunction,
        "bePlaySE",
        0x18, /* instance size */
        bePlaySE_GetVTable,
        bePlaySE_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void bePlaySE_GetMetaObjectFunction(void)
{
    bePlaySE_GetMetaObject();
}

static FieldFactory g_bePlaySE_ctorTable[] = {
    igIntMetaField_Create,
    igLongMetaField_Create,
};
static const char *g_bePlaySE_fieldTable[] = {
    "_id",
    "_time",
};
static igMetaField **g_bePlaySE_fieldHandles[] = {
    &g_bePlaySE_idMetaField,
    &g_bePlaySE_timeMetaField,
};
static int g_bePlaySE_fieldOffsets[] = {
    8,
    16,
};

void bePlaySE_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_bePlaySE_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_bePlaySE_ctorTable, 2);
    igMetaObject_NameFields(meta, g_bePlaySE_fieldTable, g_bePlaySE_fieldHandles, g_bePlaySE_fieldOffsets, base);
}

