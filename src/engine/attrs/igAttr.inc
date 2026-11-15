igMetaObject *g_igAttr_metaObject;
igMetaField *g_igAttr_cachedUnitIDMetaField;
igMetaField *g_igAttr_cachedAttrIndexMetaField;

igMetaObject *FUN_0013b070(void) {
    if (g_igAttr_metaObject == 0) {
        g_igAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAttr_metaObject;
}

igMetaObject *igAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013b110();
    return g_igAttr_metaObject;
}

void FUN_0013b110(void)
{
    igMetaObject_RunStaticInit(igAttr_Register);
}

void igAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igAttr_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAttr_GetMetaObject,
        "igAttr",
        0xC, /* instance size */
        0,
        &igAttr_InitFields,
        FUN_0013b240, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAttr_GetMetaObject(void) {
    igAttr_GetMetaObject();
}

static FieldFactory g_igAttr_ctorTable[] = {
    igShortMetaField_Create,
    igShortMetaField_Create,
};
static const char *g_igAttr_fieldTable[] = {
    "_cachedUnitID",
    "_cachedAttrIndex",
};
static igMetaField **g_igAttr_fieldHandles[] = {
    &g_igAttr_cachedUnitIDMetaField,
    &g_igAttr_cachedAttrIndexMetaField,
};
static int g_igAttr_fieldOffsets[] = {
    10,
    8,
};

void igAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    igMetaObject *temp_s0;

    temp_s0 = g_igAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igAttr_ctorTable, 2);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    igShortMetaField_SetDefault(temp_v0, -1);
    ((igShortMetaField *)temp_v0)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, g_igAttr_fieldTable, g_igAttr_fieldHandles, g_igAttr_fieldOffsets, temp_s2);
}

void FUN_0013b240(void) {
    FUN_0013b800();
    igMetaObject_AddRegistrationCallback(&FUN_0013b8a0);
}

