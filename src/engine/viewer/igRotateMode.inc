static const char *g_igRotateMode_CONSTRAINT_AXISNames[] = {
    "NONE", "CONSTRAINT_X", "CONSTRAINT_Y",
};
static int g_igRotateMode_CONSTRAINT_AXISValues[] = {
    0, 1, 2,
};
igMetaEnum *g_igRotateMode_CONSTRAINT_AXISMetaEnum;
igMetaObject *g_igRotateMode_metaObject;
igMetaField *g_igRotateMode_distanceMetaField;
igMetaField *g_igRotateMode_lastMousePosMetaField;
igMetaField *g_igRotateMode_leftMouseActiveMetaField;
igMetaField *g_igRotateMode_middleMouseActiveMetaField;
igMetaField *g_igRotateMode_rightMouseActiveMetaField;
igMetaField *g_igRotateMode_joystickTMetaField;
igMetaField *g_igRotateMode_joystickRMetaField;
igMetaField *g_igRotateMode_constraintMetaField;
igMetaField *g_igRotateMode_constraintAxisMetaField;
igMetaField *g_igRotateMode_activeMetaField;
igMetaField *g_igRotateMode_mayaMetaField;
igMetaField *g_igRotateMode_headMetaField;
igMetaField *g_igRotateMode_rollMetaField;
igMetaField *g_igRotateMode_pitchMetaField;
igMetaField *g_igRotateMode_zoomMetaField;
igMetaField *g_igRotateMode_translationMetaField;

igMetaEnum *FUN_0045c540(void) {
    if (g_igRotateMode_CONSTRAINT_AXISMetaEnum == 0) {
        g_igRotateMode_CONSTRAINT_AXISMetaEnum = igMetaEnum_Create("CONSTRAINT_AXIS", g_igRotateMode_CONSTRAINT_AXISNames, g_igRotateMode_CONSTRAINT_AXISValues, 3);
    }
    return g_igRotateMode_CONSTRAINT_AXISMetaEnum;
}

igRotateMode *igRotateMode_Create(int allocator) {
    FUN_0045c680();
    return (igRotateMode *)igMetaObject_CreateInstance(g_igRotateMode_metaObject, allocator);
}

void *igRotateMode_GetMetaObject(void) {
    bool ok;
    if (((S_45c5e0 *)g_igRotateMode_metaObject) == 0) goto make;
    ok = !!(((S_45c5e0 *)g_igRotateMode_metaObject)->f & 4);
    if (ok != false) goto done;
make:
    FUN_0045c680();
done:;
    return ((S_45c5e0 *)g_igRotateMode_metaObject);
}

int igRotateMode_GetVTable(void) {
    union U_45c630 u;
    igObject_InitHeader(u.b);
    u.vt = (int)&g_igViewMode_vtable[0];
    igMatrix44f_SetIdentity(&u.b[12]);
    u.vt = (int)&g_igRotateMode_vtable[0];
    return *(int *)&u.b[*(int *)((char *)((void *)g_objectSystem[0]) + 916)];
}

void FUN_0045c680(void)
{
    igMetaObject_RunStaticInit(igRotateMode_Register);
}

void igRotateMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRotateMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        thunk_igRotateMode_GetMetaObject,
        "igRotateMode",
        0x94, /* instance size */
        igRotateMode_GetVTable,
        &igRotateMode_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igRotateMode_GetMetaObject(void) {
    igRotateMode_GetMetaObject();
}

static FieldFactory g_igRotateMode_ctorTable[] = {
    igFloatMetaField_Create,
    igVec2fMetaField_CreateInstance,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igVec2fMetaField_CreateInstance,
    igVec2fMetaField_CreateInstance,
    igBoolMetaField_Create,
    igEnumMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igVec3fMetaField_CreateInstance,
};
static const char *g_igRotateMode_fieldTable[] = {
    "_distance",
    "_lastMousePos",
    "_leftMouseActive",
    "_middleMouseActive",
    "_rightMouseActive",
    "_joystickT",
    "_joystickR",
    "_constraint",
    "_constraintAxis",
    "_active",
    "_maya",
    "_head",
    "_roll",
    "_pitch",
    "_zoom",
    "_translation",
};
static igMetaField **g_igRotateMode_fieldHandles[] = {
    &g_igRotateMode_distanceMetaField,
    &g_igRotateMode_lastMousePosMetaField,
    &g_igRotateMode_leftMouseActiveMetaField,
    &g_igRotateMode_middleMouseActiveMetaField,
    &g_igRotateMode_rightMouseActiveMetaField,
    &g_igRotateMode_joystickTMetaField,
    &g_igRotateMode_joystickRMetaField,
    &g_igRotateMode_constraintMetaField,
    &g_igRotateMode_constraintAxisMetaField,
    &g_igRotateMode_activeMetaField,
    &g_igRotateMode_mayaMetaField,
    &g_igRotateMode_headMetaField,
    &g_igRotateMode_rollMetaField,
    &g_igRotateMode_pitchMetaField,
    &g_igRotateMode_zoomMetaField,
    &g_igRotateMode_translationMetaField,
};
static int g_igRotateMode_fieldOffsets[] = {
    76,
    80,
    88,
    89,
    90,
    92,
    100,
    108,
    112,
    116,
    117,
    120,
    124,
    128,
    132,
    136,
};

void igRotateMode_InitFields(void) {
    int temp_s2;
    int spA[2];
    int spB[2];
    int spC[2];
    int spD[3];
    void *temp_v0;
    void *temp_a0_4;
    void *temp_a0_3;
    void *temp_a0_2;
    void *temp_a0;
    void *temp_s0;

    temp_s0 = g_igRotateMode_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igRotateMode_ctorTable, 0x10);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2), 1.0f);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    spA[0] = 0;
    spA[1] = 0;
    igVec2fMetaField_SetDefault(temp_a0, spA);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    spB[0] = 0;
    spB[1] = 0;
    igVec2fMetaField_SetDefault(temp_a0_2, spB);
    temp_a0_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    spC[0] = 0;
    spC[1] = 0;
    igVec2fMetaField_SetDefault(temp_a0_3, spC);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    igEnumMetaField_SetDefaultValue(temp_v0, 0);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_0045c540);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9), 1);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xB), 0.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC), 0.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xD), 0.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xE), 1.0f);
    temp_a0_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xF));
    spD[0] = 0;
    spD[1] = 0;
    spD[2] = 0;
    igVec3fMetaField_SetDefault(temp_a0_4, spD);
    igMetaObject_NameFields(temp_s0, g_igRotateMode_fieldTable, g_igRotateMode_fieldHandles, g_igRotateMode_fieldOffsets, temp_s2);
}

