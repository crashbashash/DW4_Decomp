void beAction2InfoWork_CreateInstance(int arg0) {
    FUN_0036c4d0();
    igMetaObject_CreateInstance(*(int *)0x589E98, arg0);
}

igMetaObject *FUN_0036c2e0(void) {
    if (g_beAction2InfoWork_metaObject[0] == 0) {
        g_beAction2InfoWork_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beAction2InfoWork_metaObject[0];
}

igMetaObject *FUN_0036c330(void)
{
    igMetaObject *g = g_beAction2InfoWork_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0036c4d0();
    return g_beAction2InfoWork_metaObject[0];
}

int beAction2InfoWork_GetVTable(void) {
    union U_36c380 u;
    int temp_s;
    char *p184;
    char *p180;
    char *p176;
    char *p104;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_005343b0[0];
    p104 = &u.b[8];
    *(int *)p104 = 0;
    p176 = &u.b[80];
    *(int *)p176 = 0;
    p180 = &u.b[84];
    *(int *)p180 = 0;
    p184 = &u.b[88];
    *(int *)p184 = 0;
    *(int *)&u.b[92] = 0;
    temp_s = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_005343b0[0];
    FUN_00239200(&u.b[92], -1);
    FUN_001d21b0(p184, -1);
    FUN_001aaf00(p180, -1);
    FUN_0019ab10(p176, -1);
    FUN_0036c450((void **)p104, (short)(-1));
    return temp_s;
}

void **FUN_0036c450(void **arg0, short arg1) {
    S_temp_a0_36c450 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_36c450 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_0036c4d0(void)
{
    igMetaObject_RunStaticInit(beAction2InfoWork_Register);
}

void *beAction2InfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2InfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beAction2InfoWork_GetMetaObject,
        beAction2InfoWork_className,
        0x60, /* instance size */
        beAction2InfoWork_GetVTable,
        beAction2InfoWork_InitFields,
        0, /* extra callback item */
        g_beAction2InfoWork_callbackList /* callback list */
    );
}

void beAction2InfoWork_GetMetaObject(void)
{
    FUN_0036c330();
}

void beAction2InfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s1_4;
    void *temp_s1_5;
    void *temp_s0;

    temp_s0 = (void *)g_beAction2InfoWork_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7ec0[0], 0x15);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0036d9f0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0x11));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00138f20();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0x12));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_00139640();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0x13));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_001313d0();
    temp_s1_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0x14));
    ((igObjectRefMetaField *)temp_s1_5)->_metaObject = FUN_00135e60();
    igMetaObject_NameFields(temp_s0, &DAT_004c7f20[0], &DAT_004c7f80[0], &DAT_004c7fe0[0], temp_s2);
}

