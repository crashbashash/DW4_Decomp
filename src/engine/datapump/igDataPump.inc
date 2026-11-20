igMetaObject *g_igDataPump_metaObject;
igMetaField *g_igDataPump_destObjMetaField;
igMetaField *g_igDataPump_destMetaMetaField;
igMetaField *g_igDataPump_destMetaClassNameMetaField;
igMetaField *g_igDataPump_destMetaFieldNameMetaField;
igMetaField *g_igDataPump_dpiMetaField;

void igDataPump_Create(int arg0) {
    igDataPump_EnsureRegistered();
    igMetaObject_CreateInstance(g_igDataPump_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igDataPump_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPump_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDataPump_EnsureRegistered();
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
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igDataPump_vtable[0];
    igSmartPointer_igDataPumpInterface_Destruct((igSmartPointer<igObject> *)&obj.w6, -1);
    igStringRef_Destruct((igStringRef *)&obj.w5, -1);
    igStringRef_Destruct((igStringRef *)&obj.w4, -1);
    igSmartPointer_igMetaField_Destruct((igSmartPointer<igObject> *)&obj.w3, -1);
    igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&obj.w2, -1);
    return t;
}

void igDataPump_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDataPump_Register);
}

static igMetaObjectCallback g_igDataPump_callbackList[] = { Gap::Core::igObject::arkRegister, igMetaField_EnsureRegistered, igDataPumpInterface_EnsureRegistered, 0 };

CallbackArray *igDataPump_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igDataPump_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igDataPump_GetMetaObjectFunction,
        "igDataPump",
        0x1C, /* instance size */
        igDataPump_GetVTable,
        &igDataPump_InitFields,
        0, /* extra callback item */
        g_igDataPump_callbackList /* callback list */
    );
}

void igDataPump_GetMetaObjectFunction(void) {
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
    *(int *)((char *)(destObjField) + 56) = (int)Gap::Core::igObject::getClassMeta();
    *(char *)((char *)(destObjField) + 52) = 1;
    destMetaField = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 1));
    *(int *)((char *)(destMetaField) + 56) = (int)igMetaField_GetOrCreateMetaObject();
    *(char *)((char *)(destMetaField) + 38) = 0;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 2), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 3), 0);
    dpiField = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 4));
    *(int *)((char *)(dpiField) + 56) = (int)igDataPumpInterface_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igDataPump_fieldTable, g_igDataPump_fieldHandles, g_igDataPump_fieldOffsets, firstField);
}

