void igGroup_CreateInstance(int arg0) {
    FUN_0019f330();
    igMetaObject_CreateInstance((int)g_igGroup_metaObject, arg0);
}

igMetaObject *FUN_0019f210(void) {
    if (g_igGroup_metaObject == 0) {
        g_igGroup_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igGroup_metaObject;
}

igMetaObject *igGroup_GetMetaObject(void)
{
    igMetaObject *g = g_igGroup_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019f330();
    return g_igGroup_metaObject;
}

int igGroup_GetVTable(void) {
    struct Obj_19f2b0 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.fC = 0;
    obj.f10 = 0;
    obj.vt = (&DAT_00528dd0[0]);
    obj.f1C = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&DAT_00528dd0[0]);
    FUN_001958f0((void * *)&obj.f1C, -1);
    FUN_00195970((struct T_195970 *)&obj, 0);
    return temp_s0;
}

void FUN_0019f330(void)
{
    igMetaObject_RunStaticInit(igGroup_Register);
}

static igMetaObjectCallback g_igGroup_callbackList[] = { FUN_0019ccc0, 0 };

void igGroup_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGroup_metaObject,
        igNode_Register,
        igNode_GetPublishedMetaObject,
        thunk_igGroup_GetMetaObject,
        "igGroup",
        0x20, /* instance size */
        igGroup_GetVTable,
        &igGroup_InitFields,
        0, /* extra callback item */
        g_igGroup_callbackList /* callback list */
    );
}

void thunk_igGroup_GetMetaObject(void) {
    igGroup_GetMetaObject();
}

static FieldFactory g_igGroup_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igGroup_fieldTable[] = {
    "_childList",
};
static igMetaField **g_igGroup_fieldHandles[] = {
    &g_igGroup_childListMetaField,
};
static int g_igGroup_fieldOffsets[] = {
    28,
};

void igGroup_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igGroup_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igGroup_ctorTable, 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0019cbe0();
    ((igMetaField *)temp_s1)->_resetMethod = 3;
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 2;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igGroup_fieldTable, g_igGroup_fieldHandles, g_igGroup_fieldOffsets, temp_s2);
}

