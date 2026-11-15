igMetaObject *g_igCollisionGrid_metaObject;
igMetaField *g_igCollisionGrid_cellsMetaField;
igMetaField *g_igCollisionGrid_activeCellsMetaField;
igMetaField *g_igCollisionGrid_processedCellsMetaField;
igMetaField *g_igCollisionGrid_checkedGroupsMetaField;
igMetaField *g_igCollisionGrid_dynamicCollisionsMetaField;
igMetaField *g_igCollisionGrid_staticCollisionsMetaField;
igMetaField *g_igCollisionGrid_lostGroupsMetaField;
igMetaField *g_igCollisionGrid_sizeXMetaField;
igMetaField *g_igCollisionGrid_sizeYMetaField;
igMetaField *g_igCollisionGrid_sizeZMetaField;
igMetaField *g_igCollisionGrid_maxRadiusMetaField;
igMetaField *g_igCollisionGrid_boundMetaField;
igMetaField *g_igCollisionGrid_deltasMetaField;
igMetaField *g_igCollisionGrid_rateMetaField;
igMetaField *g_igCollisionGrid_maxPriorityMetaField;

void FUN_0023a040(int arg0) {
    FUN_0023a340();
    igMetaObject_CreateInstance((int)g_igCollisionGrid_metaObject, arg0);
}

igMetaObject *FUN_0023a080(void) {
    if (g_igCollisionGrid_metaObject == 0) {
        g_igCollisionGrid_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igCollisionGrid_metaObject;
}

igMetaObject *igCollisionGrid_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGrid_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023a340();
    return g_igCollisionGrid_metaObject;
}

int igCollisionGrid_GetVTable(void) {
    union U_23a120 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052d1c0[0];
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[36] = 0;
    *(int *)&u.b[40] = 0;
    *(int *)&u.b[44] = 0;
    *(int *)&u.b[48] = 0;
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0052d1c0[0];
    FUN_00198190(&u.b[56], -1);
    FUN_0023a2c0((void **)&u.b[52], -1);
    FUN_0023a2c0((void **)&u.b[48], -1);
    FUN_0023a2c0((void **)&u.b[44], -1);
    FUN_0023a2c0((void **)&u.b[40], -1);
    FUN_0023a240((void **)&u.b[36], -1);
    FUN_0023a240((void **)&u.b[12], -1);
    FUN_0023a240((void **)&u.b[8], -1);
    return r;
}

void **FUN_0023a240(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_0023a2c0(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_0023a340(void)
{
    igMetaObject_RunStaticInit(igCollisionGrid_Register);
}

static igMetaObjectCallback g_igCollisionGrid_callbackList[] = { FUN_0023a650, FUN_00239b20, FUN_0018a780, 0 };

void igCollisionGrid_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCollisionGrid_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCollisionGrid_GetMetaObject,
        "igCollisionGrid",
        0x4C, /* instance size */
        igCollisionGrid_GetVTable,
        &igCollisionGrid_InitFields,
        0, /* extra callback item */
        g_igCollisionGrid_callbackList /* callback list */
    );
}

void thunk_igCollisionGrid_GetMetaObject(void) {
    igCollisionGrid_GetMetaObject();
}

static FieldFactory g_igCollisionGrid_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igObjectRefMetaField_Create,
    FUN_00187890,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_igCollisionGrid_fieldTable[] = {
    "_cells",
    "_activeCells",
    "_processedCells",
    "_checkedGroups",
    "_dynamicCollisions",
    "_staticCollisions",
    "_lostGroups",
    "_sizeX",
    "_sizeY",
    "_sizeZ",
    "_maxRadius",
    "_bound",
    "_deltas",
    "_rate",
    "_maxPriority",
};
static igMetaField **g_igCollisionGrid_fieldHandles[] = {
    &g_igCollisionGrid_cellsMetaField,
    &g_igCollisionGrid_activeCellsMetaField,
    &g_igCollisionGrid_processedCellsMetaField,
    &g_igCollisionGrid_checkedGroupsMetaField,
    &g_igCollisionGrid_dynamicCollisionsMetaField,
    &g_igCollisionGrid_staticCollisionsMetaField,
    &g_igCollisionGrid_lostGroupsMetaField,
    &g_igCollisionGrid_sizeXMetaField,
    &g_igCollisionGrid_sizeYMetaField,
    &g_igCollisionGrid_sizeZMetaField,
    &g_igCollisionGrid_maxRadiusMetaField,
    &g_igCollisionGrid_boundMetaField,
    &g_igCollisionGrid_deltasMetaField,
    &g_igCollisionGrid_rateMetaField,
    &g_igCollisionGrid_maxPriorityMetaField,
};
static int g_igCollisionGrid_fieldOffsets[] = {
    8,
    12,
    36,
    40,
    44,
    48,
    52,
    16,
    20,
    24,
    28,
    56,
    60,
    72,
    32,
};

void igCollisionGrid_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    igMetaObject *temp_s0;

    temp_s0 = g_igCollisionGrid_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igCollisionGrid_ctorTable, 0xF);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0023a570();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_0023a570();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_0023a570();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_00239a40();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_00239a40();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_00239a40();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)FUN_00239a40();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_0018a6a0();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD), 1);
    igMetaObject_NameFields(temp_s0, g_igCollisionGrid_fieldTable, g_igCollisionGrid_fieldHandles, g_igCollisionGrid_fieldOffsets, temp_s1);
}

