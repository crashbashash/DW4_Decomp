igMetaObject *g_igVec3fMetaField_metaObject;
int g_igVec3fMetaField_descriptor;

igMetaField *igVec3fMetaField_CreateInstance(void *arg0) {
    igVec3fMetaField_EnsureRegistered();
    return (igMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igVec3fMetaField_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igVec3fMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVec3fMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVec3fMetaField_EnsureRegistered();
    return g_igVec3fMetaField_metaObject;
}

int igVec3fMetaField_GetVTable(void) {
    struct Obj5 obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igMetaField_Init((igMetaField *)&obj);
    obj.vt = &g_igVec3fMetaField_vtable[0];
    t = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj.vt = &g_igMetaField_vtable[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1);
            }
        }
    }
    return t;
}

void igVec3fMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVec3fMetaField_Register);
}

static igMetaObjectCallback g_igVec3fMetaField_callbackList[] = { FUN_00187a40, 0 };

CallbackArray *igVec3fMetaField_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVec3fMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igVec3fMetaField_GetMetaObject,
        "igVec3fMetaField",
        0x34, /* instance size */
        igVec3fMetaField_GetVTable,
        0,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igVec3fMetaField_callbackList /* callback list */
    );
}

void thunk_igVec3fMetaField_GetMetaObject(void) {
    igVec3fMetaField_GetMetaObject();
}

void FUN_00187a40(void) {
    void *temp_s0;

    if (g_igVec3fMetaField_descriptor == 0) {
        g_igVec3fMetaField_descriptor = (int)(igMetaObject_CreateInstance(g_igVec3fMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        temp_s0 = (void *)(g_igVec3fMetaField_descriptor);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), temp_s0);
            {
                void *held = (void *)g_igVec3fMetaField_descriptor;
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(g_igVec3fMetaField_descriptor) + 18) = (short) (*(int *)((char *)(igMetaField_GetMetaFieldList()) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igVec3fMetaField_descriptor);
        }
    }
}

int FUN_00187b10(void) {
    if (g_igVec3fMetaField_descriptor == 0) {
        igVec3fMetaField_EnsureRegistered();
    }
    return g_igVec3fMetaField_descriptor;
}

