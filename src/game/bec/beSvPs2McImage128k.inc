igMetaObject *g_beSvPs2McImage128k_metaObject;
igMetaField *g_beSvPs2McImage128k_dataSizeMetaField;
igMetaField *g_beSvPs2McImage128k_dataMetaField;

void *beSvPs2McImage128k_GetMetaObject(void) {
    igMetaObject *g = g_beSvPs2McImage128k_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvPs2McImage128k_EnsureRegistered();
    }
    return g_beSvPs2McImage128k_metaObject;
}

int beSvPs2McImage128k_GetVTable(void) {
    struct Obj_347ca0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beSvPs2McImage128k_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beSvPs2McImage128k_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvPs2McImage128k_Register);
}

void *beSvPs2McImage128k_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvPs2McImage128k_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSvPs2McImage128k_GetMetaObjectFunction,
        "beSvPs2McImage128k",
        0x10, /* instance size */
        beSvPs2McImage128k_GetVTable,
        beSvPs2McImage128k_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvPs2McImage128k_GetMetaObjectFunction(void)
{
    beSvPs2McImage128k_GetMetaObject();
}

static FieldFactory g_beSvPs2McImage128k_ctorTable[] = {
    igIntMetaField_Create,
    igMemoryRefMetaField_Create,
};
static const char *g_beSvPs2McImage128k_fieldTable[] = {
    "_dataSize",
    "_data",
};
static igMetaField **g_beSvPs2McImage128k_fieldHandles[] = {
    &g_beSvPs2McImage128k_dataSizeMetaField,
    &g_beSvPs2McImage128k_dataMetaField,
};
static int g_beSvPs2McImage128k_fieldOffsets[] = {
    12,
    8,
};

void beSvPs2McImage128k_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSvPs2McImage128k_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSvPs2McImage128k_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(temp_s0, g_beSvPs2McImage128k_fieldTable, g_beSvPs2McImage128k_fieldHandles, g_beSvPs2McImage128k_fieldOffsets, temp_s2);
}

