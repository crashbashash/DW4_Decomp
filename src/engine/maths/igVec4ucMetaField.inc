igMetaObject *g_igVec4ucMetaField_metaObject;
M *g_igVec4ucMetaField_descriptor;

igMetaObject *igVec4ucMetaField_GetMetaObject(void)
{
    igMetaObject *meta = g_igVec4ucMetaField_metaObject;
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    igVec4ucMetaField_EnsureRegistered();
end:
    return g_igVec4ucMetaField_metaObject;
}

int igVec4ucMetaField_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init((igMetaField *)u.b);
    u.vt = (int)&g_igVec4ucMetaField_vtable[0];
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
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

void igVec4ucMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVec4ucMetaField_Register);
}

static igMetaObjectCallback g_igVec4ucMetaField_callbackList[] = { FUN_00187190, 0 };

CallbackArray *igVec4ucMetaField_Register(void) {
    FUN_00186a40();  /* one-shot static-init guard (byte flag), chaining to sibling init stubs */
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVec4ucMetaField_metaObject,
        Gap::Core::igMetaField::arkRegisterInternal,
        igMetaField_GetPublishedMetaObject,
        (igMetaObjectCallback)thunk_igVec4ucMetaField_GetMetaObject_00187170,
        "igVec4ucMetaField",
        0x34, /* instance size */
        igVec4ucMetaField_GetVTable,
        0,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igVec4ucMetaField_callbackList /* callback list */
    );
}

void igVec4ucMetaField_GetMetaObjectFunction(void) {
    igVec4ucMetaField_GetMetaObject();
}

int FUN_00187180(void) {
    return (int)Gap::Core::igMetaField::getClassMeta();
}

void FUN_00187190(void) {
    M *temp_s0;
    M *p;
    int len;

    if (g_igVec4ucMetaField_descriptor == 0) {
        g_igVec4ucMetaField_descriptor = (M *)igMetaObject_CreateInstance(g_igVec4ucMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
        temp_s0 = g_igVec4ucMetaField_descriptor;
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)temp_s0);
            p = g_igVec4ucMetaField_descriptor;
            p->f4 = p->f4 - 1;
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)p);
            }
            len = Gap::Core::igMetaField::getMetaFieldTypes()->_count;
            g_igVec4ucMetaField_descriptor->f18 = len - 1;
            ((Gap::Core::igMetaField *)g_igVec4ucMetaField_descriptor)->validate();
        }
    }
}

int FUN_00187260(void) {
    if (g_igVec4ucMetaField_descriptor == 0) {
        igVec4ucMetaField_EnsureRegistered();
    }
    return (int)g_igVec4ucMetaField_descriptor;
}

