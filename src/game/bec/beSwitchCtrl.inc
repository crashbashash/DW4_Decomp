void FUN_00343490(int arg0) {
    FUN_00343650();
    igMetaObject_CreateInstance(*(int *)0x587DF8, arg0);
}

igMetaObject *FUN_003434d0(void) {
    if (g_beSwitchCtrl_metaObject[0] == 0) {
        g_beSwitchCtrl_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beSwitchCtrl_metaObject[0];
}

void *FUN_00343520(void) {
    igMetaObject *g = g_beSwitchCtrl_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00343650();
    }
    return g_beSwitchCtrl_metaObject[0];
}

int beSwitchCtrl_GetVTable(void) {
    union U_343570 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_0053a0d0[0];
    q0 = (S_ref *)&u.b[24];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_0053b470[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053a0d0[0];
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

void FUN_00343650(void)
{
    igMetaObject_RunStaticInit(beSwitchCtrl_Register);
}

void *beSwitchCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSwitchCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSwitchCtrl_GetMetaObject,
        beSwitchCtrl_className,
        0x20, /* instance size */
        beSwitchCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSwitchCtrl_GetMetaObject(void)
{
    FUN_00343520();
}

int FUN_00343700(void) {
    if (DAT_00587e00[0] == 0) {
        DAT_00587e00[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c3790[0], &DAT_00587e08[0], 1);
    }
    return DAT_00587e00[0];
}

