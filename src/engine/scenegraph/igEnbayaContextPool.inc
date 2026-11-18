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
    int base;
    void *freeIndexListField;
    void *boneCountListField;
    void *poolListField;
    void *meta;

    meta = (void *)g_igEnbayaContextPool_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igEnbayaContextPool_ctorTable, 3);
    poolListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)poolListField)->_metaObject = (int)igPointerListList_GetOrCreateMetaObject();
    ((igRefMetaField *)poolListField)->_construct = 1;
    ((igMetaField *)poolListField)->_persistent = 0;
    boneCountListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)boneCountListField)->_metaObject = (int)igUnsignedIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)boneCountListField)->_construct = 1;
    ((igMetaField *)boneCountListField)->_persistent = 0;
    freeIndexListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)freeIndexListField)->_metaObject = (int)igUnsignedIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)freeIndexListField)->_construct = 1;
    ((igMetaField *)freeIndexListField)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igEnbayaContextPool_fieldTable, g_igEnbayaContextPool_fieldHandles, g_igEnbayaContextPool_fieldOffsets, base);
}

