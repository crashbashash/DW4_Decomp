igMetaObject *g_igVec4fMetaField_metaObject;
int g_igVec4fMetaField_descriptor;

igMetaField *igVec4fMetaField_CreateInstance(igMemoryPoolView *pool) {
    igVec4fMetaField_EnsureRegistered();
    return (igMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igVec4fMetaField_metaObject, pool);
}

igMetaObject *igVec4fMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVec4fMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVec4fMetaField_EnsureRegistered();
    return g_igVec4fMetaField_metaObject;
}

int igVec4fMetaField_GetVTable(void) {
    struct F f;
    int temp_s0;
    int *temp_a1;
    int temp_v0;

    FUN_002fbfe0(&f);
    f.obj.vt = &g_igVec4fMetaField_vtable[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)g_objectSystem + 916));
    f.obj.vt = &g_igMetaField_vtable[0];
    if (&f.ref != 0) {
        if (f.ref != 0) {
            temp_a1 = f.ref - 2;
            temp_v0 = f.ref[-1] - 1;
            f.ref[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*temp_a1, (StringTokenHeader *)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igVec4fMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVec4fMetaField_Register);
}

static igMetaObjectCallback g_igVec4fMetaField_callbackList[] = { FUN_00187450, 0 };

CallbackArray *igVec4fMetaField_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVec4fMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igVec4fMetaField_GetMetaObject,
        "igVec4fMetaField",
        0x34, /* instance size */
        igVec4fMetaField_GetVTable,
        0,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igVec4fMetaField_callbackList /* callback list */
    );
}

void thunk_igVec4fMetaField_GetMetaObject(void) {
    igVec4fMetaField_GetMetaObject();
}

void FUN_00187450(void) {
    void *temp_s0;

    if (g_igVec4fMetaField_descriptor == 0) {
        g_igVec4fMetaField_descriptor = (int)(igMetaObject_CreateInstance(g_igVec4fMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        temp_s0 = (void *)(g_igVec4fMetaField_descriptor);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            {
                void *held = (void *)g_igVec4fMetaField_descriptor;
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)held);
                }
            }
            *(short *)((char *)(g_igVec4fMetaField_descriptor) + 18) = (short) (*(int *)((char *)(igMetaField_GetMetaFieldList()) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igVec4fMetaField_descriptor);
        }
    }
}

int FUN_00187520(void) {
    if (g_igVec4fMetaField_descriptor == 0) {
        igVec4fMetaField_EnsureRegistered();
    }
    return g_igVec4fMetaField_descriptor;
}

