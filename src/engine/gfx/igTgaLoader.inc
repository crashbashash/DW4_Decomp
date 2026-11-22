igMetaObject *g_igTgaLoader_metaObject;
igMetaField *g_igTgaLoader_fileMetaField;
igMetaField *g_igTgaLoader_paletteMetaField;
igMetaField *g_igTgaLoader_tempMapMetaField;
igMetaField *g_igTgaLoader_tempRowMetaField;
igMetaField *g_igTgaLoader_bCountMetaField;
igMetaField *g_igTgaLoader_bTypeMetaField;
igMetaField *g_igTgaLoader_psizeMetaField;
igMetaField *g_igTgaLoader_nextCharMetaField;
igMetaField *g_igTgaLoader_limitCharMetaField;
igMetaField *g_igTgaLoader_sbprMetaField;

int igTgaLoader_Create(int arg0) {
    igTgaLoader_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igTgaLoader_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igTgaLoader_GetMetaObject(void)
{
    igMetaObject *g = g_igTgaLoader_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTgaLoader_EnsureRegistered();
    return g_igTgaLoader_metaObject;
}

int igTgaLoader_GetVTable(void) {
    Obj_1500f0 o;
    int **ps;
    int *temp_a0;
    int temp_s0;

    igObject_InitHeader((igObject *)&o);
    ps = &o.ref;
    o.vt = &g_igTgaLoader_vtable[0];
    *ps = 0;
    temp_s0 = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = &g_igTgaLoader_vtable[0];
    if (ps != 0) {
        temp_a0 = *ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
    }
    return temp_s0;
}

void igTgaLoader_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTgaLoader_Register);
}

static igMetaObjectCallback g_igTgaLoader_callbackList[] = { Gap::Core::igFile::arkRegister, 0 };

CallbackArray *igTgaLoader_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTgaLoader_metaObject,
        igImageLoader_Register,
        igImageLoader_GetPublishedMetaObject,
        igTgaLoader_GetMetaObjectFunction,
        "igTgaLoader",
        0x30, /* instance size */
        igTgaLoader_GetVTable,
        &igTgaLoader_InitFields,
        0, /* extra callback item */
        g_igTgaLoader_callbackList /* callback list */
    );
}

void igTgaLoader_GetMetaObjectFunction(void) {
    igTgaLoader_GetMetaObject();
}

igMetaObject *igImageLoader_GetPublishedMetaObject(void) {
    return g_igImageLoader_metaObject;
}

static FieldFactory g_igTgaLoader_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igTgaLoader_fieldTable[] = {
    "_file",
    "_palette",
    "_tempMap",
    "_tempRow",
    "_bCount",
    "_bType",
    "_psize",
    "_nextChar",
    "_limitChar",
    "_sbpr",
};
static igMetaField **g_igTgaLoader_fieldHandles[] = {
    &g_igTgaLoader_fileMetaField,
    &g_igTgaLoader_paletteMetaField,
    &g_igTgaLoader_tempMapMetaField,
    &g_igTgaLoader_tempRowMetaField,
    &g_igTgaLoader_bCountMetaField,
    &g_igTgaLoader_bTypeMetaField,
    &g_igTgaLoader_psizeMetaField,
    &g_igTgaLoader_nextCharMetaField,
    &g_igTgaLoader_limitCharMetaField,
    &g_igTgaLoader_sbprMetaField,
};
static int g_igTgaLoader_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
};

void igTgaLoader_InitFields(void) {
    int fieldStart;
    void *tempRowField;
    void *tempMapField;
    void *paletteField;
    void *fileField;
    igMetaObject *meta;

    meta = g_igTgaLoader_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igTgaLoader_ctorTable, 0xA);
    fileField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)fileField)->_metaObject = (int)Gap::Core::igFile::getClassTypeLazy();
    paletteField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 1));
    ((igMemoryRefMetaField *)paletteField)->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    tempMapField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 2));
    ((igMemoryRefMetaField *)tempMapField)->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    tempRowField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 3));
    ((igMemoryRefMetaField *)tempRowField)->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    igMetaObject_NameFields(meta, g_igTgaLoader_fieldTable, g_igTgaLoader_fieldHandles, g_igTgaLoader_fieldOffsets, fieldStart);
}

