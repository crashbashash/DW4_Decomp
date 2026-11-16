igMetaObject *g_igMatrixObject_metaObject;
igMetaField *g_igMatrixObject_mMetaField;

void FUN_001e4c50(int arg0) {
    FUN_001e4d30();
    igMetaObject_CreateInstance(g_igMatrixObject_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igMatrixObject_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixObject_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4d30();
    return g_igMatrixObject_metaObject;
}

int igMatrixObject_GetVTable(void) {
    struct Obj_1e4ce0 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igMatrixObject_vtable[0];
    igMatrix44f_SetIdentity((float *)(obj.pad + 4));
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
}

void FUN_001e4d30(void)
{
    igMetaObject_RunStaticInit(igMatrixObject_Register);
}

CallbackArray *igMatrixObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMatrixObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMatrixObject_GetMetaObject,
        "igMatrixObject",
        0x48, /* instance size */
        igMatrixObject_GetVTable,
        &igMatrixObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMatrixObject_GetMetaObject(void) {
    igMatrixObject_GetMetaObject();
}

static FieldFactory g_igMatrixObject_ctorTable[] = {
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
};
static const char *g_igMatrixObject_fieldTable[] = {
    "_m",
};
static igMetaField **g_igMatrixObject_fieldHandles[] = {
    &g_igMatrixObject_mMetaField,
};
static int g_igMatrixObject_fieldOffsets[] = {
    8,
};

void igMatrixObject_InitFields(void) {
    int firstField;
    igMetaObject *meta;

    meta = g_igMatrixObject_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMatrixObject_ctorTable, 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igMatrixObject_fieldTable, g_igMatrixObject_fieldHandles, g_igMatrixObject_fieldOffsets, firstField);
}

