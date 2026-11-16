igMetaObject *g_igController_metaObject;
igMetaField *g_igController_buttonMapMetaField;
igMetaField *g_igController_isMappedMetaField;

igMetaObject *igController_GetMetaObject(void)
{
    igMetaObject *g = g_igController_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146900();
    return g_igController_metaObject;
}

void FUN_00146900(void)
{
    igMetaObject_RunStaticInit(igController_Register);
}

CallbackArray *igController_Register(void) {
    WindowInputLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igController_metaObject,
        igEventProducer_Register,
        igEventProducer_GetPublishedMetaObject,
        thunk_igController_GetMetaObject,
        "igController",
        0x10, /* instance size */
        0,
        &igController_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igController_GetMetaObject(void) {
    igController_GetMetaObject();
}

static FieldFactory g_igController_ctorTable[] = {
    igMemoryRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_igController_fieldTable[] = {
    "_buttonMap",
    "_isMapped",
};
static igMetaField **g_igController_fieldHandles[] = {
    &g_igController_buttonMapMetaField,
    &g_igController_isMappedMetaField,
};
static int g_igController_fieldOffsets[] = {
    8,
    12,
};

void igController_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igController_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igController_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 60) = igIntMetaField_GetDefaultDescriptor();
    *(char *)((char *)(temp_s1) + 53) = 1;
    *(char *)((char *)(temp_s1) + 64) = 1;
    *(char *)((char *)(temp_s1) + 65) = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igController_fieldTable, g_igController_fieldHandles, g_igController_fieldOffsets, temp_s2);
    *(int *)((char *)(g_igController_metaObject) + 60) = (int)thunk_igPsx2Controller_GetMetaObject;
}

