igMetaObject *g_beXboxImage24k_metaObject;
igMetaField *g_beXboxImage24k_dataSizeMetaField;
igMetaField *g_beXboxImage24k_dataMetaField;

igMetaObject *beXboxImage24k_GetOrCreateMetaObject(void) {
    if (g_beXboxImage24k_metaObject == 0) {
        g_beXboxImage24k_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beXboxImage24k_metaObject;
}

void *beXboxImage24k_GetMetaObject(void) {
    unsigned char b;
    if (g_beXboxImage24k_metaObject != 0) {
        b = (g_beXboxImage24k_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beXboxImage24k_EnsureRegistered();
done:
    return g_beXboxImage24k_metaObject;
}

int beXboxImage24k_GetVTable(void) {
    beXboxImage24k obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beXboxImage24k_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beXboxImage24k_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beXboxImage24k_Register);
}

CallbackArray *beXboxImage24k_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beXboxImage24k_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beXboxImage24k_GetMetaObjectFunction,
        "beXboxImage24k",
        0x10, /* instance size */
        beXboxImage24k_GetVTable,
        beXboxImage24k_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beXboxImage24k_GetMetaObjectFunction(void)
{
    beXboxImage24k_GetMetaObject();
}

static FieldFactory g_beXboxImage24k_ctorTable[] = {
    igIntMetaField_Create,
    igMemoryRefMetaField_Create,
};
static const char *g_beXboxImage24k_fieldTable[] = {
    "_dataSize",
    "_data",
};
static igMetaField **g_beXboxImage24k_fieldHandles[] = {
    &g_beXboxImage24k_dataSizeMetaField,
    &g_beXboxImage24k_dataMetaField,
};
static int g_beXboxImage24k_fieldOffsets[] = {
    12,
    8,
};

void beXboxImage24k_InitFields(void) {
    int base;
    void *data;
    igMetaObject *meta;

    meta = g_beXboxImage24k_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beXboxImage24k_ctorTable, 2);
    data = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igMemoryRefMetaField *)data)->_memType = igCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(meta, g_beXboxImage24k_fieldTable, g_beXboxImage24k_fieldHandles, g_beXboxImage24k_fieldOffsets, base);
}

