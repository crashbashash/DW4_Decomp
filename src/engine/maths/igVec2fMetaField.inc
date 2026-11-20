igMetaObject *g_igVec2fMetaField_metaObject;
int g_igVec2fMetaField_descriptor;

igMetaField *igVec2fMetaField_CreateInstance(igMemoryPoolView *pool) {
    igVec2fMetaField_EnsureRegistered();
    return (igMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igVec2fMetaField_metaObject, pool);
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

    igMetaField_Init((igMetaField *)&o);
    o.vt = &g_igVec2fMetaField_vtable[0];
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = &g_igMetaField_vtable[0];
    if (&o.str != 0) {
        temp_v1 = o.str;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*temp_a1, (StringTokenHeader *)temp_a1);
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

CallbackArray *igVec2fMetaField_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVec2fMetaField_metaObject,
        Gap::Core::igMetaField::arkRegisterInternal,
        igMetaField_GetPublishedMetaObject,
        igVec2fMetaField_GetMetaObjectFunction,
        "igVec2fMetaField",
        0x34, /* instance size */
        igVec2fMetaField_GetVTable,
        0,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igVec2fMetaField_callbackList /* callback list */
    );
}

void igVec2fMetaField_GetMetaObjectFunction(void) {
    igVec2fMetaField_GetMetaObject();
}

void FUN_00187d00(void) {
    void *temp_s0;

    if (g_igVec2fMetaField_descriptor == 0) {
        g_igVec2fMetaField_descriptor = (int)(igMetaObject_CreateInstance(g_igVec2fMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        temp_s0 = (void *)(g_igVec2fMetaField_descriptor);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)temp_s0);
            {
                void *held = (void *)g_igVec2fMetaField_descriptor;
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)held);
                }
            }
            *(short *)((char *)(g_igVec2fMetaField_descriptor) + 18) = (short) (*(int *)((char *)(Gap::Core::igMetaField::getMetaFieldTypes()) + 12) - 1);
            ((Gap::Core::igMetaField *)g_igVec2fMetaField_descriptor)->validate();
        }
    }
}

int FUN_00187dd0(void) {
    if (g_igVec2fMetaField_descriptor == 0) {
        igVec2fMetaField_EnsureRegistered();
    }
    return g_igVec2fMetaField_descriptor;
}

