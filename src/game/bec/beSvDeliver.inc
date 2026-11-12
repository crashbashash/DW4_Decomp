int FUN_0034b0d0(void) {
    if (((int *)DAT_005883c8)[0] == 0) {
        ((int *)DAT_005883c8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_005883c8)[0];
}

SFUN_0034b120 *FUN_0034b120(void) {
    if (DAT_005883c8[0] == 0 || !DAT_005883c8[0]->ok()) FUN_0034b260();
    return DAT_005883c8[0];
}

int beSvDeliver_GetVTable(void) {
    union U_34b170 u;
    int temp_s5;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_005388b0[0]);
    u.w[3] = 0;
    u.w[12] = 0;
    u.w[13] = 0;
    u.w[14] = 0;
    u.w[15] = 0;
    u.w[16] = 0;
    temp_s5 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_005388b0[0]);
    FUN_00349080((void **)(&u.w[16]), (long long)(-1));
    ObjectRef_Destruct_00150eb0(&u.w[15], -1);
    ObjectRef_Destruct_00150eb0(&u.w[14], -1);
    ObjectRef_Destruct_00150eb0(&u.w[13], -1);
    ObjectRef_Destruct_00150eb0(&u.w[12], -1);
    ObjectRef_Destruct_00150eb0(&u.w[3], -1);
    return temp_s5;
}

void FUN_0034b260(void)
{
    igMetaObject_RunStaticInit(beSvDeliver_Register);
}

void *beSvDeliver_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvDeliver_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSvDeliver_GetMetaObject,
        beSvDeliver_className,
        0x44, /* instance size */
        beSvDeliver_GetVTable,
        beSvDeliver_InitFields,
        0, /* extra callback item */
        g_beSvDeliver_callbackList /* callback list */
    );
}

void beSvDeliver_GetMetaObject(void)
{
    FUN_0034b120();
}

void beSvDeliver_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s1;

    temp_s1 = (void *)((int *)DAT_005883c8)[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c43c0[0], 0x12);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    FUN_002d4e40(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7), -1);
    FUN_002d4e40(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8), 0);
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xD));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xE));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xF));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x10));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_0034aeb0();
    ((igObjectRefMetaField *)temp_s2_6)->_refCounted = 0;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x11));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_0034a210();
    igMetaObject_NameFields(temp_s1, &DAT_004c4410[0], &DAT_004c4460[0], &DAT_004c44b0[0], temp_s0);
}

