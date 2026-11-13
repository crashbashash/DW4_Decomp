igMetaObject *FUN_003658e0(void) {
    if (g_beDataBase_metaObject[0] == 0) {
        g_beDataBase_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beDataBase_metaObject[0];
}

void *FUN_00365930(void) {
    igMetaObject *g = g_beDataBase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00365b00();
    }
    return g_beDataBase_metaObject[0];
}

int beDataBase_GetVTable(void) {
    union U_365980 u;
    int temp_s5;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00535160[0]);
    u.w[2] = 0;
    u.w[3] = 0;
    u.w[4] = 0;
    u.w[5] = 0;
    u.w[6] = 0;
    u.w[7] = 0;
    u.w[8] = 0;
    u.w[9] = 0;
    u.w[10] = 0;
    u.w[11] = 0;
    u.w[12] = 0;
    u.w[13] = 0;
    temp_s5 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00535160[0]);
    FUN_00199450(&u.w[13], -1);
    FUN_00199450(&u.w[12], -1);
    FUN_00226990(&u.w[11], -1);
    FUN_00199450(&u.w[10], -1);
    FUN_001354b0(&u.w[9], -1);
    FUN_00199450(&u.w[8], -1);
    ObjectRef_Destruct_00150eb0(&u.w[7], -1);
    FUN_00199450(&u.w[6], -1);
    FUN_001648f0(&u.w[5], -1);
    FUN_00199450(&u.w[4], -1);
    FUN_00164970(&u.w[3], -1);
    FUN_00199450(&u.w[2], -1);
    return temp_s5;
}

void FUN_00365b00(void)
{
    igMetaObject_RunStaticInit(beDataBase_Register);
}

void *beDataBase_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataBase_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beDataBase_GetMetaObject,
        beDataBase_className,
        0x38, /* instance size */
        beDataBase_GetVTable,
        beDataBase_InitFields,
        0, /* extra callback item */
        g_beDataBase_callbackList /* callback list */
    );
}

void beDataBase_GetMetaObject(void)
{
    FUN_00365930();
}

void beDataBase_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_11;
    void *temp_s2_12;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s0;

    temp_s0 = (void *)g_beDataBase_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beDataBase_ctorTable[0], 0xC);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_002caea0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_002c9dc0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_002c9780();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_002cb110();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    temp_s2_11 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_12 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s2_12)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beDataBase_fieldTable[0], &DAT_004c72c0[0], &DAT_004c72f0[0], temp_s1);
}

