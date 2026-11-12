igMetaObject *FUN_0036a230(void) {
    if (g_beBaseInfoRam_metaObject[0] == 0) {
        g_beBaseInfoRam_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beBaseInfoRam_metaObject[0];
}

void *FUN_0036a280(void) {
    igMetaObject *g = g_beBaseInfoRam_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0036a360();
    }
    return g_beBaseInfoRam_metaObject[0];
}

int beBaseInfoRam_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader(u.b);
    p = (S_ref *)&u.b[40];
    u.vt = (int)&DAT_00539e90[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00539e90[0];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return temp_s0;
}

void FUN_0036a360(void)
{
    igMetaObject_RunStaticInit(beBaseInfoRam_Register);
}

void *beBaseInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBaseInfoRam_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beBaseInfoRam_GetMetaObject,
        beBaseInfoRam_className,
        0x2c, /* instance size */
        beBaseInfoRam_GetVTable,
        beBaseInfoRam_InitFields,
        0, /* extra callback item */
        g_beBaseInfoRam_callbackList /* callback list */
    );
}

void beBaseInfoRam_GetMetaObject(void)
{
    FUN_0036a280();
}

void beBaseInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beBaseInfoRam_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7bb0[0], 9);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0036ac80();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0036a8d0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0036aec0();
    igMetaObject_NameFields(temp_s0, &DAT_004c7be0[0], &DAT_004c7c10[0], &DAT_004c7c40[0], temp_s2);
}

