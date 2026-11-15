igMetaObject *g_beBaseInfoRam_metaObject;
igMetaField *g_beBaseInfoRam_ramNoMetaField;
igMetaField *g_beBaseInfoRam_parentInfoMetaField;
igMetaField *g_beBaseInfoRam_parentManagerMetaField;
igMetaField *g_beBaseInfoRam_isRunMetaField;
igMetaField *g_beBaseInfoRam_st0MetaField;
igMetaField *g_beBaseInfoRam_st1MetaField;
igMetaField *g_beBaseInfoRam_st2MetaField;
igMetaField *g_beBaseInfoRam_st3MetaField;
igMetaField *g_beBaseInfoRam_dataListMetaField;

igMetaObject *FUN_0036a230(void) {
    if (g_beBaseInfoRam_metaObject == 0) {
        g_beBaseInfoRam_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beBaseInfoRam_metaObject;
}

void *FUN_0036a280(void) {
    igMetaObject *g = g_beBaseInfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0036a360();
    }
    return g_beBaseInfoRam_metaObject;
}

int beBaseInfoRam_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader(u.b);
    p = (S_ref *)&u.b[40];
    u.vt = (int)&DAT_00539e90[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00539e90[0];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return temp_s0;
}

void FUN_0036a360(void)
{
    igMetaObject_RunStaticInit(beBaseInfoRam_Register);
}

static igMetaObjectCallback g_beBaseInfoRam_callbackList[] = { FUN_0036ad20, FUN_0036a970, FUN_0036afa0, 0 };

void *beBaseInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beBaseInfoRam_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beBaseInfoRam_GetMetaObject,
        "beBaseInfoRam",
        0x2c, /* instance size */
        beBaseInfoRam_GetVTable,
        beBaseInfoRam_InitFields,
        0, /* extra callback item */
        g_beBaseInfoRam_callbackList /* callback list */
    );
}

void beBaseInfoRam_GetMetaObject(void)
{
    FUN_0036a280();
}

static FieldFactory g_beBaseInfoRam_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beBaseInfoRam_fieldTable[] = {
    "_ramNo",
    "_parentInfo",
    "_parentManager",
    "_isRun",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
    "_dataList",
};
static igMetaField **g_beBaseInfoRam_fieldHandles[] = {
    &g_beBaseInfoRam_ramNoMetaField,
    &g_beBaseInfoRam_parentInfoMetaField,
    &g_beBaseInfoRam_parentManagerMetaField,
    &g_beBaseInfoRam_isRunMetaField,
    &g_beBaseInfoRam_st0MetaField,
    &g_beBaseInfoRam_st1MetaField,
    &g_beBaseInfoRam_st2MetaField,
    &g_beBaseInfoRam_st3MetaField,
    &g_beBaseInfoRam_dataListMetaField,
};
static int g_beBaseInfoRam_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
};

void beBaseInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beBaseInfoRam_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beBaseInfoRam_ctorTable, 9);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0036ac80();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0036a8d0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0036aec0();
    igMetaObject_NameFields(temp_s0, g_beBaseInfoRam_fieldTable, g_beBaseInfoRam_fieldHandles, g_beBaseInfoRam_fieldOffsets, temp_s2);
}

