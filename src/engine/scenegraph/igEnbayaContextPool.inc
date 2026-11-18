igMetaObject *g_igEnbayaContextPool_metaObject;
igMetaField *g_igEnbayaContextPool_poolListMetaField;
igMetaField *g_igEnbayaContextPool_boneCountListMetaField;
igMetaField *g_igEnbayaContextPool_freeIndexListMetaField;

igEnbayaContextPool *igEnbayaContextPool_Create(int allocator) {
    igEnbayaContextPool_RunStaticInit();
    return (igEnbayaContextPool *)igMetaObject_CreateInstance(g_igEnbayaContextPool_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igEnbayaContextPool_GetMetaObject(void)
{
    igMetaObject *g = g_igEnbayaContextPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igEnbayaContextPool_RunStaticInit();
    return g_igEnbayaContextPool_metaObject;
}

int igEnbayaContextPool_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igEnbayaContextPool_vtable[0];
    q2 = (S_ref *)&u.b[8];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[16];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igEnbayaContextPool_vtable[0];
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

void igEnbayaContextPool_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igEnbayaContextPool_Register);
}

static igMetaObjectCallback g_igEnbayaContextPool_callbackList[] = { igPointerListList_EnsureRegistered, igUnsignedIntList_EnsureRegistered, 0 };

CallbackArray *igEnbayaContextPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igEnbayaContextPool_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEnbayaContextPool_GetMetaObject,
        "igEnbayaContextPool",
        0x14, /* instance size */
        igEnbayaContextPool_GetVTable,
        &igEnbayaContextPool_InitFields,
        0, /* extra callback item */
        g_igEnbayaContextPool_callbackList /* callback list */
    );
}

void thunk_igEnbayaContextPool_GetMetaObject(void) {
    igEnbayaContextPool_GetMetaObject();
}

static FieldFactory g_igEnbayaContextPool_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igEnbayaContextPool_fieldTable[] = {
    "_poolList",
    "_boneCountList",
    "_freeIndexList",
};
static igMetaField **g_igEnbayaContextPool_fieldHandles[] = {
    &g_igEnbayaContextPool_poolListMetaField,
    &g_igEnbayaContextPool_boneCountListMetaField,
    &g_igEnbayaContextPool_freeIndexListMetaField,
};
static int g_igEnbayaContextPool_fieldOffsets[] = {
    8,
    12,
    16,
};

void igEnbayaContextPool_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igEnbayaContextPool_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igEnbayaContextPool_ctorTable, 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igPointerListList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igUnsignedIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)igUnsignedIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    ((igMetaField *)temp_s1_3)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igEnbayaContextPool_fieldTable, g_igEnbayaContextPool_fieldHandles, g_igEnbayaContextPool_fieldOffsets, temp_s2);
}

