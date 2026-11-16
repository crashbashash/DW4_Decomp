igMetaObject *g_igVec2fMetaField_metaObject;
int g_igVec2fMetaField_descriptor;

void FUN_00187b50(int arg0) {
    igVec2fMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((int)g_igVec2fMetaField_metaObject, arg0);
}

igMetaObject *igVec2fMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVec2fMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVec2fMetaField_EnsureRegistered();
    return g_igVec2fMetaField_metaObject;
}

int igVec2fMetaField_GetVTable(void) {
    Obj6 o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igMetaField_Init(&o);
    o.vt = &g_igVec2fMetaField_vtable[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_igMetaField_vtable[0];
    if (&o.str != 0) {
        temp_v1 = o.str;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return r;
}

void igVec2fMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVec2fMetaField_Register);
}

static igMetaObjectCallback g_igVec2fMetaField_callbackList[] = { FUN_00187d00, 0 };

void igVec2fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVec2fMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igVec2fMetaField_GetMetaObject,
        "igVec2fMetaField",
        0x34, /* instance size */
        igVec2fMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igVec2fMetaField_callbackList /* callback list */
    );
}

void thunk_igVec2fMetaField_GetMetaObject(void) {
    igVec2fMetaField_GetMetaObject();
}

void FUN_00187d00(void) {
    void *temp_s0;

    if (g_igVec2fMetaField_descriptor == 0) {
        g_igVec2fMetaField_descriptor = (int)(igMetaObject_CreateInstance(g_igVec2fMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0])));
        temp_s0 = (void *)(g_igVec2fMetaField_descriptor);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), temp_s0);
            {
                void *held = (void *)g_igVec2fMetaField_descriptor;
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(g_igVec2fMetaField_descriptor) + 18) = (short) (*(int *)((char *)(igMetaField_GetMetaFieldList()) + 12) - 1);
            igMetaField_FinalizeDescriptor(g_igVec2fMetaField_descriptor);
        }
    }
}

int FUN_00187dd0(void) {
    if (g_igVec2fMetaField_descriptor == 0) {
        igVec2fMetaField_EnsureRegistered();
    }
    return g_igVec2fMetaField_descriptor;
}

