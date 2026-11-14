void *FUN_0035e660(void) {
    igMetaObject *g = g_beHitLandDelivInfoRam_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035e7a0();
    }
    return g_beHitLandDelivInfoRam_metaObject[0];
}

int beHitLandDelivInfoRam_GetVTable(void) {
    union U_35e6b0 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;

    igObject_InitHeader(u.b);
    q1 = (S_ref *)&u.b[40];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00536230[0];
    q0 = (S_ref *)&u.b[44];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00536230[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&DAT_00539e90[0];
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}

void FUN_0035e7a0(void)
{
    igMetaObject_RunStaticInit(beHitLandDelivInfoRam_Register);
}

void *beHitLandDelivInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandDelivInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beHitLandDelivInfoRam_GetMetaObject,
        beHitLandDelivInfoRam_className,
        0x68, /* instance size */
        beHitLandDelivInfoRam_GetVTable,
        beHitLandDelivInfoRam_InitFields,
        0, /* extra callback item */
        g_beHitLandDelivInfoRam_callbackList /* callback list */
    );
}

void beHitLandDelivInfoRam_GetMetaObject(void)
{
    FUN_0035e660();
}

void beHitLandDelivInfoRam_InitFields(void) {
    void *temp_a0;
    int temp_s2;
    void *temp_s1;
    int va[3];
    int vb[3];
    int vc[3];
    void *temp_a0_3;
    void *temp_a0_2;
    void *temp_s0;

    temp_s0 = (void *)g_beHitLandDelivInfoRam_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beHitLandDelivInfoRam_ctorTable[0], 9);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196190();
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 3.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, 3 + temp_s2), 4.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, 4 + temp_s2), 4.0f);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    va[0] = 0;
    va[1] = 0;
    va[2] = 0;
    FUN_0018e470(temp_a0, va);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, 6 + temp_s2));
    vb[0] = 0;
    vb[1] = 0;
    vb[2] = 0;
    FUN_0018e470(temp_a0_2, vb);
    temp_a0_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, 7 + temp_s2));
    vc[0] = 0;
    vc[1] = 0;
    vc[2] = 0;
    FUN_0018e470(temp_a0_3, vc);
    igMetaObject_NameFields(temp_s0, &g_beHitLandDelivInfoRam_fieldTable[0], &DAT_004c67f0[0], &DAT_004c6820[0], temp_s2);
}

