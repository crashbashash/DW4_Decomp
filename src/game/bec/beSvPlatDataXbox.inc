void *FUN_003472b0(void) {
    struct G *g = DAT_00588040[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003473f0();
    }
    return DAT_00588040[0];
}

int beSvPlatDataXbox_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;

    igObject_InitHeader(u.b);
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00538c80[0];
    q0 = (S_ref *)&u.b[36];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00538c80[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
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

void FUN_003473f0(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataXbox_Register);
}

void *beSvPlatDataXbox_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvPlatDataXbox_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataXbox_GetMetaObject,
        beSvPlatDataXbox_className,
        0x2c, /* instance size */
        beSvPlatDataXbox_GetVTable,
        beSvPlatDataXbox_InitFields,
        0, /* extra callback item */
        g_beSvPlatDataXbox_callbackList /* callback list */
    );
}

void beSvPlatDataXbox_GetMetaObject(void)
{
    FUN_003472b0();
}

void beSvPlatDataXbox_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    F_3474b0 *temp_s0;
    G_3474b0 *tg;
    void *temp_s1;
    T_3474b0 *temp_v0_2;

    temp_s1 = (void *)(((void * *)DAT_00588040)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c3d20[0], 4);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00502570[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T_3474b0 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002ea4b0(temp_v0_2, 9);
    temp_v0_2->f1c = &DAT_00588048[0];
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->refs = temp_v0_2->refs - 1;
    if (((unsigned long long) ((long long) temp_v0_2->refs << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (F_3474b0 *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    temp_s0->f56 = FUN_00347600();
    temp_s0->b52 = 1;
    tg = (G_3474b0 *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3);
    tg->w52 = 2;
    igMetaObject_NameFields(temp_s1, &DAT_004c3d30[0], &DAT_004c3d40[0], &DAT_004c3d50[0], temp_s2);
}

