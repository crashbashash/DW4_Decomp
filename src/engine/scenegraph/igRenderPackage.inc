void FUN_00197ab0(int arg0) {
    FUN_00197cc0();
    igMetaObject_CreateInstance((int)g_igRenderPackage_metaObject, arg0);
}

igMetaObject *g_igRenderPackage_metaObject;
igMetaField *g_igRenderPackage_stateAttrsMetaField;
igMetaField *g_igRenderPackage_cachedStateAttrsMetaField;
igMetaField *g_igRenderPackage_geomAttrsMetaField;
igMetaField *g_igRenderPackage_sortingCacheMetaField;
igMetaField *g_igRenderPackage_distanceMetaField;
igMetaField *g_igRenderPackage_theMassMetaField;

igMetaObject *FUN_00197af0(void) {
    if (g_igRenderPackage_metaObject == 0) {
        g_igRenderPackage_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igRenderPackage_metaObject;
}

igMetaObject *igRenderPackage_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderPackage_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00197cc0();
    return g_igRenderPackage_metaObject;
}

int igRenderPackage_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_igRenderPackage_vtable[0];
    q2 = (S_ref *)&u.b[8];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[16];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[28];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igRenderPackage_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q1);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q2);
            }
        }
    }
    return temp_s0;
}

void FUN_00197cc0(void)
{
    igMetaObject_RunStaticInit(igRenderPackage_Register);
}

static igMetaObjectCallback g_igRenderPackage_callbackList[] = { igNonRefCountedAttrList_EnsureRegistered, FUN_001978a0, 0 };

void igRenderPackage_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRenderPackage_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRenderPackage_GetMetaObject,
        "igRenderPackage",
        0x20, /* instance size */
        igRenderPackage_GetVTable,
        &igRenderPackage_InitFields,
        0, /* extra callback item */
        g_igRenderPackage_callbackList /* callback list */
    );
}

void thunk_igRenderPackage_GetMetaObject(void) {
    igRenderPackage_GetMetaObject();
}

static FieldFactory g_igRenderPackage_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igRawRefMetaField_Create,
    igFloatMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igRenderPackage_fieldTable[] = {
    "_stateAttrs",
    "_cachedStateAttrs",
    "_geomAttrs",
    "_sortingCache",
    "_distance",
    "_theMass",
};
static igMetaField **g_igRenderPackage_fieldHandles[] = {
    &g_igRenderPackage_stateAttrsMetaField,
    &g_igRenderPackage_cachedStateAttrsMetaField,
    &g_igRenderPackage_geomAttrsMetaField,
    &g_igRenderPackage_sortingCacheMetaField,
    &g_igRenderPackage_distanceMetaField,
    &g_igRenderPackage_theMassMetaField,
};
static int g_igRenderPackage_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
};

void igRenderPackage_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_igRenderPackage_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igRenderPackage_ctorTable, 6);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0013ad40();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0013ad40();
    ((igObjectRefMetaField *)temp_s2_2)->_refCounted = 0;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0013ad40();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_001977c0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igRenderPackage_fieldTable, g_igRenderPackage_fieldHandles, g_igRenderPackage_fieldOffsets, temp_s0);
}

