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

int FUN_0014ad00(void) {
    if (g_igVertexStream_vertexStreamCompileModeMetaEnum == 0) {
        g_igVertexStream_vertexStreamCompileModeMetaEnum = igMetaEnum_Create("IG_VERTEX_STREAM_COMPILE_MODE", g_igVertexStream_vertexStreamCompileModeNames, g_igVertexStream_vertexStreamCompileModeValues, 3);
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

int FUN_0014ad60(void) {
    if (g_igVertexStream_vertexAccessModeMetaEnum == 0) {
        g_igVertexStream_vertexAccessModeMetaEnum = igMetaEnum_Create("IG_VERTEX_ACCESS_MODE", g_igVertexStream_vertexAccessModeNames, g_igVertexStream_vertexAccessModeValues, 4);
    }
    return (int)g_igVertexStream_vertexAccessModeMetaEnum;
}

int FUN_0014adc0(int arg0) {
    FUN_0014af80();
    return igMetaObject_CreateInstance(g_igVertexStream_metaObject, arg0);
}

igMetaObject *FUN_0014ae00(void) {
    if (g_igVertexStream_metaObject == 0) {
        g_igVertexStream_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igVertexStream_metaObject;
}

igMetaObject *igVertexStream_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexStream_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014af80();
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

    igObject_InitHeader(u.b);
    q0 = (void **)&u.b[8];
    *q0 = 0;
    u.vt = (int)(&DAT_005263a0[0]);
    q1 = (S_ref *)&u.b[20];
    *(int *)q1 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)(&DAT_005263a0[0]);
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
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
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s1;
}

void FUN_0014af80(void)
{
    igMetaObject_RunStaticInit(igVertexStream_Register);
}

static igMetaObjectCallback g_igVertexStream_callbackList[] = { FUN_0014b2a0, 0 };

void igVertexStream_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexStream_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igVertexStream_GetMetaObject,
        "igVertexStream",
        0x24, /* instance size */
        igVertexStream_GetVTable,
        &igVertexStream_InitFields,
        0, /* extra callback item */
        g_igVertexStream_callbackList /* callback list */
    );
}

void thunk_igVertexStream_GetMetaObject(void) {
    igVertexStream_GetMetaObject();
}

static FieldFactory g_igVertexStream_ctorTable[] = {
    igRawRefMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
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
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    igMetaObject *meta;

    meta = g_igVertexStream_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igVertexStream_ctorTable, 6);
    ((igRawRefMetaField *)igMetaObject_GetFieldAt(meta, fieldStart))->_persistent = 0;
    ((igBoolMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 1))->_persistent = 0;
    temp_s2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 2));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0014b1c0();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 3));
    igEnumMetaField_SetDefaultValue(temp_v0, &DAT_00488628[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_0014ad60);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 4));
    igEnumMetaField_SetDefaultValue(temp_v0_2, &DAT_00488630[0]);
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&FUN_00149aa0);
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 5));
    igEnumMetaField_SetDefaultValue(temp_v0_3, &DAT_00488638[0]);
    ((igEnumMetaField *)temp_v0_3)->_getMetaEnumFunction = (int)(FUN_0014ad00);
    igMetaObject_NameFields(meta, g_igVertexStream_fieldTable, g_igVertexStream_fieldHandles, g_igVertexStream_fieldOffsets, fieldStart);
    ((igMetaObject *)g_igVertexStream_metaObject)->_abstractProxy = (int)thunk_igPsx2VertexStream_GetMetaObject;
}

