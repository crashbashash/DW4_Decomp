igMetaObject *g_beNumVerInsideData_metaObject;
igMetaField *g_beNumVerInsideData_indexMetaField;
igMetaField *g_beNumVerInsideData_kindMetaField;

int beNumVerInsideData_Create(int allocator) {
    beNumVerInsideData_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_beNumVerInsideData_metaObject, (igMemoryPoolView *)allocator);
}

void *beNumVerInsideData_GetMetaObject(void) {
    bool ok;
    if (g_beNumVerInsideData_metaObject == 0) goto make;
    ok = !!(g_beNumVerInsideData_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNumVerInsideData_EnsureRegistered();
done:;
    return g_beNumVerInsideData_metaObject;
}

int beNumVerInsideData_GetVTable(void) {
    beNumVerInsideData obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beNumVerInsideData_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beNumVerInsideData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNumVerInsideData_Register);
}

CallbackArray *beNumVerInsideData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumVerInsideData_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beNumVerInsideData_GetMetaObjectFunction,
        "beNumVerInsideData",
        0x10, /* instance size */
        beNumVerInsideData_GetVTable,
        beNumVerInsideData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNumVerInsideData_GetMetaObjectFunction(void)
{
    beNumVerInsideData_GetMetaObject();
}

static FieldFactory g_beNumVerInsideData_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNumVerInsideData_fieldTable[] = {
    "_index",
    "_kind",
};
static igMetaField **g_beNumVerInsideData_fieldHandles[] = {
    &g_beNumVerInsideData_indexMetaField,
    &g_beNumVerInsideData_kindMetaField,
};
static int g_beNumVerInsideData_fieldOffsets[] = {
    8,
    12,
};

void beNumVerInsideData_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNumVerInsideData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNumVerInsideData_ctorTable, 2);
    igMetaObject_NameFields(meta, g_beNumVerInsideData_fieldTable, g_beNumVerInsideData_fieldHandles, g_beNumVerInsideData_fieldOffsets, base);
}

