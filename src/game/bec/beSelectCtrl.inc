void FUN_00345a00(int arg0) {
    FUN_00345bc0();
    igMetaObject_CreateInstance(*(int *)0x587F98, arg0);
}

int FUN_00345a40(void) {
    if (((int *)DAT_00587f98)[0] == 0) {
        ((int *)DAT_00587f98)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00587f98)[0];
}

void *FUN_00345a90(void) {
    struct G *g = DAT_00587f98[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00345bc0();
    }
    return DAT_00587f98[0];
}

int beSelectCtrl_GetVTable(void) {
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
    u.vt = (int)&DAT_0053a0d0[0];
    q0 = (S_ref *)&u.b[24];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_0053b290[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
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

void FUN_00345bc0(void)
{
    igMetaObject_RunStaticInit(beSelectCtrl_Register);
}

void *beSelectCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSelectCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSelectCtrl_GetMetaObject,
        beSelectCtrl_className,
        0x28, /* instance size */
        beSelectCtrl_GetVTable,
        beSelectCtrl_InitFields,
        0, /* extra callback item */
        g_beSelectCtrl_callbackList /* callback list */
    );
}

void beSelectCtrl_GetMetaObject(void)
{
    FUN_00345a90();
}

void beSelectCtrl_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00587f98)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3b88[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c3b90[0], &DAT_004c3b98[0], &DAT_004c3ba0[0], temp_s2);
}

