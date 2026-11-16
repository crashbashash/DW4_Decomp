igMetaObject *g_beNumberCtrl_metaObject;

void beNumberCtrl_CreateInstance(int allocator) {
    beNumberCtrl_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5886E0, allocator);
}

igMetaObject *beNumberCtrl_GetOrCreateMetaObject(void) {
    if (g_beNumberCtrl_metaObject == 0) {
        g_beNumberCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNumberCtrl_metaObject;
}

void *beNumberCtrl_GetMetaObject(void) {
    igMetaObject *g = g_beNumberCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNumberCtrl_EnsureRegistered();
    }
    return g_beNumberCtrl_metaObject;
}

int beNumberCtrl_GetVTable(void) {
    union U_34e440 u;
    int temp_s1;
    char *q1;
    int *tv1, *ta1;
    int tc1;
    igObject *q2;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&g_beBaseInfoManager_vtable[0]);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    q2 = (igObject *)&u.b[24];
    *(int *)q2 = 0;
    u.w[0] = (int)(&g_beNumberCtrl_vtable[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beBaseInfoManager_vtable[0]);
    if (q2 != 0) {
        q2 = *(igObject **)q2;
        if (q2 != 0) {
            q2->_refCount = (int)q2->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q2->_refCount << 0x29) >> 0x29) == 0) {
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

void beNumberCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNumberCtrl_Register);
}

void *beNumberCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumberCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNumberCtrl_GetMetaObjectFunction,
        "beNumberCtrl",
        0x20, /* instance size */
        beNumberCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNumberCtrl_GetMetaObjectFunction(void)
{
    beNumberCtrl_GetMetaObject();
}

