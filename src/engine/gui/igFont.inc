igMetaObject *g_igFont_metaObject;
igMetaField *g_igFont_heightMetaField;
igMetaField *g_igFont_baseLineMetaField;
igMetaField *g_igFont_attrListMetaField;
igMetaField *g_igFont_vertexFlagsMetaField;

igMetaObject *FUN_004507f0(void) {
    if (g_igFont_metaObject == 0) {
        g_igFont_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igFont_metaObject;
}

igMetaObject *igFont_GetMetaObject(void)
{
    igMetaObject *g = g_igFont_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFont_EnsureRegistered();
    return g_igFont_metaObject;
}

void igFont_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFont_Register);
}

static igMetaObjectCallback g_igFont_callbackList[] = { FUN_0013afe0, 0 };

void igFont_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igFont_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igFont_GetMetaObject,
        "igFont",
        0x1C, /* instance size */
        0,
        &igFont_InitFields,
        0, /* extra callback item */
        g_igFont_callbackList /* callback list */
    );
}

void thunk_igFont_GetMetaObject(void) {
    igFont_GetMetaObject();
}

static FieldFactory g_igFont_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igObjectRefMetaField_Create,
    igUnsignedIntMetaField_Create,
};
static const char *g_igFont_fieldTable[] = {
    "_height",
    "_baseLine",
    "_attrList",
    "_vertexFlags",
};
static igMetaField **g_igFont_fieldHandles[] = {
    &g_igFont_heightMetaField,
    &g_igFont_baseLineMetaField,
    &g_igFont_attrListMetaField,
    &g_igFont_vertexFlagsMetaField,
};
static int g_igFont_fieldOffsets[] = {
    12,
    16,
    20,
    24,
};

void igFont_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igFont_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igFont_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_igFont_fieldTable, g_igFont_fieldHandles, g_igFont_fieldOffsets, temp_s2);
}

