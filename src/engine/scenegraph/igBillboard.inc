igMetaObject *igBillboard_GetMetaObject(void)
{
    igMetaObject *g = g_igBillboard_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a5050();
    return g_igBillboard_metaObject[0];
}

int igBillboard_GetVTable(void) {
    union U_1a4fd0 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[3] = 0;
    u.w[4] = 0;
    u.w[7] = 0;
    u.w[0] = (int)(&DAT_0052a2a0[0]);
    u.w[15] = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052a2a0[0]);
    FUN_00142d10(&u.w[15], -1);
    FUN_00195a90((struct T_195a90 *)&u.w[0], 0);
    return temp_s0;
}

void FUN_001a5050(void)
{
    igMetaObject_RunStaticInit(igBillboard_Register);
}

void igBillboard_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igBillboard_metaObject),
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igBillboard_GetMetaObject,
        igBillboard_className,
        0x40, /* instance size */
        igBillboard_GetVTable,
        &igBillboard_InitFields,
        0, /* extra callback item */
        g_igBillboard_callbackList /* callback list */
    );
}

void thunk_igBillboard_GetMetaObject(void) {
    igBillboard_GetMetaObject();
}

void igBillboard_InitFields(void) {
    float spA[4];
    float spB[4];
    int temp_s2;
    void *temp_s1;
    void *temp_a0_2;
    void *temp_a0;
    void *temp_s0;

    temp_s0 = (void *)DAT_00561f68[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048cbc0[0], 4);
    temp_a0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    spA[0] = 0;
    spA[2] = 1.0f;
    spA[1] = 0;
    FUN_0018e470(temp_a0, spA);
    temp_a0_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2)));
    spB[0] = 0;
    spB[1] = 0;
    spB[2] = 0;
    FUN_0018e470(temp_a0_2, spB);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3)));
    *(int *)((char *)(temp_s1) + 56) = FUN_001356f0();
    *(char *)((char *)(temp_s1) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_0048cbd0[0], &DAT_0048cbe0[0], &DAT_0048cbf0[0], temp_s2);
}

