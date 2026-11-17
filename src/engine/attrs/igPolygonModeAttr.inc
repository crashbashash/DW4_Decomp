igMetaObject *g_igPolygonModeAttr_metaObject;
igMetaField *g_igPolygonModeAttr_modeMetaField;

igMetaObject *FUN_00134940(void) {
    if (g_igPolygonModeAttr_metaObject == 0) {
        g_igPolygonModeAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igPolygonModeAttr_metaObject;
}

igMetaObject *igPolygonModeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igPolygonModeAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00134a20();
    return g_igPolygonModeAttr_metaObject;
}

int igPolygonModeAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igPolygonModeAttr_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void FUN_00134a20(void)
{
    igMetaObject_RunStaticInit(igPolygonModeAttr_Register);
}

CallbackArray *igPolygonModeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPolygonModeAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igPolygonModeAttr_GetMetaObject,
        "igPolygonModeAttr",
        0x10, /* instance size */
        igPolygonModeAttr_GetVTable,
        &igPolygonModeAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igPolygonModeAttr_GetMetaObject(void) {
    igPolygonModeAttr_GetMetaObject();
}

static FieldFactory g_igPolygonModeAttr_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igPolygonModeAttr_fieldTable[] = {
    "_mode",
};
static igMetaField **g_igPolygonModeAttr_fieldHandles[] = {
    &g_igPolygonModeAttr_modeMetaField,
};
static int g_igPolygonModeAttr_fieldOffsets[] = {
    12,
};

void igPolygonModeAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    igMetaObject *temp_s0;

    temp_s0 = g_igPolygonModeAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igPolygonModeAttr_ctorTable, 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0, 0);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_001495c0);
    igMetaObject_NameFields(temp_s0, g_igPolygonModeAttr_fieldTable, g_igPolygonModeAttr_fieldHandles, g_igPolygonModeAttr_fieldOffsets, temp_s2);
}

