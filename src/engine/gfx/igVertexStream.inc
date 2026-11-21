igMetaObject *g_igVertexStream_metaObject;
igMetaField *g_igVertexStream_streamMetaField;
igMetaField *g_igVertexStream_isConfiguredMetaField;
igMetaField *g_igVertexStream_vertexDataListMetaField;
igMetaField *g_igVertexStream_accessModeMetaField;
igMetaField *g_igVertexStream_primitiveMetaField;
igMetaField *g_igVertexStream_streamModeMetaField;

static const char *g_igVertexStream_vertexStreamCompileModeNames[] = {
    "IG_VERTEX_STREAM_COMPILE_ALL", "IG_VERTEX_STREAM_COMPILE_COMPACT_MAX", "IG_VERTEX_STREAM_COMPILE_EVERYTHING",
};
static int g_igVertexStream_vertexStreamCompileModeValues[] = {
    0, 1, 2,
};
igMetaEnum *g_igVertexStream_vertexStreamCompileModeMetaEnum;

int IG_VERTEX_STREAM_COMPILE_MODE_GetMetaEnum(void) {
    if (g_igVertexStream_vertexStreamCompileModeMetaEnum == 0) {
        g_igVertexStream_vertexStreamCompileModeMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("IG_VERTEX_STREAM_COMPILE_MODE", g_igVertexStream_vertexStreamCompileModeNames, g_igVertexStream_vertexStreamCompileModeValues, 3);
    }
    return (int)g_igVertexStream_vertexStreamCompileModeMetaEnum;
}

static const char *g_igVertexStream_vertexAccessModeNames[] = {
    "IG_VERTEX_ACCESS_READ_WRITE", "IG_VERTEX_ACCESS_READ", "IG_VERTEX_ACCESS_WRITE", "IG_VERTEX_ACCESS_WRITE_ONCE",
};
static int g_igVertexStream_vertexAccessModeValues[] = {
    0, 1, 2, 3,
};
igMetaEnum *g_igVertexStream_vertexAccessModeMetaEnum;

int IG_VERTEX_ACCESS_MODE_GetMetaEnum(void) {
    if (g_igVertexStream_vertexAccessModeMetaEnum == 0) {
        g_igVertexStream_vertexAccessModeMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("IG_VERTEX_ACCESS_MODE", g_igVertexStream_vertexAccessModeNames, g_igVertexStream_vertexAccessModeValues, 4);
    }
    return (int)g_igVertexStream_vertexAccessModeMetaEnum;
}

int igVertexStream_Create(int arg0) {
    igVertexStream_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igVertexStream_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igVertexStream_GetOrCreateMetaObject(void) {
    if (g_igVertexStream_metaObject == 0) {
        g_igVertexStream_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igVertexStream_metaObject;
}

igMetaObject *igVertexStream_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexStream_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVertexStream_EnsureRegistered();
    return g_igVertexStream_metaObject;
}

int igVertexStream_GetVTable(void) {
    union U u;
    int temp_s1;
    void ** q0;
    S_ref * q1;

    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader((igObject *)u.b);
    q0 = (void **)&u.b[8];
    *q0 = 0;
    u.vt = (int)(&g_igVertexStream_vtable[0]);
    q1 = (S_ref *)&u.b[20];
    *(int *)q1 = 0;
    temp_s1 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)(&g_igVertexStream_vtable[0]);
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q1);
            }
        }
    }
    u.vt = (int)(&g_igNamedObject_vtable[0]);
    if (q0 != 0) {
        temp_v1 = *q0;
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

void igVertexStream_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVertexStream_Register);
}

static igMetaObjectCallback g_igVertexStream_callbackList[] = { igVertexDataList_EnsureRegistered, 0 };

CallbackArray *igVertexStream_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexStream_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igVertexStream_GetMetaObjectFunction,
        "igVertexStream",
        0x24, /* instance size */
        igVertexStream_GetVTable,
        &igVertexStream_InitFields,
        0, /* extra callback item */
        g_igVertexStream_callbackList /* callback list */
    );
}

void igVertexStream_GetMetaObjectFunction(void) {
    igVertexStream_GetMetaObject();
}

static FieldFactory g_igVertexStream_ctorTable[] = {
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igVertexStream_fieldTable[] = {
    "_stream",
    "_isConfigured",
    "_vertexDataList",
    "_accessMode",
    "_primitive",
    "_streamMode",
};
static igMetaField **g_igVertexStream_fieldHandles[] = {
    &g_igVertexStream_streamMetaField,
    &g_igVertexStream_isConfiguredMetaField,
    &g_igVertexStream_vertexDataListMetaField,
    &g_igVertexStream_accessModeMetaField,
    &g_igVertexStream_primitiveMetaField,
    &g_igVertexStream_streamModeMetaField,
};
static int g_igVertexStream_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
};

void igVertexStream_InitFields(void) {
    int fieldStart;
    void *dataListField;
    void *accessModeField;
    void *primitiveTypeField;
    void *compileModeField;
    igMetaObject *meta;

    meta = g_igVertexStream_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igVertexStream_ctorTable, 6);
    ((igRawRefMetaField *)igMetaObject_GetFieldAt(meta, fieldStart))->_persistent = 0;
    ((igBoolMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 1))->_persistent = 0;
    dataListField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 2));
    ((igObjectRefMetaField *)dataListField)->_metaObject = (int)igVertexDataList_GetOrCreateMetaObject();
    accessModeField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 3));
    ((Gap::Core::igEnumMetaField *)accessModeField)->setDefault(0);
    ((igEnumMetaField *)accessModeField)->_getMetaEnumFunction = (int)(&IG_VERTEX_ACCESS_MODE_GetMetaEnum);
    primitiveTypeField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 4));
    ((Gap::Core::igEnumMetaField *)primitiveTypeField)->setDefault(0);
    ((igEnumMetaField *)primitiveTypeField)->_getMetaEnumFunction = (int)(&IG_GFX_DRAW_GetMetaEnum);
    compileModeField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 5));
    ((Gap::Core::igEnumMetaField *)compileModeField)->setDefault(0);
    ((igEnumMetaField *)compileModeField)->_getMetaEnumFunction = (int)(IG_VERTEX_STREAM_COMPILE_MODE_GetMetaEnum);
    igMetaObject_NameFields(meta, g_igVertexStream_fieldTable, g_igVertexStream_fieldHandles, g_igVertexStream_fieldOffsets, fieldStart);
    ((igMetaObject *)g_igVertexStream_metaObject)->_abstractProxy = (int)igPsx2VertexStream_GetMetaObjectFunction;
}

