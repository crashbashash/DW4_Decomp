void FUN_0034e360(int arg0) {
    FUN_0034e520();
    igMetaObject_CreateInstance(*(int *)0x5886E0, arg0);
}

igMetaObject *FUN_0034e3a0(void) {
    if (g_beNumberCtrl_metaObject[0] == 0) {
        g_beNumberCtrl_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNumberCtrl_metaObject[0];
}

void *FUN_0034e3f0(void) {
    igMetaObject *g = g_beNumberCtrl_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034e520();
    }
    return g_beNumberCtrl_metaObject[0];
}

int beNumberCtrl_GetVTable(void) {
    union U_34e440 u;
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
    u.w[0] = (int)(&DAT_0053b890[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
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

void FUN_0034e520(void)
{
    igMetaObject_RunStaticInit(beNumberCtrl_Register);
}

void *beNumberCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumberCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNumberCtrl_GetMetaObject,
        beNumberCtrl_className,
        0x20, /* instance size */
        beNumberCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNumberCtrl_GetMetaObject(void)
{
    FUN_0034e3f0();
}

