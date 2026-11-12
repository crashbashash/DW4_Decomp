void *FUN_00347e20(void) {
    struct G *g = DAT_00588160[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00347f50();
    }
    return DAT_00588160[0];
}

int beSvPlatDataGC_GetVTable(void) {
    union U_347e70 u;
    int temp_s0;
    char *q0;
    S_ref *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00538b00[0];
    q0 = &u.b[104];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00538b00[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    u.vt = (int)&DAT_00538d40[0];
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

void FUN_00347f50(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataGC_Register);
}

void *beSvPlatDataGC_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvPlatDataGC_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataGC_GetMetaObject,
        beSvPlatDataGC_className,
        0x8c, /* instance size */
        beSvPlatDataGC_GetVTable,
        beSvPlatDataGC_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvPlatDataGC_GetMetaObject(void)
{
    FUN_00347e20();
}

void beSvPlatDataGC_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    H *temp_s0;
    G_348000 *tg;
    H *temp_s0_2;
    void *temp_s1;
    T_348000 *temp_v0_2;

    temp_s1 = (void *)(((void * *)DAT_00588160)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c3f30[0], 0xD);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00502570[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T_348000 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002ea4b0(temp_v0_2, 2);
    temp_v0_2->f1c = &DAT_00588168[0];
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->refs = temp_v0_2->refs - 1;
    if (((unsigned long long) ((long long) temp_v0_2->refs << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    tg = (G_348000 *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2);
    tg->w52 = 2;
    temp_s0 = (H *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 9));
    temp_s0->f60 = FUN_002cc2c0();
    temp_s0_2 = (H *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xB));
    temp_s0_2->f60 = FUN_002cc2c0();
    tg = (G_348000 *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xC);
    tg->w52 = 0x40;
    igMetaObject_NameFields(temp_s1, &DAT_004c3f70[0], &DAT_004c3fb0[0], &DAT_004c3ff0[0], temp_s2);
}

