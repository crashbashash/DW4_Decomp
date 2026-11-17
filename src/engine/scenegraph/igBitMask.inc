igMetaObject *g_igBitMask_metaObject;
igMetaField *g_igBitMask_bitCountMetaField;

igMetaObject *FUN_001a4d90(void) {
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
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
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
        igUnsignedIntList_Register,
        igUnsignedIntList_GetPublishedMetaObject,
        thunk_igBitMask_GetMetaObject,
        "igBitMask",
        0x18, /* instance size */
        igBitMask_GetVTable,
        &igBitMask_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBitMask_GetMetaObject(void) {
    igBitMask_GetMetaObject();
}

int FUN_001a4f00(void) {
    return (int)g_igUnsignedIntList_metaObject;
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
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igBitMask_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igBitMask_ctorTable, 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igBitMask_fieldTable, g_igBitMask_fieldHandles, g_igBitMask_fieldOffsets, temp_s1);
}

