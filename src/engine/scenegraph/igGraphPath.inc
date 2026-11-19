igGraphPath *igGraphPath_Create(int allocator) {
    igGraphPath_EnsureRegistered();
    return (igGraphPath *)igMetaObject_CreateInstance((igMetaObject *)g_igGraphPath_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *g_igGraphPath_metaObject;
igMetaField *g_igGraphPath_pathMetaField;
igMetaField *g_igGraphPath_centerMetaField;
igMetaField *g_igGraphPath_lengthMetaField;

igMetaObject *igGraphPath_GetOrCreateMetaObject(void) {
    if (g_igGraphPath_metaObject == 0) {
        g_igGraphPath_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGraphPath_metaObject;
}

igMetaObject *igGraphPath_GetMetaObject(void)
{
    igMetaObject *g = g_igGraphPath_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGraphPath_EnsureRegistered();
    return g_igGraphPath_metaObject;
}

int igGraphPath_GetVTable(void) {
    Obj_19f710 o;
    int **ps;
    int *temp_a0;
    int temp_s0;

    igObject_InitHeader((igObject *)&o);
    ps = &o.ref;
    o.vt = &g_igGraphPath_vtable[0];
    *ps = 0;
    temp_s0 = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = &g_igGraphPath_vtable[0];
    if (ps != 0) {
        temp_a0 = *ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
    }
    return temp_s0;
}

void igGraphPath_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGraphPath_Register);
}

static igMetaObjectCallback g_igGraphPath_callbackList[] = { igNodeList_EnsureRegistered, 0 };

CallbackArray *igGraphPath_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGraphPath_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igGraphPath_GetMetaObjectFunction,
        "igGraphPath",
        0x1C, /* instance size */
        igGraphPath_GetVTable,
        &igGraphPath_InitFields,
        0, /* extra callback item */
        g_igGraphPath_callbackList /* callback list */
    );
}

void igGraphPath_GetMetaObjectFunction(void) {
    igGraphPath_GetMetaObject();
}

static FieldFactory g_igGraphPath_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igFloatMetaField_Create,
};
static const char *g_igGraphPath_fieldTable[] = {
    "_path",
    "_center",
    "_length",
};
static igMetaField **g_igGraphPath_fieldHandles[] = {
    &g_igGraphPath_pathMetaField,
    &g_igGraphPath_centerMetaField,
    &g_igGraphPath_lengthMetaField,
};
static int g_igGraphPath_fieldOffsets[] = {
    8,
    12,
    24,
};

void igGraphPath_InitFields(void) {
    int base;
    void *centerField;
    void *pathField;
    void *meta;
    struct { int x; int y; int z; } defaultCenter;

    meta = (void *)g_igGraphPath_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igGraphPath_ctorTable, 3);
    pathField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)pathField)->_metaObject = (int)igNodeList_GetOrCreateMetaObject();
    ((igMetaField *)pathField)->_resetMethod = 3;
    ((igRefMetaField *)pathField)->_construct = 1;
    centerField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    defaultCenter.x = 0;
    defaultCenter.y = 0;
    defaultCenter.z = 0;
    igVec3fMetaField_SetDefault((igMetaField *)centerField, (const float *)&defaultCenter);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2), 1.0f);
    igMetaObject_NameFields((igMetaObject *)meta, g_igGraphPath_fieldTable, g_igGraphPath_fieldHandles, g_igGraphPath_fieldOffsets, base);
}

