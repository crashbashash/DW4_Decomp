igMetaObject *g_igSphere_metaObject;
igMetaField *g_igSphere_centerMetaField;
igMetaField *g_igSphere_radiusMetaField;

void FUN_00187e10(int arg0) {
    FUN_00187f30();
    igMetaObject_CreateInstance((igMetaObject *)g_igSphere_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *FUN_00187e50(void) {
    if (g_igSphere_metaObject == 0) {
        g_igSphere_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igSphere_metaObject;
}

igMetaObject *igSphere_GetMetaObject(void)
{
    igMetaObject *g = g_igSphere_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00187f30();
    return g_igSphere_metaObject;
}

int igSphere_GetVTable(void) {
    union U2 u;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igSphere_vtable[0];
    return *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
}

void FUN_00187f30(void)
{
    igMetaObject_RunStaticInit(igSphere_Register);
}

CallbackArray *igSphere_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSphere_metaObject,
        igVolume_Register,
        (igMetaObjectGetFunction)igVolume_GetPublishedMetaObject,
        thunk_igSphere_GetMetaObject,
        "igSphere",
        0x18, /* instance size */
        igSphere_GetVTable,
        &igSphere_InitFields,
        thunk_FUN_0018d480, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igSphere_GetMetaObject(void) {
    igSphere_GetMetaObject();
}

igMetaObject *FUN_00187fd0(void) {
    return g_igVolume_metaObject;
}

static FieldFactory g_igSphere_ctorTable[] = {
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igFloatMetaField_Create,
};

static const char *g_igSphere_fieldTable[] = {
    "_center",
    "_radius",
};

static igMetaField **g_igSphere_fieldHandles[] = {
    &g_igSphere_centerMetaField,
    &g_igSphere_radiusMetaField,
};

static int g_igSphere_fieldOffsets[] = {
    8,
    20,
};

void igSphere_InitFields(void) {
    int temp_s1;
    void *temp_s0;
    int v[3];
    int temp_a0;

    temp_s0 = (void *)g_igSphere_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (FieldFactory *)g_igSphere_ctorTable, 2);
    temp_a0 = (int)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1);
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
    igVec3fMetaField_SetDefault((igMetaField *)temp_a0, (const float *)v);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1), -1.0f);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)g_igSphere_fieldTable, (igMetaField ***)g_igSphere_fieldHandles, (int *)g_igSphere_fieldOffsets, temp_s1);
}

void thunk_FUN_0018d480(void) {
    FUN_0018d480();
}

