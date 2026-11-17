igMetaObject *g_igRay_metaObject;
igMetaField *g_igRay_posMetaField;
igMetaField *g_igRay_dirMetaField;
igMetaField *g_igRay_lenMetaField;

void igRay_CreateInstance(int arg0) {
    igRay_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)g_igRay_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *FUN_00188260(void) {
    if (g_igRay_metaObject == 0) {
        g_igRay_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRay_metaObject;
}

igMetaObject *igRay_GetMetaObject(void)
{
    igMetaObject *g = g_igRay_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRay_EnsureRegistered();
    return g_igRay_metaObject;
}

int igRay_GetVTable(void) {
    struct Obj7 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igRay_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void igRay_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRay_Register);
}

CallbackArray *igRay_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRay_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRay_GetMetaObject,
        "igRay",
        0x24, /* instance size */
        igRay_GetVTable,
        &igRay_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igRay_GetMetaObject(void) {
    igRay_GetMetaObject();
}

static FieldFactory g_igRay_ctorTable[] = {
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igFloatMetaField_Create,
};

static const char *g_igRay_fieldTable[] = {
    "_pos",
    "_dir",
    "_len",
};

static igMetaField **g_igRay_fieldHandles[] = {
    &g_igRay_posMetaField,
    &g_igRay_dirMetaField,
    &g_igRay_lenMetaField,
};

static int g_igRay_fieldOffsets[] = {
    8,
    20,
    32,
};

void igRay_InitFields(void) {
    int temp_s1;
    void *temp_s0;
    int temp_a0_2;
    int temp_a0;
    int sp40[4];
    int sp30[4];

    temp_s0 = (void *)g_igRay_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (FieldFactory *)g_igRay_ctorTable, 3);
    temp_a0 = (int)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1);
    sp40[0] = 0;
    sp40[1] = 0;
    sp40[2] = 0;
    igVec3fMetaField_SetDefault((igMetaField *)temp_a0, (const float *)&sp40[0]);
    temp_a0_2 = (int)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1);
    sp30[0] = 0;
    sp30[1] = 0x3F800000;
    sp30[2] = 0;
    igVec3fMetaField_SetDefault((igMetaField *)temp_a0_2, (const float *)&sp30[0]);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)g_igRay_fieldTable, (igMetaField ***)g_igRay_fieldHandles, (int *)g_igRay_fieldOffsets, temp_s1);
}

