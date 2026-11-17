igMetaObject *g_igDataPump_metaObject;
igMetaField *g_igDataPump_destObjMetaField;
igMetaField *g_igDataPump_destMetaMetaField;
igMetaField *g_igDataPump_destMetaClassNameMetaField;
igMetaField *g_igDataPump_destMetaFieldNameMetaField;
igMetaField *g_igDataPump_dpiMetaField;

void FUN_001e5950(int arg0) {
    FUN_001e5ab0();
    igMetaObject_CreateInstance(g_igDataPump_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igDataPump_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPump_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5ab0();
    return g_igDataPump_metaObject;
}

int igDataPump_GetVTable(void) {
    struct Obj_1e59e0 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igDataPump_vtable[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    obj.vt = &g_igDataPump_vtable[0];
    FUN_001c7600(&obj.w6, -1);
    igStringRef_Destruct((igStringRef *)&obj.w5, -1);
    igStringRef_Destruct((igStringRef *)&obj.w4, -1);
    igSmartPointer_igMetaField_Destruct((igSmartPointer<igObject> *)&obj.w3, -1);
    igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&obj.w2, -1);
    return t;
}

void FUN_001e5ab0(void)
{
    igMetaObject_RunStaticInit(igDataPump_Register);
}

static igMetaObjectCallback g_igDataPump_callbackList[] = { igObject_EnsureRegistered, igMetaField_EnsureRegistered, FUN_001e55d0, 0 };

CallbackArray *igDataPump_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igDataPump_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDataPump_GetMetaObject,
        "igDataPump",
        0x1C, /* instance size */
        igDataPump_GetVTable,
        &igDataPump_InitFields,
        0, /* extra callback item */
        g_igDataPump_callbackList /* callback list */
    );
}

void thunk_igDataPump_GetMetaObject(void) {
    igDataPump_GetMetaObject();
}

static FieldFactory g_igDataPump_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igDataPump_fieldTable[] = {
    "_destObj",
    "_destMeta",
    "_destMetaClassName",
    "_destMetaFieldName",
    "_dpi",
};
static igMetaField **g_igDataPump_fieldHandles[] = {
    &g_igDataPump_destObjMetaField,
    &g_igDataPump_destMetaMetaField,
    &g_igDataPump_destMetaClassNameMetaField,
    &g_igDataPump_destMetaFieldNameMetaField,
    &g_igDataPump_dpiMetaField,
};
static int g_igDataPump_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
};

void igDataPump_InitFields(void) {
    int firstField;
    void *destObjField;
    void *dpiField;
    void *destMetaField;
    igMetaObject *meta;

    meta = g_igDataPump_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igDataPump_ctorTable, 5);
    destObjField = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField));
    *(int *)((char *)(destObjField) + 56) = (int)((int) g_igObject_metaObject[0]);
    *(char *)((char *)(destObjField) + 52) = 1;
    destMetaField = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 1));
    *(int *)((char *)(destMetaField) + 56) = igMetaField_GetOrCreateMetaObject();
    *(char *)((char *)(destMetaField) + 38) = 0;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 2), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 3), 0);
    dpiField = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 4));
    *(int *)((char *)(dpiField) + 56) = (int)FUN_001e5530();
    igMetaObject_NameFields((igMetaObject *)meta, g_igDataPump_fieldTable, g_igDataPump_fieldHandles, g_igDataPump_fieldOffsets, firstField);
}

