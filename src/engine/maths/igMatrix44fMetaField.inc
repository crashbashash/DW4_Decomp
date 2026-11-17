igMetaObject *g_igMatrix44fMetaField_metaObject;
int g_igMatrix44fMetaField_descriptor;

igMetaField *igMatrix44fMetaField_CreateInstance(igMemoryPoolView *pool) {
    igMatrix44fMetaField_EnsureRegistered();
    return (igMetaField *)igMetaObject_CreateInstance(g_igMatrix44fMetaField_metaObject, pool);
}

igMetaObject *igMatrix44fMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrix44fMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMatrix44fMetaField_EnsureRegistered();
    return g_igMatrix44fMetaField_metaObject;
}

int igMatrix44fMetaField_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init((igMetaField *)u.b);
    u.vt = (int)&g_igMatrix44fMetaField_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
    u.vt = (int)&g_igMetaField_vtable[0];
    ps = &u.b[12];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*temp_a1, (StringTokenHeader *)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igMatrix44fMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMatrix44fMetaField_Register);
}

static igMetaObjectCallback g_igMatrix44fMetaField_callbackList[] = { FUN_00188810, 0 };

CallbackArray *igMatrix44fMetaField_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMatrix44fMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igMatrix44fMetaField_GetMetaObject,
        "igMatrix44fMetaField",
        0x34, /* instance size */
        igMatrix44fMetaField_GetVTable,
        0,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igMatrix44fMetaField_callbackList /* callback list */
    );
}

void thunk_igMatrix44fMetaField_GetMetaObject(void) {
    igMatrix44fMetaField_GetMetaObject();
}

void FUN_00188810(void) {
    void *temp_s0;

    if (g_igMatrix44fMetaField_descriptor == 0) {
        g_igMatrix44fMetaField_descriptor = (int)(igMetaObject_CreateInstance(g_igMatrix44fMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        temp_s0 = (void *)(g_igMatrix44fMetaField_descriptor);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), temp_s0);
            {
                void *held = (void *)g_igMatrix44fMetaField_descriptor;
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)held);
                }
            }
            *(short *)((char *)(g_igMatrix44fMetaField_descriptor) + 18) = (short) (*(int *)((char *)(igMetaField_GetMetaFieldList()) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igMatrix44fMetaField_descriptor);
        }
    }
}

int FUN_001888e0(void) {
    if (g_igMatrix44fMetaField_descriptor == 0) {
        igMatrix44fMetaField_EnsureRegistered();
    }
    return g_igMatrix44fMetaField_descriptor;
}

