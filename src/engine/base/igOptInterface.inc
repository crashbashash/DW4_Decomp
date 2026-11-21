igMetaObject *g_igOptInterface_metaObject;
igMetaField *g_igOptInterface_optimizationListMetaField;
igMetaField *g_igOptInterface_filePathMetaField;
igMetaField *g_igOptInterface_fileMetaField;
igMetaField *g_igOptInterface_disabledInfosMetaField;

igMetaObject *igOptInterface_GetOrCreateMetaObject(void) {
    if (g_igOptInterface_metaObject == 0) {
        g_igOptInterface_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igOptInterface_metaObject;
}

igMetaObject *igOptInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igOptInterface_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00225c10();
    return g_igOptInterface_metaObject;
}

int igOptInterface_GetVTable(void) {
    struct Obj_2 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igOptInterface_vtable[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igOptInterface_vtable[0];
    igSmartPointer_igInfoList_Destruct((igSmartPointer<igObject> *)&obj.w11, -1);
    FUN_00225b90((void **)&obj.w10, -1);
    igStringRef_Destruct((igStringRef *)&obj.w9, -1);
    igSmartPointer_igMetaObjectList_Destruct((igSmartPointer<igObject> *)&obj.w8, -1);
    return t;
}

void **FUN_00225b90(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void FUN_00225c10(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igOptInterface_Register);
}

static igMetaObjectCallback g_igOptInterface_callbackList[] = { igMetaObjectList_EnsureRegistered, FUN_002290c0, igInfoList_EnsureRegistered, 0 };

CallbackArray *igOptInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igOptInterface_metaObject,
        (igMetaObjectRegisterFunction)igInterface_Register,
        (igMetaObjectGetFunction)igInterface_GetPublishedMetaObject,
        igOptInterface_GetMetaObjectFunction,
        "igOptInterface",
        0x30, /* instance size */
        igOptInterface_GetVTable,
        &igOptInterface_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igOptInterface_callbackList /* callback list */
    );
}

void igOptInterface_GetMetaObjectFunction(void) {
    igOptInterface_GetMetaObject();
}

igMetaObject *igInterface_GetPublishedMetaObject(void) {
    return g_igInterface_metaObject;
}

static FieldFactory g_igOptInterface_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igOptInterface_fieldTable[] = {
    "_optimizationList",
    "_filePath",
    "_file",
    "_disabledInfos",
};
static igMetaField **g_igOptInterface_fieldHandles[] = {
    &g_igOptInterface_optimizationListMetaField,
    &g_igOptInterface_filePathMetaField,
    &g_igOptInterface_fileMetaField,
    &g_igOptInterface_disabledInfosMetaField,
};
static int g_igOptInterface_fieldOffsets[] = {
    32,
    36,
    40,
    44,
};

void igOptInterface_InitFields(void) {
    int base;
    void *field;
    void *field2;
    void *field3;
    void *field4;
    igMetaObject *meta;

    meta = g_igOptInterface_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igOptInterface_ctorTable, 4);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMetaObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)field)->_construct = 1;
    field4 = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((Gap::Core::igStringMetaField *)field4)->setDefault("");
    ((igStringMetaField *)field4)->_destruct = 1;
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)igFileInfo_GetOrCreateMetaObject();
    ((igRefMetaField *)field2)->_construct = 1;
    field3 = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)field3)->_metaObject = (int)igInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)field3)->_construct = 1;
    igMetaObject_NameFields(meta, g_igOptInterface_fieldTable, g_igOptInterface_fieldHandles, g_igOptInterface_fieldOffsets, base);
}

