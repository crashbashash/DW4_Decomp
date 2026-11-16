igMetaObject *g_igBillboard_metaObject;
igMetaField *g_igBillboard_modeMetaField;
igMetaField *g_igBillboard_axisMetaField;
igMetaField *g_igBillboard_originMetaField;
igMetaField *g_igBillboard_mvmMetaField;

igMetaObject *igBillboard_GetMetaObject(void)
{
    igMetaObject *g = g_igBillboard_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBillboard_EnsureRegistered();
    return g_igBillboard_metaObject;
}

int igBillboard_GetVTable(void) {
    union U_1a4fd0 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[3] = 0;
    u.w[4] = 0;
    u.w[7] = 0;
    u.w[0] = (int)(&g_igBillboard_vtable[0]);
    u.w[15] = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_igBillboard_vtable[0]);
    FUN_00142d10(&u.w[15], -1);
    FUN_00195a90((struct T_195a90 *)&u.w[0], 0);
    return temp_s0;
}

void igBillboard_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBillboard_Register);
}

static igMetaObjectCallback g_igBillboard_callbackList[] = { igModelViewMatrixAttr_EnsureRegistered, 0 };

void igBillboard_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBillboard_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igBillboard_GetMetaObject,
        "igBillboard",
        0x40, /* instance size */
        igBillboard_GetVTable,
        &igBillboard_InitFields,
        0, /* extra callback item */
        g_igBillboard_callbackList /* callback list */
    );
}

void thunk_igBillboard_GetMetaObject(void) {
    igBillboard_GetMetaObject();
}

static FieldFactory g_igBillboard_ctorTable[] = {
    igIntMetaField_Create,
    FUN_00187890,
    FUN_00187890,
    igObjectRefMetaField_Create,
};
static const char *g_igBillboard_fieldTable[] = {
    "_mode",
    "_axis",
    "_origin",
    "_mvm",
};
static igMetaField **g_igBillboard_fieldHandles[] = {
    &g_igBillboard_modeMetaField,
    &g_igBillboard_axisMetaField,
    &g_igBillboard_originMetaField,
    &g_igBillboard_mvmMetaField,
};
static int g_igBillboard_fieldOffsets[] = {
    32,
    36,
    48,
    60,
};

void igBillboard_InitFields(void) {
    float spA[4];
    float spB[4];
    int temp_s2;
    void *temp_s1;
    void *temp_a0_2;
    void *temp_a0;
    void *temp_s0;

    temp_s0 = (void *)g_igBillboard_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igBillboard_ctorTable, 4);
    temp_a0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    spA[0] = 0;
    spA[2] = 1.0f;
    spA[1] = 0;
    FUN_0018e470(temp_a0, spA);
    temp_a0_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2)));
    spB[0] = 0;
    spB[1] = 0;
    spB[2] = 0;
    FUN_0018e470(temp_a0_2, spB);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3)));
    *(int *)((char *)(temp_s1) + 56) = FUN_001356f0();
    *(char *)((char *)(temp_s1) + 38) = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igBillboard_fieldTable, g_igBillboard_fieldHandles, g_igBillboard_fieldOffsets, temp_s2);
}

