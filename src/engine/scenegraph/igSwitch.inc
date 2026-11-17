igSwitch *igSwitch_CreateInstance(int allocator) {
    igSwitch_EnsureRegistered();
    return (igSwitch *)igMetaObject_CreateInstance((igMetaObject *)g_igSwitch_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *g_igSwitch_metaObject;
igMetaField *g_igSwitch_childMaskMetaField;

igMetaObject *igSwitch_GetOrCreateMetaObject(void) {
    if (g_igSwitch_metaObject == 0) {
        g_igSwitch_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igSwitch_metaObject;
}

igMetaObject *igSwitch_GetMetaObject(void)
{
    igMetaObject *g = g_igSwitch_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSwitch_EnsureRegistered();
    return g_igSwitch_metaObject;
}

int igSwitch_GetVTable(void) {
    union U_1969d0 u;
    int temp_s0;
    char *ps;
    igObject_InitHeader((igObject *)u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[28] = 0;
    u.vt = (int)&g_igSwitch_vtable[0];
    ps = &u.b[32];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
    u.vt = (int)&g_igSwitch_vtable[0];
    FUN_00196a50((struct R * *)ps, -1);
    igGroup_Destroy((igGroup *)u.b, 0);
    return temp_s0;
}

struct R **FUN_00196a50(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void igSwitch_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igSwitch_Register);
}

static igMetaObjectCallback g_igSwitch_callbackList[] = { igBitMask_EnsureRegistered, 0 };

CallbackArray *igSwitch_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSwitch_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igSwitch_GetMetaObject,
        "igSwitch",
        0x24, /* instance size */
        igSwitch_GetVTable,
        &igSwitch_InitFields,
        0, /* extra callback item */
        g_igSwitch_callbackList /* callback list */
    );
}

void thunk_igSwitch_GetMetaObject(void) {
    igSwitch_GetMetaObject();
}

static FieldFactory g_igSwitch_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igSwitch_fieldTable[] = {
    "_childMask",
};
static igMetaField **g_igSwitch_fieldHandles[] = {
    &g_igSwitch_childMaskMetaField,
};
static int g_igSwitch_fieldOffsets[] = {
    32,
};

void igSwitch_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igSwitch_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igSwitch_ctorTable, 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001a4d90();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igSwitch_fieldTable, g_igSwitch_fieldHandles, g_igSwitch_fieldOffsets, temp_s2);
}

