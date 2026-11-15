igMetaObject *g_igCollisionGroup_metaObject;
igMetaField *g_igCollisionGroup_transformMetaField;
igMetaField *g_igCollisionGroup_positionMetaField;
igMetaField *g_igCollisionGroup_lastPositionMetaField;
igMetaField *g_igCollisionGroup_collisionPositionMetaField;
igMetaField *g_igCollisionGroup_directionMetaField;
igMetaField *g_igCollisionGroup_radiusMetaField;
igMetaField *g_igCollisionGroup_timeMetaField;
igMetaField *g_igCollisionGroup_collisionCellsMetaField;

igMetaObject *igCollisionGroup_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGroup_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239c80();
    return g_igCollisionGroup_metaObject;
}

int igCollisionGroup_GetVTable(void) {
    union U_239c00 u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[28] = 0;
    u.vt = (int)&DAT_0052d3c0[0];
    p = (int *)&u.b[32];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0052d3c0[0];
    FUN_001a7580(p, -1);
    FUN_00195a90(u.b, 0);
    return temp_s0;
}

void FUN_00239c80(void)
{
    igMetaObject_RunStaticInit(igCollisionGroup_Register);
}

static igMetaObjectCallback g_igCollisionGroup_callbackList[] = { FUN_001964d0, 0 };

void igCollisionGroup_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCollisionGroup_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igCollisionGroup_GetMetaObject,
        "igCollisionGroup",
        0x60, /* instance size */
        igCollisionGroup_GetVTable,
        &igCollisionGroup_InitFields,
        0, /* extra callback item */
        g_igCollisionGroup_callbackList /* callback list */
    );
}

void thunk_igCollisionGroup_GetMetaObject(void) {
    igCollisionGroup_GetMetaObject();
}

static FieldFactory g_igCollisionGroup_ctorTable[] = {
    igObjectRefMetaField_Create,
    FUN_00187890,
    FUN_00187890,
    FUN_00187890,
    FUN_00187890,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_igCollisionGroup_fieldTable[] = {
    "_transform",
    "_position",
    "_lastPosition",
    "_collisionPosition",
    "_direction",
    "_radius",
    "_time",
    "_collisionCells",
};
static igMetaField **g_igCollisionGroup_fieldHandles[] = {
    &g_igCollisionGroup_transformMetaField,
    &g_igCollisionGroup_positionMetaField,
    &g_igCollisionGroup_lastPositionMetaField,
    &g_igCollisionGroup_collisionPositionMetaField,
    &g_igCollisionGroup_directionMetaField,
    &g_igCollisionGroup_radiusMetaField,
    &g_igCollisionGroup_timeMetaField,
    &g_igCollisionGroup_collisionCellsMetaField,
};
static int g_igCollisionGroup_fieldOffsets[] = {
    32,
    36,
    48,
    60,
    72,
    84,
    88,
    92,
};

void igCollisionGroup_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igCollisionGroup_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igCollisionGroup_ctorTable, 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196190();
    igMetaObject_NameFields(temp_s0, g_igCollisionGroup_fieldTable, g_igCollisionGroup_fieldHandles, g_igCollisionGroup_fieldOffsets, temp_s2);
}

