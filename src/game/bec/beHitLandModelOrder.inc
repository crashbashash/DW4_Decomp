void FUN_0035de90(int arg0) {
    FUN_0035e090();
    igMetaObject_CreateInstance(*(int *)0x589390, arg0);
}

igMetaObject *FUN_0035ded0(void) {
    if (g_beHitLandModelOrder_metaObject[0] == 0) {
        g_beHitLandModelOrder_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beHitLandModelOrder_metaObject[0];
}

void *FUN_0035df20(void) {
    bool ok;
    if (g_beHitLandModelOrder_metaObject[0] == 0) goto make;
    ok = !!(g_beHitLandModelOrder_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_0035e090();
done:;
    return g_beHitLandModelOrder_metaObject[0];
}

int beHitLandModelOrder_GetVTable(void) {
    union U_35df70 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    char *q2;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053a7a0[0];
    q2 = &u.b[32];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[48];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[56];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053a7a0[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    if (q2 != 0) {
        temp_v1 = *(int **)q2;
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

void FUN_0035e090(void)
{
    igMetaObject_RunStaticInit(beHitLandModelOrder_Register);
}

void *beHitLandModelOrder_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandModelOrder_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beHitLandModelOrder_GetMetaObject,
        beHitLandModelOrder_className,
        0x3c, /* instance size */
        beHitLandModelOrder_GetVTable,
        beHitLandModelOrder_InitFields,
        0, /* extra callback item */
        g_beHitLandModelOrder_callbackList /* callback list */
    );
}

void beHitLandModelOrder_GetMetaObject(void)
{
    FUN_0035df20();
}

void beHitLandModelOrder_InitFields(void) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_s1;
    int temp_s2;
    void *temp_s1_2;
    void *temp_s0;
    int sp50[3];
    int sp40[3];

    temp_s0 = (void *)g_beHitLandModelOrder_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beHitLandModelOrder_ctorTable[0], 9);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2), &DAT_00502a98[0]);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    sp50[0] = 0;
    sp50[1] = 0;
    sp50[2] = 0;
    FUN_0018e470(temp_a0, sp50);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    sp40[0] = 0;
    sp40[1] = 0;
    sp40[2] = 0;
    FUN_0018e470(temp_a0_2, sp40);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    *(int *)((char *)(temp_s1) + 56) = FUN_001880b0();
    *(char *)((char *)(temp_s1) + 52) = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    *(int *)((char *)(temp_s1_2) + 56) = (int)FUN_0035e270();
    *(char *)((char *)(temp_s1_2) + 52) = 1;
    igMetaObject_NameFields(temp_s0, &g_beHitLandModelOrder_fieldTable[0], &DAT_004c6700[0], &DAT_004c6730[0], temp_s2);
}

