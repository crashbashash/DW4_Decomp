igMetaObject *g_igGeometryMaskAttr_metaObject;
igMetaField *g_igGeometryMaskAttr_maskMetaField;

void FUN_00137070(int arg0) {
    FUN_00137140();
    igMetaObject_CreateInstance(*(igMetaObject * *)0x55F148, (igMemoryPoolView *)arg0);
}

igMetaObject *igGeometryMaskAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryMaskAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00137140();
    return g_igGeometryMaskAttr_metaObject;
}

int igGeometryMaskAttr_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igGeometryMaskAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_00137140(void)
{
    igMetaObject_RunStaticInit(igGeometryMaskAttr_Register);
}

CallbackArray *igGeometryMaskAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGeometryMaskAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igGeometryMaskAttr_GetMetaObject,
        "igGeometryMaskAttr",
        0x10, /* instance size */
        igGeometryMaskAttr_GetVTable,
        &igGeometryMaskAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igGeometryMaskAttr_GetMetaObject(void) {
    igGeometryMaskAttr_GetMetaObject();
}

static FieldFactory g_igGeometryMaskAttr_ctorTable[] = {
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igGeometryMaskAttr_fieldTable[] = {
    "_mask",
};
static igMetaField **g_igGeometryMaskAttr_fieldHandles[] = {
    &g_igGeometryMaskAttr_maskMetaField,
};
static int g_igGeometryMaskAttr_fieldOffsets[] = {
    12,
};

void igGeometryMaskAttr_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igGeometryMaskAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igGeometryMaskAttr_ctorTable, 1);
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1), -1);
    igMetaObject_NameFields(temp_s0, g_igGeometryMaskAttr_fieldTable, g_igGeometryMaskAttr_fieldHandles, g_igGeometryMaskAttr_fieldOffsets, temp_s1);
}

