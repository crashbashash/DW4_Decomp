igMetaObject *g_beUnicodeObj_metaObject;
igMetaField *g_beUnicodeObj_bufferMetaField;

beUnicodeObj *beUnicodeObj_Create(int allocator) {
    beUnicodeObj_EnsureRegistered();
    return (beUnicodeObj *)igMetaObject_CreateInstance(g_beUnicodeObj_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beUnicodeObj_GetMetaObject(void) {
    igMetaObject *g = g_beUnicodeObj_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beUnicodeObj_EnsureRegistered();
    return g_beUnicodeObj_metaObject;
}

int beUnicodeObj_GetVTable(void) {
    beUnicodeObj obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beUnicodeObj_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beUnicodeObj_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beUnicodeObj_Register);
}

CallbackArray *beUnicodeObj_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beUnicodeObj_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beUnicodeObj_GetMetaObjectFunction,
        "beUnicodeObj",
        0x10, /* instance size */
        beUnicodeObj_GetVTable,
        beUnicodeObj_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beUnicodeObj_GetMetaObjectFunction(void)
{
    beUnicodeObj_GetMetaObject();
}

static FieldFactory g_beUnicodeObj_ctorTable[] = {
    igMemoryRefMetaField_Create,
};
static const char *g_beUnicodeObj_fieldTable[] = {
    "_buffer",
};
static igMetaField **g_beUnicodeObj_fieldHandles[] = {
    &g_beUnicodeObj_bufferMetaField,
};
static int g_beUnicodeObj_fieldOffsets[] = {
    12,
};

void beUnicodeObj_InitFields(void) {
    int base;
    void *buffer;
    igMetaObject *meta;

    meta = g_beUnicodeObj_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beUnicodeObj_ctorTable, 1);
    buffer = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igMemoryRefMetaField *)buffer)->_memType = igUnsignedShortMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(meta, g_beUnicodeObj_fieldTable, g_beUnicodeObj_fieldHandles, g_beUnicodeObj_fieldOffsets, base);
}

