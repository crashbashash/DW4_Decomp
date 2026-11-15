igMetaObject *g_beMatCtrlInfoWork_metaObject;
igMetaField *g_beMatCtrlInfoWork_runFlagListMetaField;
igMetaField *g_beMatCtrlInfoWork_matOnPlListsMetaField;

void FUN_00359480(int arg0) {
    FUN_00359640();
    igMetaObject_CreateInstance(*(int *)0x5890C0, arg0);
}

igMetaObject *FUN_003594c0(void) {
    if (g_beMatCtrlInfoWork_metaObject == 0) {
        g_beMatCtrlInfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMatCtrlInfoWork_metaObject;
}

void *FUN_00359510(void) {
    igMetaObject *g = g_beMatCtrlInfoWork_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00359640();
    }
    return g_beMatCtrlInfoWork_metaObject;
}

int beMatCtrlInfoWork_GetVTable(void) {
    Obj_359560 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536c40[0];
    obj.m8 = 0;
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00536c40[0];
    obj.rel12();
    obj.rel8();
    return r;
}

void FUN_00359640(void)
{
    igMetaObject_RunStaticInit(beMatCtrlInfoWork_Register);
}

static igMetaObjectCallback g_beMatCtrlInfoWork_callbackList[] = { igBoolList_EnsureRegistered, igIntListList_EnsureRegistered, 0 };

void *beMatCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMatCtrlInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMatCtrlInfoWork_GetMetaObject,
        "beMatCtrlInfoWork",
        0x10, /* instance size */
        beMatCtrlInfoWork_GetVTable,
        beMatCtrlInfoWork_InitFields,
        0, /* extra callback item */
        g_beMatCtrlInfoWork_callbackList /* callback list */
    );
}

void beMatCtrlInfoWork_GetMetaObject(void)
{
    FUN_00359510();
}

static FieldFactory g_beMatCtrlInfoWork_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMatCtrlInfoWork_fieldTable[] = {
    "_runFlagList",
    "_matOnPlLists",
};
static igMetaField **g_beMatCtrlInfoWork_fieldHandles[] = {
    &g_beMatCtrlInfoWork_runFlagListMetaField,
    &g_beMatCtrlInfoWork_matOnPlListsMetaField,
};
static int g_beMatCtrlInfoWork_fieldOffsets[] = {
    8,
    12,
};

void beMatCtrlInfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMatCtrlInfoWork_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beMatCtrlInfoWork_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igBoolList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntListList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beMatCtrlInfoWork_fieldTable, g_beMatCtrlInfoWork_fieldHandles, g_beMatCtrlInfoWork_fieldOffsets, temp_s2);
}

