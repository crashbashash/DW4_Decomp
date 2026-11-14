igMetaObject *igPsx2VertexStream_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2VertexStream_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00152050();
    return g_igPsx2VertexStream_metaObject[0];
}

int igPsx2VertexStream_GetVTable(void) {
    union U_151f70 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_005263a0[0];
    q0 = (S_ref *)&u.b[20];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_005250b0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_005263a0[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
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
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_00152050(void)
{
    igMetaObject_RunStaticInit(igPsx2VertexStream_Register);
}

void igPsx2VertexStream_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2VertexStream_metaObject,
        igVertexStream_Register,
        igVertexStream_GetPublishedMetaObject,
        thunk_igPsx2VertexStream_GetMetaObject,
        igPsx2VertexStream_className,
        0x90, /* instance size */
        igPsx2VertexStream_GetVTable,
        &igPsx2VertexStream_InitFields,
        thunk_FUN_0017f5a0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *FUN_001520e0(void) {
    return g_igVertexStream_metaObject[0];
}

void igPsx2VertexStream_InitFields(void) {
    void *temp_s1;
    int temp_s2;
    void *f;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)g_igPsx2VertexStream_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igPsx2VertexStream_ctorTable[0], 0xA);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s2), 1);
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)) + 38) = 0;
    f = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2);
    *(int *)((char *)f + 52) = 0x10;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7)) + 38) = 0;
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    *(int *)((char *)(temp_s1) + 60) = igUnsignedCharMetaField_GetDefaultDescriptor();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9));
    *(int *)((char *)(temp_s1_2) + 60) = igUnsignedCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(temp_s0, &g_igPsx2VertexStream_fieldTable[0], &DAT_00489cc0[0], &DAT_00489cf0[0], temp_s2);
}

void thunk_FUN_0017f5a0(void) {
    FUN_0017f5a0();
}

