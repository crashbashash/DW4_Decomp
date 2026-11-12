void FUN_00342970(int arg0) {
    FUN_00342b00();
    igMetaObject_CreateInstance(*(int *)0x587CE8, arg0);
}

int FUN_003429b0(void) {
    if (((int *)DAT_00587ce8)[0] == 0) {
        ((int *)DAT_00587ce8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00587ce8)[0];
}

void *FUN_00342a00(void) {
    struct G *g = DAT_00587ce8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00342b00();
    }
    return DAT_00587ce8[0];
}

int beTargetObj_GetVTable(void) {
    union U_342a50 u;
    int temp_s2;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[0] = (int)(&DAT_0053ba50[0]);
    u.w[4] = 0;
    u.w[5] = 0;
    u.w[6] = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0053ba50[0]);
    FUN_001374b0(&u.w[6], -1);
    ObjectRef_Destruct_00150eb0(&u.w[5], -1);
    FUN_001374b0(&u.w[4], -1);
    FUN_00231030(u.b, 0);
    return temp_s2;
}

void FUN_00342b00(void)
{
    igMetaObject_RunStaticInit(beTargetObj_Register);
}

void *beTargetObj_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTargetObj_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beTargetObj_GetMetaObject,
        beTargetObj_className,
        0x1c, /* instance size */
        beTargetObj_GetVTable,
        beTargetObj_InitFields,
        0, /* extra callback item */
        g_beTargetObj_callbackList /* callback list */
    );
}

void beTargetObj_GetMetaObject(void)
{
    FUN_00342a00();
}

void beTargetObj_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00587ce8)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3540[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0018a0a0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0018a0a0();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c3550[0], &DAT_004c3560[0], &DAT_004c3570[0], temp_s2);
}

