igProbe *igProbe_Create(int allocator) {
    igProbe_EnsureRegistered();
    return (igProbe *)igMetaObject_CreateInstance((igMetaObject *)g_igProbe_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *g_igProbe_metaObject;
igMetaField *g_igProbe_volumeMetaField;
igMetaField *g_igProbe_raysMetaField;
igMetaField *g_igProbe_intersectFaceTypeMetaField;

igMetaObject *igProbe_GetOrCreateMetaObject(void) {
    if (g_igProbe_metaObject == 0) {
        g_igProbe_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igProbe_metaObject;
}

igMetaObject *igProbe_GetMetaObject(void)
{
    igMetaObject *g = g_igProbe_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igProbe_EnsureRegistered();
    return g_igProbe_metaObject;
}

int igProbe_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igProbe_vtable[0];
    q2 = (S_ref *)&u.b[8];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[16];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igProbe_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q1);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q2);
            }
        }
    }
    return temp_s0;
}

void igProbe_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igProbe_Register);
}

static igMetaObjectCallback g_igProbe_callbackList[] = { FUN_00186b20, igRayList_EnsureRegistered, igIntList_EnsureRegistered, 0 };

CallbackArray *igProbe_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igProbe_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igProbe_GetMetaObject,
        "igProbe",
        0x14, /* instance size */
        igProbe_GetVTable,
        &igProbe_InitFields,
        0, /* extra callback item */
        g_igProbe_callbackList /* callback list */
    );
}

void thunk_igProbe_GetMetaObject(void) {
    igProbe_GetMetaObject();
}

static FieldFactory g_igProbe_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igProbe_fieldTable[] = {
    "_volume",
    "_rays",
    "_intersectFaceType",
};
static igMetaField **g_igProbe_fieldHandles[] = {
    &g_igProbe_volumeMetaField,
    &g_igProbe_raysMetaField,
    &g_igProbe_intersectFaceTypeMetaField,
};
static int g_igProbe_fieldOffsets[] = {
    8,
    12,
    16,
};

void igProbe_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igProbe_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igProbe_ctorTable, 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00186a80();
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igRayList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igProbe_fieldTable, g_igProbe_fieldHandles, g_igProbe_fieldOffsets, temp_s2);
}

