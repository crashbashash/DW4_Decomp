int igGraphPath_Create(int arg0) {
    igGraphPath_EnsureRegistered();
    return igMetaObject_CreateInstance((int)g_igGraphPath_metaObject, arg0);
}

igMetaObject *g_igGraphPath_metaObject;
igMetaField *g_igGraphPath_pathMetaField;
igMetaField *g_igGraphPath_centerMetaField;
igMetaField *g_igGraphPath_lengthMetaField;

igMetaObject *igGraphPath_GetOrCreateMetaObject(void) {
    if (g_igGraphPath_metaObject == 0) {
        g_igGraphPath_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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

    igObject_InitHeader(&o);
    ps = &o.ref;
    o.vt = &g_igGraphPath_vtable[0];
    *ps = 0;
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_igGraphPath_vtable[0];
    if (ps != 0) {
        temp_a0 = *ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)temp_a0);
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

void igGraphPath_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGraphPath_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igGraphPath_GetMetaObject,
        "igGraphPath",
        0x1C, /* instance size */
        igGraphPath_GetVTable,
        &igGraphPath_InitFields,
        0, /* extra callback item */
        g_igGraphPath_callbackList /* callback list */
    );
}

void thunk_igGraphPath_GetMetaObject(void) {
    igGraphPath_GetMetaObject();
}

static FieldFactory g_igGraphPath_ctorTable[] = {
    igObjectRefMetaField_Create,
    FUN_00187890,
    igFloatMetaField_Create,
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
    int temp_s2;
    void *temp_a0;
    void *temp_s1;
    void *temp_s0;
    struct { int a; int b; int c; } z;

    temp_s0 = (void *)g_igGraphPath_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igGraphPath_ctorTable, 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    *(int *)((char *)(temp_s1) + 56) = (int)igNodeList_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s1) + 36) = 3;
    *(char *)((char *)(temp_s1) + 52) = 1;
    temp_a0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    z.a = 0;
    z.b = 0;
    z.c = 0;
    FUN_0018e470(temp_a0, &z);
    igFloatMetaField_SetDefault(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2)), 1.0f);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igGraphPath_fieldTable, g_igGraphPath_fieldHandles, g_igGraphPath_fieldOffsets, temp_s2);
}

