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

void *beMessengerArgData_Create(void *allocator){beMessengerArgData_EnsureRegistered();return ((void *)igMetaObject_CreateInstance((void *)g_beMessengerArgData_metaObject,allocator));}

igMetaObject *FUN_00358dc0(void) {
    if (g_beMessengerArgData_metaObject == 0) {
        g_beMessengerArgData_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMessengerArgData_metaObject;
}

igMetaObject *FUN_00358e10(void) {
    if (g_beMessengerArgData_metaObject == 0 || !isValid(g_beMessengerArgData_metaObject)) beMessengerArgData_EnsureRegistered();
    return g_beMessengerArgData_metaObject;
}

int beMessengerArgData_GetVTable(void) {
    struct Obj_358e60 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536ca0[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00536ca0[0];
    igSmartPointer_igStringRefList_Destruct(&obj.w11, -1);
    igSmartPointer_igObjectList_Destruct(&obj.w10, -1);
    FUN_001998f0(&obj.w9, -1);
    FUN_001374b0(&obj.w8, -1);
    FUN_00195190(&obj.w7, -1);
    FUN_001354b0(&obj.w6, -1);
    igSmartPointer_igIntList_Destruct(&obj.w5, -1);
    FUN_00226990(&obj.w4, -1);
    igStringRef_Destruct(&obj.w3, -1);
    return t;
}

void beMessengerArgData_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerArgData_Register);}

static igMetaObjectCallback g_beMessengerArgData_callbackList[] = { igBoolList_EnsureRegistered, igIntList_EnsureRegistered, igFloatList_EnsureRegistered, igLongList_EnsureRegistered, FUN_0018a180, FUN_00189a80, igObjectList_EnsureRegistered, igStringRefList_EnsureRegistered, 0 };

void *beMessengerArgData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMessengerArgData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMessengerArgData_GetMetaObject,
        "beMessengerArgData",
        0x30, /* instance size */
        beMessengerArgData_GetVTable,
        beMessengerArgData_InitFields,
        0, /* extra callback item */
        g_beMessengerArgData_callbackList /* callback list */
    );
}

void beMessengerArgData_GetMetaObject(void)
{
    FUN_00358e10();
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
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMessengerArgData_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beMessengerArgData_ctorTable, 0xA);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igBoolList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igLongList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0018a0a0();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_001899a0();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beMessengerArgData_fieldTable, g_beMessengerArgData_fieldHandles, g_beMessengerArgData_fieldOffsets, temp_s1);
}

