igMetaObject *g_beMessengerArgData_metaObject;
igMetaField *g_beMessengerArgData_isRunCheckMetaField;
igMetaField *g_beMessengerArgData_debugStringMetaField;
igMetaField *g_beMessengerArgData_boolListMetaField;
igMetaField *g_beMessengerArgData_intListMetaField;
igMetaField *g_beMessengerArgData_floatListMetaField;
igMetaField *g_beMessengerArgData_longListMetaField;
igMetaField *g_beMessengerArgData_vec3fListMetaField;
igMetaField *g_beMessengerArgData_matrix44fListMetaField;
igMetaField *g_beMessengerArgData_objectListMetaField;
igMetaField *g_beMessengerArgData_stringListMetaField;

beMessengerArgData *beMessengerArgData_Create(void *allocator) {
    beMessengerArgData_EnsureRegistered();
    return (beMessengerArgData *)igMetaObject_CreateInstance((void *)g_beMessengerArgData_metaObject,allocator);
}

igMetaObject *beMessengerArgData_GetOrCreateMetaObject(void) {
    if (g_beMessengerArgData_metaObject == 0) {
        g_beMessengerArgData_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMessengerArgData_metaObject;
}

igMetaObject *beMessengerArgData_GetMetaObject(void) {
    if (g_beMessengerArgData_metaObject == 0 || !isValid(g_beMessengerArgData_metaObject)) beMessengerArgData_EnsureRegistered();
    return g_beMessengerArgData_metaObject;
}

int beMessengerArgData_GetVTable(void) {
    beMessengerArgData obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beMessengerArgData_vtable[0];
    obj._debugString = 0;
    obj._boolList = 0;
    obj._intList = 0;
    obj._floatList = 0;
    obj._longList = 0;
    obj._vec3fList = 0;
    obj._matrix44fList = 0;
    obj._objectList = 0;
    obj._stringList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beMessengerArgData_vtable[0];
    igSmartPointer_igStringRefList_Destruct(&obj._stringList, -1);
    igSmartPointer_igObjectList_Destruct(&obj._objectList, -1);
    igSmartPointer_igMatrix44fList_Destruct(&obj._matrix44fList, -1);
    igSmartPointer_igVec3fList_Destruct(&obj._vec3fList, -1);
    igSmartPointer_igLongList_Destruct(&obj._longList, -1);
    igSmartPointer_igFloatList_Destruct(&obj._floatList, -1);
    igSmartPointer_igIntList_Destruct(&obj._intList, -1);
    igSmartPointer_igBoolList_Destruct(&obj._boolList, -1);
    igStringRef_Destruct(&obj._debugString, -1);
    return vtable;
}

void beMessengerArgData_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerArgData_Register);}

static igMetaObjectCallback g_beMessengerArgData_callbackList[] = { igBoolList_EnsureRegistered, igIntList_EnsureRegistered, igFloatList_EnsureRegistered, igLongList_EnsureRegistered, igVec3fList_EnsureRegistered, igMatrix44fList_EnsureRegistered, igObjectList_EnsureRegistered, igStringRefList_EnsureRegistered, 0 };

void *beMessengerArgData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMessengerArgData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMessengerArgData_GetMetaObjectFunction,
        "beMessengerArgData",
        0x30, /* instance size */
        beMessengerArgData_GetVTable,
        beMessengerArgData_InitFields,
        0, /* extra callback item */
        g_beMessengerArgData_callbackList /* callback list */
    );
}

void beMessengerArgData_GetMetaObjectFunction(void)
{
    beMessengerArgData_GetMetaObject();
}

static FieldFactory g_beMessengerArgData_ctorTable[] = {
    igBoolMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMessengerArgData_fieldTable[] = {
    "_isRunCheck",
    "_debugString",
    "_boolList",
    "_intList",
    "_floatList",
    "_longList",
    "_vec3fList",
    "_matrix44fList",
    "_objectList",
    "_stringList",
};
static igMetaField **g_beMessengerArgData_fieldHandles[] = {
    &g_beMessengerArgData_isRunCheckMetaField,
    &g_beMessengerArgData_debugStringMetaField,
    &g_beMessengerArgData_boolListMetaField,
    &g_beMessengerArgData_intListMetaField,
    &g_beMessengerArgData_floatListMetaField,
    &g_beMessengerArgData_longListMetaField,
    &g_beMessengerArgData_vec3fListMetaField,
    &g_beMessengerArgData_matrix44fListMetaField,
    &g_beMessengerArgData_objectListMetaField,
    &g_beMessengerArgData_stringListMetaField,
};
static int g_beMessengerArgData_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
};

void beMessengerArgData_InitFields(void) {
    void *boolList;
    void *intList;
    void *floatList;
    void *longList;
    void *vec3fList;
    void *matrix44fList;
    void *objectList;
    void *stringList;
    int base;
    void *meta;

    meta = (void *)g_beMessengerArgData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMessengerArgData_ctorTable, 0xA);
    boolList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)boolList)->_metaObject = igBoolList_GetOrCreateMetaObject();
    ((igRefMetaField *)boolList)->_construct = 1;
    intList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)intList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)intList)->_construct = 1;
    floatList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)floatList)->_metaObject = igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)floatList)->_construct = 1;
    longList = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)longList)->_metaObject = igLongList_GetOrCreateMetaObject();
    ((igRefMetaField *)longList)->_construct = 1;
    vec3fList = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)vec3fList)->_metaObject = igVec3fList_GetOrCreateMetaObject();
    ((igRefMetaField *)vec3fList)->_construct = 1;
    matrix44fList = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)matrix44fList)->_metaObject = igMatrix44fList_GetOrCreateMetaObject();
    ((igRefMetaField *)matrix44fList)->_construct = 1;
    objectList = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)objectList)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)objectList)->_construct = 1;
    stringList = (void *)(igMetaObject_GetFieldAt(meta, base + 9));
    ((igObjectRefMetaField *)stringList)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)stringList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beMessengerArgData_fieldTable, g_beMessengerArgData_fieldHandles, g_beMessengerArgData_fieldOffsets, base);
}

