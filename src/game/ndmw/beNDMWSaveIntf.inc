void FUN_003bcc80(int arg0) {
    FUN_003bcdd0();
    igMetaObject_CreateInstance(*(int *)0x58B160, arg0);
}

int FUN_003bccc0(void) {
    if (((int *)DAT_0058b160)[0] == 0) {
        ((int *)DAT_0058b160)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058b160)[0];
}

void *FUN_003bcd10(void) {
    struct G *g = DAT_0058b160[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bcdd0();
    }
    return DAT_0058b160[0];
}

int beNDMWSaveIntf_GetVTable(void) {
    struct F_3bcd60 f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.w[5] = 0;
    f.vt = &DAT_0053eb80[0];
    f.w[8] = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_0053eb80[0];
    FUN_0033dda0(&f.w[8], -1);
    FUN_0033f5e0(&f, 0);
    return temp_s0;
}

void FUN_003bcdd0(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntf_Register);
}

void *beNDMWSaveIntf_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWSaveIntf_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWSaveIntf_GetMetaObject,
        beNDMWSaveIntf_className,
        0x2c, /* instance size */
        beNDMWSaveIntf_GetVTable,
        beNDMWSaveIntf_InitFields,
        0, /* extra callback item */
        g_beNDMWSaveIntf_callbackList /* callback list */
    );
}

void beNDMWSaveIntf_GetMetaObject(void)
{
    FUN_003bcd10();
}

void beNDMWSaveIntf_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058b160)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca350[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004ca360[0], &DAT_004ca370[0], &DAT_004ca380[0], temp_s2);
}

