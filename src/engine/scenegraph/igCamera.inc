void igCamera_CreateInstance(int arg0) {
    igCamera_EnsureRegistered();
    igMetaObject_CreateInstance((int)g_igCamera_metaObject, arg0);
}

igMetaObject *g_igCamera_metaObject;
igMetaField *g_igCamera_cameraTypeMetaField;
igMetaField *g_igCamera_horizontalFieldOfViewMetaField;
igMetaField *g_igCamera_nearPlaneMetaField;
igMetaField *g_igCamera_farPlaneMetaField;
igMetaField *g_igCamera_deadfield1MetaField;
igMetaField *g_igCamera_deadfield2MetaField;
igMetaField *g_igCamera_deadfield3MetaField;

igMetaObject *igCamera_GetOrCreateMetaObject(void) {
    if (g_igCamera_metaObject == 0) {
        g_igCamera_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igCamera_metaObject;
}

igMetaObject *igCamera_GetMetaObject(void)
{
    igMetaObject *g = g_igCamera_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCamera_EnsureRegistered();
    return g_igCamera_metaObject;
}

int igCamera_GetVTable(void) {
    Obj_1a4600 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[2] = 0;
    o.w[3] = 0;
    o.vt = &g_igCamera_vtable[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_igCamera_vtable[0];
    igNode_Destroy((struct T_195970 *)&o, 0);
    return r;
}

void igCamera_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCamera_Register);
}

void igCamera_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCamera_metaObject,
        igNode_Register,
        igNode_GetPublishedMetaObject,
        thunk_igCamera_GetMetaObject,
        "igCamera",
        0x38, /* instance size */
        igCamera_GetVTable,
        &igCamera_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igCamera_GetMetaObject(void) {
    igCamera_GetMetaObject();
}

static FieldFactory g_igCamera_ctorTable[] = {
    igEnumMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_igCamera_fieldTable[] = {
    "_cameraType",
    "_horizontalFieldOfView",
    "_nearPlane",
    "_farPlane",
    "_deadfield1",
    "_deadfield2",
    "_deadfield3",
};
static igMetaField **g_igCamera_fieldHandles[] = {
    &g_igCamera_cameraTypeMetaField,
    &g_igCamera_horizontalFieldOfViewMetaField,
    &g_igCamera_nearPlaneMetaField,
    &g_igCamera_farPlaneMetaField,
    &g_igCamera_deadfield1MetaField,
    &g_igCamera_deadfield2MetaField,
    &g_igCamera_deadfield3MetaField,
};
static int g_igCamera_fieldOffsets[] = {
    28,
    44,
    48,
    52,
    32,
    36,
    40,
};

void igCamera_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)g_igCamera_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igCamera_ctorTable, 7);
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    igEnumMetaField_SetDefaultValue(temp_v0, 0);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_001a47d0);
    igFloatMetaField_SetDefault(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)), 45.0f);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igCamera_fieldTable, g_igCamera_fieldHandles, g_igCamera_fieldOffsets, temp_s2);
}

static const char *g_igCamera_cameraTypeNames[] = {
    "CameraPoint", "CameraTarget",
};
static int g_igCamera_cameraTypeValues[] = {
    0, 1,
};
igMetaEnum *g_igCamera_cameraTypeMetaEnum;

igMetaEnum *FUN_001a47d0(void) {
    if (g_igCamera_cameraTypeMetaEnum == 0) {
        g_igCamera_cameraTypeMetaEnum = igMetaEnum_Create("CameraType", g_igCamera_cameraTypeNames, g_igCamera_cameraTypeValues, 2);
    }
    return g_igCamera_cameraTypeMetaEnum;
}

