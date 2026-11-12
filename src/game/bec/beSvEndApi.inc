void FUN_003485f0(int arg0) {
    FUN_003487c0();
    igMetaObject_CreateInstance(*(int *)0x5881E0, arg0);
}

void *FUN_00348630(void) {
    struct G *g = DAT_005881e0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003487c0();
    }
    return DAT_005881e0[0];
}

int beSvEndApi_GetVTable(void) {
    Obj_348680 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053c070[0];
    obj.r1 = 0;
    obj.r2 = 0;
    obj.r3 = 0;
    obj.vt = &DAT_0053bc80[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053c070[0];
    obj.rel(&obj.r3);
    obj.rel(&obj.r2);
    obj.rel(&obj.r1);
    return r;
}

void FUN_003487c0(void)
{
    igMetaObject_RunStaticInit(beSvEndApi_Register);
}

void *beSvEndApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvEndApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvEndApi_GetMetaObject,
        beSvEndApi_className,
        0x40, /* instance size */
        beSvEndApi_GetVTable,
        beSvEndApi_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvEndApi_GetMetaObject(void)
{
    FUN_00348630();
}

void beSvEndApi_InitFields(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(((void * *)DAT_005881e0)[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_005027d8[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002ea4b0(temp_v0_2, 0xB);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_005881e8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_v0_2);
    ((SR *)temp_v0_2)->f4 = ((SR *)temp_v0_2)->f4 - 1;
    if ((((SR *)temp_v0_2)->f4 & 0x7FFFFF) == 0) {
        igObject_Destroy(temp_v0_2);
    }
}

