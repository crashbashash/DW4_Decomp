void FUN_0035c010(int arg0) {
    FUN_0035c1d0();
    igMetaObject_CreateInstance(*(int *)0x589258, arg0);
}

int FUN_0035c050(void) {
    if (DAT_00589258[0] == 0) {
        DAT_00589258[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00589258[0];
}

void *FUN_0035c0a0(void) {
    unsigned char b;
    if (((void * *)DAT_00589258)[0] != 0) {
        b = (*(int *)((char *)(((void * *)DAT_00589258)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0035c1d0();
done:
    return ((void * *)DAT_00589258)[0];
}

int beLightCtrl_GetVTable(void) {
    union U_35c0f0 u;
    int temp_s1;
    char *q1;
    int *tv1, *ta1;
    int tc1;
    S_ref *q2;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_0053a0d0[0]);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[24];
    *(int *)q2 = 0;
    u.w[0] = (int)(&DAT_0053c260[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0053a0d0[0]);
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    u.w[0] = (int)(&DAT_00524950[0]);
    if (q1 != 0) {
        tv1 = *(int **)q1;
        if (tv1 != 0) {
            ta1 = tv1 - 2;
            tc1 = tv1[-1] - 1;
            tv1[-1] = tc1;
            if (tc1 == 0) {
                StringChunk_ReleaseHeader(*ta1, ta1);
            }
        }
    }
    return temp_s1;
}

void FUN_0035c1d0(void)
{
    igMetaObject_RunStaticInit(beLightCtrl_Register);
}

void *beLightCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLightCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beLightCtrl_GetMetaObject,
        beLightCtrl_className,
        0x20, /* instance size */
        beLightCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLightCtrl_GetMetaObject(void)
{
    FUN_0035c0a0();
}

