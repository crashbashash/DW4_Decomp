igMetaObject *g_beDemoKeepMes_metaObject;
igMetaField *g_beDemoKeepMes_kindMetaField;
igMetaField *g_beDemoKeepMes_sendTimeMetaField;
igMetaField *g_beDemoKeepMes_groupNameMetaField;
igMetaField *g_beDemoKeepMes_infoNameMetaField;
igMetaField *g_beDemoKeepMes_ramNoMetaField;
igMetaField *g_beDemoKeepMes_messageMetaField;
igMetaField *g_beDemoKeepMes_mesParamMetaField;

void beDemoKeepMes_CreateInstance(int arg0) {
    FUN_00363d60();
    igMetaObject_CreateInstance(*(int *)0x5897F8, arg0);
}

igMetaObject *FUN_00363c60(void) {
    igMetaObject *g = g_beDemoKeepMes_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_00363d60();
    return g_beDemoKeepMes_metaObject;
}

int beDemoKeepMes_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00535610[0];
    *(int *)&u.b[24] = 0;
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[36] = 0;
    *(int *)&u.b[40] = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00535610[0];
    igStringRef_Destruct(&u.b[40], -1);
    igStringRef_Destruct(&u.b[36], -1);
    igStringRef_Destruct(&u.b[28], -1);
    igStringRef_Destruct(&u.b[24], -1);
    return r;
}

void FUN_00363d60(void)
{
    igMetaObject_RunStaticInit(beDemoKeepMes_Register);
}

void *beDemoKeepMes_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDemoKeepMes_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beDemoKeepMes_GetMetaObject,
        "beDemoKeepMes",
        0x30, /* instance size */
        beDemoKeepMes_GetVTable,
        beDemoKeepMes_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beDemoKeepMes_GetMetaObject(void)
{
    FUN_00363c60();
}

static FieldFactory g_beDemoKeepMes_ctorTable[] = {
    igIntMetaField_Create,
    igLongMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igIntMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_beDemoKeepMes_fieldTable[] = {
    "_kind",
    "_sendTime",
    "_groupName",
    "_infoName",
    "_ramNo",
    "_message",
    "_mesParam",
};
static igMetaField **g_beDemoKeepMes_fieldHandles[] = {
    &g_beDemoKeepMes_kindMetaField,
    &g_beDemoKeepMes_sendTimeMetaField,
    &g_beDemoKeepMes_groupNameMetaField,
    &g_beDemoKeepMes_infoNameMetaField,
    &g_beDemoKeepMes_ramNoMetaField,
    &g_beDemoKeepMes_messageMetaField,
    &g_beDemoKeepMes_mesParamMetaField,
};
static int g_beDemoKeepMes_fieldOffsets[] = {
    8,
    16,
    24,
    28,
    32,
    36,
    40,
};

void beDemoKeepMes_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beDemoKeepMes_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beDemoKeepMes_ctorTable, 7);
    igMetaObject_NameFields(temp_s0, g_beDemoKeepMes_fieldTable, g_beDemoKeepMes_fieldHandles, g_beDemoKeepMes_fieldOffsets, temp_s1);
}

