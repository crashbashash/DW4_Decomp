int FUN_0014ad00(void) {
    if (DAT_0055fa00[0] == 0) {
        DAT_0055fa00[0] = igMetaEnum_Create(&IG_VERTEX_STREAM_COMPILE_MODE[0], &DAT_00488560[0], &DAT_00488570[0], 3);
    }
    return DAT_0055fa00[0];
}

int FUN_0014ad60(void) {
    if (DAT_0055fa08[0] == 0) {
        DAT_0055fa08[0] = igMetaEnum_Create(&IG_VERTEX_ACCESS_MODE[0], &DAT_00488580[0], &DAT_00488590[0], 4);
    }
    return DAT_0055fa08[0];
}

int FUN_0014adc0(int arg0) {
    FUN_0014af80();
    return igMetaObject_CreateInstance(*(int *)0x55FA10, arg0);
}

igMetaObject *FUN_0014ae00(void) {
    if (g_igVertexStream_metaObject[0] == 0) {
        g_igVertexStream_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igVertexStream_metaObject[0];
}

igMetaObject *igVertexStream_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexStream_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014af80();
    return g_igVertexStream_metaObject[0];
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

void igVertexStream_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexStream_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igVertexStream_GetMetaObject,
        igVertexStream_className,
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

void igVertexStream_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_s1;

    temp_s1 = (void *)(g_igVertexStream_metaObject[0]);
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igVertexStream_ctorTable[0], 6);
    ((igRawRefMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0))->_persistent = 0;
    ((igBoolMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1))->_persistent = 0;
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0014b1c0();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    FUN_002dc7a0(temp_v0, &DAT_00488628[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_0014ad60);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    FUN_002dc7a0(temp_v0_2, &DAT_00488630[0]);
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&FUN_00149aa0);
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    FUN_002dc7a0(temp_v0_3, &DAT_00488638[0]);
    ((igEnumMetaField *)temp_v0_3)->_getMetaEnumFunction = (int)(FUN_0014ad00);
    igMetaObject_NameFields(temp_s1, &g_igVertexStream_fieldTable[0], &DAT_004885f0[0], &DAT_00488610[0], temp_s0);
    ((igMetaObject *)g_igVertexStream_metaObject[0])->_abstractProxy = (int)thunk_igPsx2VertexStream_GetMetaObject;
}

