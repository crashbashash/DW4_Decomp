igMetaObject *g_igVec4fArrayMetaField_metaObject;
igMetaField *g_igVec4fArrayMetaField_numMetaField;
M *g_igVec4fArrayMetaField_descriptor;

void FUN_00187560(int arg0) {
    igVec4fArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)g_igVec4fArrayMetaField_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igVec4fArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVec4fArrayMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVec4fArrayMetaField_EnsureRegistered();
    return g_igVec4fArrayMetaField_metaObject;
}

int igVec4fArrayMetaField_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init((igMetaField *)u.b);
    u.vt = (int)&g_igVec4fArrayMetaField_vtable[0];
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

void igVec4fArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVec4fArrayMetaField_Register);
}

static igMetaObjectCallback g_igVec4fArrayMetaField_callbackList[] = { FUN_001877c0, 0 };

CallbackArray *igVec4fArrayMetaField_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVec4fArrayMetaField_metaObject,
        igVec4fMetaField_Register,
        (igMetaObjectGetFunction)igVec4fMetaField_GetPublishedMetaObject,
        thunk_igVec4fArrayMetaField_GetMetaObject,
        "igVec4fArrayMetaField",
        0x38, /* instance size */
        igVec4fArrayMetaField_GetVTable,
        &igVec4fArrayMetaField_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igVec4fArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igVec4fArrayMetaField_GetMetaObject(void) {
    igVec4fArrayMetaField_GetMetaObject();
}

igMetaObject *FUN_00187720(void) {
    return g_igVec4fMetaField_metaObject;
}

static FieldFactory g_igVec4fArrayMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};

static const char *g_igVec4fArrayMetaField_fieldTable[] = {
    "_num",
};

static igMetaField **g_igVec4fArrayMetaField_fieldHandles[] = {
    &g_igVec4fArrayMetaField_numMetaField,
};

static int g_igVec4fArrayMetaField_fieldOffsets[] = {
    52,
};

void igVec4fArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igVec4fArrayMetaField_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (FieldFactory *)g_igVec4fArrayMetaField_ctorTable, 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)g_igVec4fArrayMetaField_fieldTable, (igMetaField ***)g_igVec4fArrayMetaField_fieldHandles, (int *)g_igVec4fArrayMetaField_fieldOffsets, temp_s1);
}

void FUN_001877c0(void) {
    M *temp_s0;
    M *o;
    int t;

    if (g_igVec4fArrayMetaField_descriptor == 0) {
        g_igVec4fArrayMetaField_descriptor = (M *)igMetaObject_CreateInstance(g_igVec4fArrayMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
        temp_s0 = g_igVec4fArrayMetaField_descriptor;
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            o = g_igVec4fArrayMetaField_descriptor;
            o->f4 = o->f4 - 1;
            if ((o->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
            t = igMetaField_GetMetaFieldList()->_count - 1;
            g_igVec4fArrayMetaField_descriptor->f18 = t;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igVec4fArrayMetaField_descriptor);
        }
    }
}

