igMetaObject *g_beLightCtrl_metaObject;

void beLightCtrl_CreateInstance(int arg0) {
    beLightCtrl_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589258, arg0);
}

igMetaObject *beLightCtrl_GetOrCreateMetaObject(void) {
    if (g_beLightCtrl_metaObject == 0) {
        g_beLightCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beLightCtrl_metaObject;
}

void *beLightCtrl_GetMetaObject(void) {
    unsigned char b;
    if (((void * *)&g_beLightCtrl_metaObject)[0] != 0) {
        b = (*(int *)((char *)(((void * *)&g_beLightCtrl_metaObject)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    beLightCtrl_EnsureRegistered();
done:
    return ((void * *)&g_beLightCtrl_metaObject)[0];
}

int beLightCtrl_GetVTable(void) {
    union U_35c0f0 u;
    int temp_s1;
    char *q1;
    int *tv1, *ta1;
    int tc1;
    S_ref *q2;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&g_beBaseInfoManager_vtable[0]);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[24];
    *(int *)q2 = 0;
    u.w[0] = (int)(&g_beLightCtrl_vtable[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beBaseInfoManager_vtable[0]);
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
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

void beLightCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLightCtrl_Register);
}

void *beLightCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLightCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beLightCtrl_GetMetaObjectFunction,
        "beLightCtrl",
        0x20, /* instance size */
        beLightCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLightCtrl_GetMetaObjectFunction(void)
{
    beLightCtrl_GetMetaObject();
}

