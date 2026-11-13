void beActionStarter_CreateInstance(int arg0) {
    FUN_0036c1f0();
    igMetaObject_CreateInstance(*(int *)0x589E90, arg0);
}

igMetaObject *FUN_0036c070(void) {
    if (g_beActionStarter_metaObject[0] == 0) {
        g_beActionStarter_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beActionStarter_metaObject[0];
}

void *FUN_0036c0c0(void) {
    igMetaObject *g = g_beActionStarter_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0036c1f0();
    }
    return g_beActionStarter_metaObject[0];
}

int beActionStarter_GetVTable(void) {
    union U_36c110 u;
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
    u.vt = (int)&DAT_0053a030[0];
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

void FUN_0036c1f0(void)
{
    igMetaObject_RunStaticInit(beActionStarter_Register);
}

void *beActionStarter_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beActionStarter_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beActionStarter_GetMetaObject,
        beActionStarter_className,
        0x20, /* instance size */
        beActionStarter_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beActionStarter_GetMetaObject(void)
{
    FUN_0036c0c0();
}

