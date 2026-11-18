void FUN_00197ab0(int arg0) {
    igRenderPackage_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)g_igRenderPackage_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *g_igRenderPackage_metaObject;
igMetaField *g_igRenderPackage_stateAttrsMetaField;
igMetaField *g_igRenderPackage_cachedStateAttrsMetaField;
igMetaField *g_igRenderPackage_geomAttrsMetaField;
igMetaField *g_igRenderPackage_sortingCacheMetaField;
igMetaField *g_igRenderPackage_distanceMetaField;
igMetaField *g_igRenderPackage_theMassMetaField;

igMetaObject *igRenderPackage_GetOrCreateMetaObject(void) {
    if (g_igRenderPackage_metaObject == 0) {
        g_igRenderPackage_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRenderPackage_metaObject;
}

igMetaObject *igRenderPackage_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderPackage_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRenderPackage_EnsureRegistered();
    return g_igRenderPackage_metaObject;
}

int igRenderPackage_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igRenderPackage_vtable[0];
    q2 = (S_ref *)&u.b[8];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[16];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[28];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igRenderPackage_vtable[0];
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

void igRenderPackage_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRenderPackage_Register);
}

static igMetaObjectCallback g_igRenderPackage_callbackList[] = { igNonRefCountedAttrList_EnsureRegistered, igRenderPackageList_EnsureRegistered, 0 };

CallbackArray *igRenderPackage_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRenderPackage_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igRenderPackage_GetMetaObjectFunction,
        "igRenderPackage",
        0x20, /* instance size */
        igRenderPackage_GetVTable,
        &igRenderPackage_InitFields,
        0, /* extra callback item */
        g_igRenderPackage_callbackList /* callback list */
    );
}

void igRenderPackage_GetMetaObjectFunction(void) {
    igRenderPackage_GetMetaObject();
}

static FieldFactory g_igRenderPackage_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
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
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igRenderPackage_ctorTable, 6);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igNonRefCountedAttrList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igNonRefCountedAttrList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_2)->_refCounted = 0;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igNonRefCountedAttrList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igRenderPackageList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igRenderPackage_fieldTable, g_igRenderPackage_fieldHandles, g_igRenderPackage_fieldOffsets, temp_s0);
}

