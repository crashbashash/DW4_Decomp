int FUN_0014b330(void) {
    if (DAT_0055fa50[0] == 0) {
        DAT_0055fa50[0] = igMetaEnum_Create(&DAT_004dbd40[0], &DAT_00488650[0], &DAT_00488680[0], 0xB);
    }
    return DAT_0055fa50[0];
}

int FUN_0014b390(int arg0) {
    FUN_0014b500();
    return igMetaObject_CreateInstance(*(int *)0x55FA58, arg0);
}

igMetaObject *igVertexData_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014b500();
    return g_igVertexData_metaObject[0];
}

int igVertexData_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_005270a0[0];
    q0 = (S_ref *)&u.b[12];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_005270a0[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&DAT_00524950[0];
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

void FUN_0014b500(void)
{
    igMetaObject_RunStaticInit(igVertexData_Register);
}

void igVertexData_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igVertexData_GetMetaObject,
        igVertexData_className,
        0x24, /* instance size */
        igVertexData_GetVTable,
        &igVertexData_InitFields,
        0, /* extra callback item */
        g_igVertexData_callbackList /* callback list */
    );
}

void thunk_igVertexData_GetMetaObject(void) {
    igVertexData_GetMetaObject();
}

void igVertexData_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055fa58[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004886c0[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igDataList_GetOrCreateMetaObject();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_002dc7a0(temp_v0, &DAT_00488738[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_0014b330);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004886e0[0], &DAT_00488700[0], &DAT_00488720[0], temp_s2);
}

