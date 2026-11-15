igMetaObject *g_beMeterCtrlNode_metaObject;
igMetaField *g_beMeterCtrlNode_isMeterMetaField;
igMetaField *g_beMeterCtrlNode_timeListMetaField;
igMetaField *g_beMeterCtrlNode_numberOffsetMetaField;

igMetaObject *FUN_00356cc0(void) {
    if (g_beMeterCtrlNode_metaObject == 0) {
        g_beMeterCtrlNode_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMeterCtrlNode_metaObject;
}

void *beMeterCtrlNode_ResolveMetaObject(void) {
    igMetaObject *g = g_beMeterCtrlNode_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00356de0();
    }
    return g_beMeterCtrlNode_metaObject;
}

int beMeterCtrlNode_GetVTable(void) {
    struct Obj_356d60 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.vt = &DAT_00537120[0];
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00537120[0];
    FUN_00195190(&obj.w9, -1);
    FUN_00195a90(&obj, 0);
    return t;
}

void FUN_00356de0(void)
{
    igMetaObject_RunStaticInit(beMeterCtrlNode_Register);
}

static igMetaObjectCallback g_beMeterCtrlNode_callbackList[] = { igLongList_EnsureRegistered, 0 };

void *beMeterCtrlNode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMeterCtrlNode_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beMeterCtrlNode_GetMetaObject,
        "beMeterCtrlNode",
        0x34, /* instance size */
        beMeterCtrlNode_GetVTable,
        beMeterCtrlNode_InitFields,
        FUN_00356f40, /* extra callback item */
        g_beMeterCtrlNode_callbackList /* callback list */
    );
}

void beMeterCtrlNode_GetMetaObject(void)
{
    beMeterCtrlNode_ResolveMetaObject();
}

static FieldFactory g_beMeterCtrlNode_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    FUN_00187890,
};
static const char *g_beMeterCtrlNode_fieldTable[] = {
    "_isMeter",
    "_timeList",
    "_numberOffset",
};
static igMetaField **g_beMeterCtrlNode_fieldHandles[] = {
    &g_beMeterCtrlNode_isMeterMetaField,
    &g_beMeterCtrlNode_timeListMetaField,
    &g_beMeterCtrlNode_numberOffsetMetaField,
};
static int g_beMeterCtrlNode_fieldOffsets[] = {
    32,
    36,
    40,
};

void beMeterCtrlNode_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMeterCtrlNode_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beMeterCtrlNode_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igLongList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beMeterCtrlNode_fieldTable, g_beMeterCtrlNode_fieldHandles, g_beMeterCtrlNode_fieldOffsets, temp_s2);
}

void FUN_00356f40(void)
{
    beMeterCtrlNode_RegisterTraversalFunction();
}

