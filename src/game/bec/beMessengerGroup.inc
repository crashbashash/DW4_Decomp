igMetaObject *g_beMessengerGroup_metaObject;
igMetaField *g_beMessengerGroup_infoNameListMetaField;
igMetaField *g_beMessengerGroup_ramNoListMetaField;
igMetaField *g_beMessengerGroup_ramListMetaField;

void *beMessengerGroup_Create(void *allocator){beMessengerGroup_EnsureRegistered();return ((void *)igMetaObject_CreateInstance((void *)g_beMessengerGroup_metaObject,allocator));}

void *beMessengerGroup_GetMetaObject(void) {
    igMetaObject *g = g_beMessengerGroup_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMessengerGroup_EnsureRegistered();
    }
    return g_beMessengerGroup_metaObject;
}

int beMessengerGroup_GetVTable(void) {
    struct Obj_358570 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &g_beMessengerGroup_vtable[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beMessengerGroup_vtable[0];
    FUN_0033ec00((igObject **)&obj.w5, (short)(-1));
    igSmartPointer_igIntList_Destruct(&obj.w4, -1);
    igSmartPointer_igStringRefList_Destruct(&obj.w3, -1);
    FUN_00131bc0(&obj, 0);
    return t;
}

void beMessengerGroup_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerGroup_Register);}

static igMetaObjectCallback g_beMessengerGroup_callbackList[] = { igStringRefList_EnsureRegistered, igIntList_EnsureRegistered, beBaseInfoRamList_EnsureRegistered, 0 };

void *beMessengerGroup_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMessengerGroup_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beMessengerGroup_GetMetaObjectFunction,
        "beMessengerGroup",
        0x18, /* instance size */
        beMessengerGroup_GetVTable,
        beMessengerGroup_InitFields,
        0, /* extra callback item */
        g_beMessengerGroup_callbackList /* callback list */
    );
}

void beMessengerGroup_GetMetaObjectFunction(void)
{
    beMessengerGroup_GetMetaObject();
}

static FieldFactory g_beMessengerGroup_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMessengerGroup_fieldTable[] = {
    "_infoNameList",
    "_ramNoList",
    "_ramList",
};
static igMetaField **g_beMessengerGroup_fieldHandles[] = {
    &g_beMessengerGroup_infoNameListMetaField,
    &g_beMessengerGroup_ramNoListMetaField,
    &g_beMessengerGroup_ramListMetaField,
};
static int g_beMessengerGroup_fieldOffsets[] = {
    12,
    16,
    20,
};

void beMessengerGroup_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMessengerGroup_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beMessengerGroup_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)beBaseInfoRamList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beMessengerGroup_fieldTable, g_beMessengerGroup_fieldHandles, g_beMessengerGroup_fieldOffsets, temp_s2);
}

