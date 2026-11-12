void *FUN_00346ab0(void) {
    struct G *g = DAT_00588010[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00346b70();
    }
    return DAT_00588010[0];
}

int beSaveUtilInfo_GetVTable(void) {
    struct Obj_346b00 o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f20 = 0;
    o.f24 = 0;
    o.vt = &DAT_00538da0[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00538da0[0];
    
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

void FUN_00346b70(void)
{
    igMetaObject_RunStaticInit(beSaveUtilInfo_Register);
}

void *beSaveUtilInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSaveUtilInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSaveUtilInfo_GetMetaObject,
        beSaveUtilInfo_className,
        0x1c, /* instance size */
        beSaveUtilInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSaveUtilInfo_GetMetaObject(void)
{
    FUN_00346ab0();
}

int FUN_00346c20(void) {
    if (DAT_00588018[0] == 0) {
        DAT_00588018[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c3c50[0], &DAT_004c3ca0[0], 0x12);
    }
    return DAT_00588018[0];
}

