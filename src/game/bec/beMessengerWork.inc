igMetaObject *g_beMessengerWork_metaObject;
igMetaField *g_beMessengerWork_groupNameMetaField;
igMetaField *g_beMessengerWork_infoNameMetaField;
igMetaField *g_beMessengerWork_ramNoMetaField;
igMetaField *g_beMessengerWork_messageMetaField;
igMetaField *g_beMessengerWork_findRamNoListMetaField;
igMetaField *g_beMessengerWork_findRamListMetaField;

void *beMessengerWork_Create(void *allocator){beMessengerWork_EnsureRegistered();return ((void *)igMetaObject_CreateInstance((void *)g_beMessengerWork_metaObject,allocator));}

void *beMessengerWork_GetMetaObject(void) {
    igMetaObject *g = g_beMessengerWork_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMessengerWork_EnsureRegistered();
    }
    return g_beMessengerWork_metaObject;
}

int beMessengerWork_GetVTable(void) {
    beMessengerWork obj;
    int t;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beMessengerWork_vtable[0];
    obj._groupName = 0;
    obj._infoName = 0;
    obj._message = 0;
    obj._findRamNoList = 0;
    obj._findRamList = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beMessengerWork_vtable[0];
    FUN_0033ec00((igObject **)&obj._findRamList, (short)(-1));
    igSmartPointer_igIntList_Destruct(&obj._findRamNoList, -1);
    igStringRef_Destruct(&obj._message, -1);
    igStringRef_Destruct(&obj._infoName, -1);
    igStringRef_Destruct(&obj._groupName, -1);
    return t;
}

void beMessengerWork_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerWork_Register);}

static igMetaObjectCallback g_beMessengerWork_callbackList[] = { igIntList_EnsureRegistered, beBaseInfoRamList_EnsureRegistered, 0 };

void *beMessengerWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMessengerWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMessengerWork_GetMetaObjectFunction,
        "beMessengerWork",
        0x20, /* instance size */
        beMessengerWork_GetVTable,
        beMessengerWork_InitFields,
        0, /* extra callback item */
        g_beMessengerWork_callbackList /* callback list */
    );
}

void beMessengerWork_GetMetaObjectFunction(void)
{
    beMessengerWork_GetMetaObject();
}

static FieldFactory g_beMessengerWork_ctorTable[] = {
    igStringMetaField_Create,
    igStringMetaField_Create,
    igIntMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMessengerWork_fieldTable[] = {
    "_groupName",
    "_infoName",
    "_ramNo",
    "_message",
    "_findRamNoList",
    "_findRamList",
};
static igMetaField **g_beMessengerWork_fieldHandles[] = {
    &g_beMessengerWork_groupNameMetaField,
    &g_beMessengerWork_infoNameMetaField,
    &g_beMessengerWork_ramNoMetaField,
    &g_beMessengerWork_messageMetaField,
    &g_beMessengerWork_findRamNoListMetaField,
    &g_beMessengerWork_findRamListMetaField,
};
static int g_beMessengerWork_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
};

void beMessengerWork_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMessengerWork_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beMessengerWork_ctorTable, 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)beBaseInfoRamList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beMessengerWork_fieldTable, g_beMessengerWork_fieldHandles, g_beMessengerWork_fieldOffsets, temp_s2);
}

