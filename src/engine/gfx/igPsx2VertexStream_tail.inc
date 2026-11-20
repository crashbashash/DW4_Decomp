igMetaObject *igPsx2VertexStream_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2VertexStream_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2VertexStream_EnsureRegistered();
    return g_igPsx2VertexStream_metaObject;
}

int igPsx2VertexStream_GetVTable(void) {
    union U_151f70 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader((igObject *)u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&g_igVertexStream_vtable[0];
    q0 = (S_ref *)&u.b[20];
    *(int *)q0 = 0;
    u.vt = (int)&g_igPsx2VertexStream_vtable[0];
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igVertexStream_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q0);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
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

void igPsx2VertexStream_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2VertexStream_Register);
}

CallbackArray *igPsx2VertexStream_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2VertexStream_metaObject,
        igVertexStream_Register,
        igVertexStream_GetPublishedMetaObject,
        igPsx2VertexStream_GetMetaObjectFunction,
        "igPsx2VertexStream",
        0x90, /* instance size */
        igPsx2VertexStream_GetVTable,
        &igPsx2VertexStream_InitFields,
        thunk_FUN_0017f5a0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *igVertexStream_GetPublishedMetaObject(void) {
    return g_igVertexStream_metaObject;
}

static FieldFactory g_igPsx2VertexStream_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igUnsignedLongMetaField_Create,
    (FieldFactory)igUnsignedIntArrayMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
};
static const char *g_igPsx2VertexStream_fieldTable[] = {
    "_scaleAlphaState",
    "_syncSequence",
    "_textureCoordCompiled",
    "_multipassCompiled",
    "_blendMatrixCount",
    "_blendIndexCount",
    "_vertexCountCompiled",
    "_renderListHandle",
    "_dmaBuffer",
    "_dmaBufferStruct",
};
static igMetaField **g_igPsx2VertexStream_fieldHandles[] = {
    &g_igPsx2VertexStream_scaleAlphaStateMetaField,
    &g_igPsx2VertexStream_syncSequenceMetaField,
    &g_igPsx2VertexStream_textureCoordCompiledMetaField,
    &g_igPsx2VertexStream_multipassCompiledMetaField,
    &g_igPsx2VertexStream_blendMatrixCountMetaField,
    &g_igPsx2VertexStream_blendIndexCountMetaField,
    &g_igPsx2VertexStream_vertexCountCompiledMetaField,
    &g_igPsx2VertexStream_renderListHandleMetaField,
    &g_igPsx2VertexStream_dmaBufferMetaField,
    &g_igPsx2VertexStream_dmaBufferStructMetaField,
};
static int g_igPsx2VertexStream_fieldOffsets[] = {
    36,
    40,
    48,
    112,
    116,
    120,
    124,
    128,
    132,
    136,
};

void igPsx2VertexStream_InitFields(void) {
    void *temp_s1;
    int fieldStart;
    void *f;
    void *temp_s1_2;
    igMetaObject *meta;

    meta = g_igPsx2VertexStream_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPsx2VertexStream_ctorTable, 0xA);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, fieldStart)))->setDefault(1);
    *(char *)((char *)(igMetaObject_GetFieldAt(meta, fieldStart + 1)) + 38) = 0;
    f = igMetaObject_GetFieldAt(meta, fieldStart + 2);
    *(int *)((char *)f + 52) = 0x10;
    *(char *)((char *)(igMetaObject_GetFieldAt(meta, fieldStart + 7)) + 38) = 0;
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 8));
    *(int *)((char *)(temp_s1) + 60) = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 9));
    *(int *)((char *)(temp_s1_2) + 60) = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    igMetaObject_NameFields(meta, g_igPsx2VertexStream_fieldTable, g_igPsx2VertexStream_fieldHandles, g_igPsx2VertexStream_fieldOffsets, fieldStart);
}

void thunk_FUN_0017f5a0(void) {
    FUN_0017f5a0();
}

