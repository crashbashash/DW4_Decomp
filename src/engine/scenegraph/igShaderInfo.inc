int FUN_00198cc0(int arg0) {
    igShaderInfo_EnsureRegistered();
    return (int)igMetaObject_CreateInstance((igMetaObject *)g_igShaderInfo_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *g_igShaderInfo_metaObject;
igMetaField *g_igShaderInfo_factoryListMetaField;

igMetaObject *igShaderInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igShaderInfo_EnsureRegistered();
    return g_igShaderInfo_metaObject;
}

int igShaderInfo_GetVTable(void) {
    union U_198d50 u;
    int temp_s1;
    void **q2;
    S_ref *q5;

    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader((igObject *)u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&g_igShaderInfo_vtable[0]);
    q5 = (S_ref *)&u.p[5];
    *(int *)q5 = 0;
    temp_s1 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.w[0] = (int)(&g_igShaderInfo_vtable[0]);
    if (q5 != 0) {
        q5 = *(S_ref **)q5;
        if (q5 != 0) {
            q5->f4 = (int)((int) (q5->f4 - 1));
            if (((unsigned long long) ((long long) q5->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q5);
            }
        }
    }
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q2 != 0) {
        temp_v1 = *q2;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*temp_a1, (StringTokenHeader *)temp_a1);
            }
        }
    }
    return temp_s1;
}

void igShaderInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igShaderInfo_Register);
}

static igMetaObjectCallback g_igShaderInfo_callbackList[] = { igShaderFactoryList_EnsureRegistered, 0 };

CallbackArray *igShaderInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igShaderInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igShaderInfo_GetMetaObject,
        "igShaderInfo",
        0x18, /* instance size */
        igShaderInfo_GetVTable,
        &igShaderInfo_InitFields,
        thunk_FUN_001d8ab0, /* extra callback item */
        g_igShaderInfo_callbackList /* callback list */
    );
}

void thunk_igShaderInfo_GetMetaObject(void) {
    igShaderInfo_GetMetaObject();
}

static FieldFactory g_igShaderInfo_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igShaderInfo_fieldTable[] = {
    "_factoryList",
};
static igMetaField **g_igShaderInfo_fieldHandles[] = {
    &g_igShaderInfo_factoryListMetaField,
};
static int g_igShaderInfo_fieldOffsets[] = {
    20,
};

void igShaderInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igShaderInfo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igShaderInfo_ctorTable, 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_00198fa0();
    *(char *)((char *)(temp_s1) + 52) = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igShaderInfo_fieldTable, g_igShaderInfo_fieldHandles, g_igShaderInfo_fieldOffsets, temp_s2);
    igMetaObject_AddExitCallback((int)thunk_FUN_001d8b90);
}

void thunk_FUN_001d8ab0(void) {
    FUN_001d8ab0();
}

void thunk_FUN_001d8b90(void) {
    FUN_001d8b90();
}

