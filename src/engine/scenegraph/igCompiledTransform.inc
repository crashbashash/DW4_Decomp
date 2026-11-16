int FUN_001a3590(int arg0) {
    FUN_001a3700();
    return (int)igMetaObject_CreateInstance((igMetaObject *)g_igCompiledTransform_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *g_igCompiledTransform_metaObject;
igMetaField *g_igCompiledTransform_parentIdxMetaField;
igMetaField *g_igCompiledTransform_sourceMetaField;
igMetaField *g_igCompiledTransform_moIdxMetaField;
igMetaField *g_igCompiledTransform_invJointMetaField;
igMetaField *g_igCompiledTransform_nameMetaField;
igMetaField *g_igCompiledTransform_isNodeMetaField;
igMetaField *g_igCompiledTransform_isJointChainStartMetaField;
igMetaField *g_igCompiledTransform_boneIndexMetaField;

igMetaObject *igCompiledTransform_GetMetaObject(void)
{
    igMetaObject *g = g_igCompiledTransform_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a3700();
    return g_igCompiledTransform_metaObject;
}

int igCompiledTransform_GetVTable(void) {
    union U_1a3620 u;
    int temp_s1;
    void **q1;
    void **q2;
    struct Rc *temp_a0;
    struct Rc *temp_a0_2;

    igObject_InitHeader((igObject *)u.b);
    q1 = &u.p[3];
    q2 = &u.p[6];
    u.w[0] = (int)(&g_igCompiledTransform_vtable[0]);
    *q1 = 0;
    *q2 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
    u.w[0] = (int)(&g_igCompiledTransform_vtable[0]);
    if (q2 != 0) {
        temp_a0 = (struct Rc *)*q2;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
    }
    if (q1 != 0) {
        temp_a0_2 = (struct Rc *)*q1;
        if (temp_a0_2 != 0) {
            temp_a0_2->rc = temp_a0_2->rc - 1;
            if ((temp_a0_2->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0_2);
            }
        }
    }
    return temp_s1;
}

void FUN_001a3700(void)
{
    igMetaObject_RunStaticInit(igCompiledTransform_Register);
}

static igMetaObjectCallback g_igCompiledTransform_callbackList[] = { FUN_00194e70, igStringObj_EnsureRegistered, 0 };

CallbackArray *igCompiledTransform_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCompiledTransform_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCompiledTransform_GetMetaObject,
        "igCompiledTransform",
        0x24, /* instance size */
        igCompiledTransform_GetVTable,
        &igCompiledTransform_InitFields,
        0, /* extra callback item */
        g_igCompiledTransform_callbackList /* callback list */
    );
}

void thunk_igCompiledTransform_GetMetaObject(void) {
    igCompiledTransform_GetMetaObject();
}

static FieldFactory g_igCompiledTransform_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igCompiledTransform_fieldTable[] = {
    "_parentIdx",
    "_source",
    "_moIdx",
    "_invJoint",
    "_name",
    "_isNode",
    "_isJointChainStart",
    "_boneIndex",
};
static igMetaField **g_igCompiledTransform_fieldHandles[] = {
    &g_igCompiledTransform_parentIdxMetaField,
    &g_igCompiledTransform_sourceMetaField,
    &g_igCompiledTransform_moIdxMetaField,
    &g_igCompiledTransform_invJointMetaField,
    &g_igCompiledTransform_nameMetaField,
    &g_igCompiledTransform_isNodeMetaField,
    &g_igCompiledTransform_isJointChainStartMetaField,
    &g_igCompiledTransform_boneIndexMetaField,
};
static int g_igCompiledTransform_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    29,
    32,
};

void igCompiledTransform_InitFields(void) {
    int temp_s2;
    struct Fld_1a37a0 *temp_v0_2;
    struct Fld_1a37a0 *temp_v0;
    struct Fld_1a37a0 *temp_s1_2;
    struct Fld_1a37a0 *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igCompiledTransform_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igCompiledTransform_ctorTable, 8);
    ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2))->f38 = 0;
    temp_s1 = ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    temp_s1->f56 = (int)FUN_00194dd0();
    temp_s1->f38 = 0;
    temp_v0 = ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2));
    igIntMetaField_SetDefault(temp_v0, -1);
    temp_v0->f38 = 0;
    ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3))->f38 = 0;
    temp_s1_2 = ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 4));
    temp_s1_2->f56 = igStringObj_GetOrCreateMetaObject();
    temp_s1_2->f52 = 1;
    temp_s1_2->f38 = 0;
    temp_v0_2 = ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 5));
    igBoolMetaField_SetDefaultValue(temp_v0_2, 1);
    temp_v0_2->f38 = 0;
    ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 6))->f38 = 0;
    ((struct Fld_1a37a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 7))->f38 = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igCompiledTransform_fieldTable, g_igCompiledTransform_fieldHandles, g_igCompiledTransform_fieldOffsets, temp_s2);
}

