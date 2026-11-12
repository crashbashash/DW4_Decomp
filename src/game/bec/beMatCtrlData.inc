void *FUN_0035a430(void) {
    igMetaObject *g = g_beMatCtrlData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035a560();
    }
    return g_beMatCtrlData_metaObject[0];
}

int beMatCtrlData_GetVTable(void) {
    union U_35a480 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_005369d0[0];
    q0 = (S_ref *)&u.b[12];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_005369d0[0];
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

void FUN_0035a560(void)
{
    igMetaObject_RunStaticInit(beMatCtrlData_Register);
}

void *beMatCtrlData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMatCtrlData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beMatCtrlData_GetMetaObject,
        beMatCtrlData_className,
        0x10, /* instance size */
        beMatCtrlData_GetVTable,
        beMatCtrlData_InitFields,
        0, /* extra callback item */
        g_beMatCtrlData_callbackList /* callback list */
    );
}

void beMatCtrlData_GetMetaObject(void)
{
    FUN_0035a430();
}

void beMatCtrlData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMatCtrlData_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6108[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0018a6a0();
    igMetaObject_NameFields(temp_s0, &DAT_004c6110[0], &DAT_004c6118[0], &DAT_004c6120[0], temp_s2);
}

int FUN_0035a6b0(void) {
    if (DAT_00589158[0] == 0) {
        DAT_00589158[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c6130[0], &DAT_004c6150[0], 6);
    }
    return DAT_00589158[0];
}

