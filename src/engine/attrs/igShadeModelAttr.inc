igMetaObject *g_igShadeModelAttr_metaObject;
igMetaField *g_igShadeModelAttr_modeMetaField;

igMetaObject *FUN_00133950(void) {
    if (g_igShadeModelAttr_metaObject == 0) {
        g_igShadeModelAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igShadeModelAttr_metaObject;
}

igMetaObject *igShadeModelAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igShadeModelAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igShadeModelAttr_EnsureRegistered();
    return g_igShadeModelAttr_metaObject;
}

int igShadeModelAttr_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igShadeModelAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igShadeModelAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igShadeModelAttr_Register);
}

CallbackArray *igShadeModelAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igShadeModelAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igShadeModelAttr_GetMetaObject,
        "igShadeModelAttr",
        0x10, /* instance size */
        igShadeModelAttr_GetVTable,
        &igShadeModelAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igShadeModelAttr_GetMetaObject(void) {
    igShadeModelAttr_GetMetaObject();
}

static FieldFactory g_igShadeModelAttr_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igShadeModelAttr_fieldTable[] = {
    "_mode",
};
static igMetaField **g_igShadeModelAttr_fieldHandles[] = {
    &g_igShadeModelAttr_modeMetaField,
};
static int g_igShadeModelAttr_fieldOffsets[] = {
    12,
};

int g_igShadeModelAttr_modeDefault = 1;

void igShadeModelAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    igMetaObject *temp_s0;

    temp_s0 = g_igShadeModelAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igShadeModelAttr_ctorTable, 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0, g_igShadeModelAttr_modeDefault);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00149680);
    igMetaObject_NameFields(temp_s0, g_igShadeModelAttr_fieldTable, g_igShadeModelAttr_fieldHandles, g_igShadeModelAttr_fieldOffsets, temp_s2);
}

