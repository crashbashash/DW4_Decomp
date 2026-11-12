SFUN_0035d4a0 *FUN_0035d4a0(void) {
    if (DAT_00589320[0] == 0 || !DAT_00589320[0]->ok()) FUN_0035d5a0();
    return DAT_00589320[0];
}

int beHitLandModelInfo_GetVTable(void) {
    struct Obj_35d4f0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_005363d0[0];
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_005363d0[0];
    FUN_00343260((ObjectRefWord *)&obj.w9, -1);
    FUN_00343260((ObjectRefWord *)&obj.w8, -1);
    FUN_0014aa70(&obj.w7, -1);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return t;
}

void FUN_0035d5a0(void)
{
    igMetaObject_RunStaticInit(beHitLandModelInfo_Register);
}

void *beHitLandModelInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandModelInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beHitLandModelInfo_GetMetaObject,
        beHitLandModelInfo_className,
        0x2c, /* instance size */
        beHitLandModelInfo_GetVTable,
        beHitLandModelInfo_InitFields,
        0, /* extra callback item */
        g_beHitLandModelInfo_callbackList /* callback list */
    );
}

void beHitLandModelInfo_GetMetaObject(void)
{
    FUN_0035d4a0();
}

void beHitLandModelInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589320)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6560[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196930();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00196930();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igObjectList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, &DAT_004c6570[0], &DAT_004c6580[0], &DAT_004c6590[0], temp_s2);
}

int FUN_0035d720(void) {
    if (DAT_00589348[0] == 0) {
        DAT_00589348[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c65a0[0], &DAT_004c65c0[0], 5);
    }
    return DAT_00589348[0];
}

