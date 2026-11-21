igMetaObject *g_igBitMask_metaObject;
igMetaField *g_igBitMask_bitCountMetaField;

igMetaObject *igBitMask_GetOrCreateMetaObject(void) {
    if (g_igBitMask_metaObject == 0) {
        g_igBitMask_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igBitMask_metaObject;
}

igMetaObject *igBitMask_GetMetaObject(void)
{
    igMetaObject *g = g_igBitMask_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBitMask_EnsureRegistered();
    return g_igBitMask_metaObject;
}

int igBitMask_GetVTable(void) {
    struct Obj_1a4e30 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igBitMask_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igBitMask_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBitMask_Register);
}

CallbackArray *igBitMask_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBitMask_metaObject,
        Gap::Core::igUnsignedIntList::arkRegisterInternal,
        igUnsignedIntList_GetPublishedMetaObject,
        igBitMask_GetMetaObjectFunction,
        "igBitMask",
        0x18, /* instance size */
        igBitMask_GetVTable,
        &igBitMask_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igBitMask_GetMetaObjectFunction(void) {
    igBitMask_GetMetaObject();
}

int FUN_001a4f00(void) {
    return (int)Gap::Core::igUnsignedIntList::getClassMeta();
}

static FieldFactory g_igBitMask_ctorTable[] = {
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igBitMask_fieldTable[] = {
    "_bitCount",
};
static igMetaField **g_igBitMask_fieldHandles[] = {
    &g_igBitMask_bitCountMetaField,
};
static int g_igBitMask_fieldOffsets[] = {
    20,
};

void igBitMask_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igBitMask_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igBitMask_ctorTable, 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igBitMask_fieldTable, g_igBitMask_fieldHandles, g_igBitMask_fieldOffsets, base);
}

