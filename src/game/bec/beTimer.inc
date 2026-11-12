void FUN_00341340(int arg0) {
    FUN_00341500();
    igMetaObject_CreateInstance(*(int *)0x587C18, arg0);
}

igMetaObject *FUN_00341380(void) {
    if (g_beTimer_metaObject[0] == 0) {
        g_beTimer_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beTimer_metaObject[0];
}

void *FUN_003413d0(void) {
    igMetaObject *g = g_beTimer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00341500();
    }
    return g_beTimer_metaObject[0];
}

int beTimer_GetVTable(void) {
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
    u.vt = (int)&DAT_0053b930[0];
    q0 = (S_ref *)&u.b[28];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053b930[0];
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

void FUN_00341500(void)
{
    igMetaObject_RunStaticInit(beTimer_Register);
}

void *beTimer_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTimer_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beTimer_GetMetaObject,
        beTimer_className,
        0x28, /* instance size */
        beTimer_GetVTable,
        beTimer_InitFields,
        0, /* extra callback item */
        g_beTimer_callbackList /* callback list */
    );
}

void beTimer_GetMetaObject(void)
{
    FUN_003413d0();
}

void beTimer_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beTimer_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c33a0[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0035b770();
    ((igObjectRefMetaField *)temp_s1_3)->_refCounted = 0;
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = (int)FUN_003416b0();
    ((igRefMetaField *)temp_s1_4)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c33c0[0], &DAT_004c33e0[0], &DAT_004c3400[0], temp_s2);
}

