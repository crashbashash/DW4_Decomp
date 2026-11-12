void *FUN_00340af0(void) {
    unsigned char b;
    if (DAT_00587be0[0] != 0) {
        b = (*(int *)((char *)(DAT_00587be0[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00340bb0();
done:
    return DAT_00587be0[0];
}

int beWaterPlainInfo_GetVTable(void) {
    struct W_340b40 o;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    o.vt = DAT_005398d0;
    r = *(int *)((char *)&o + *(int *)(((char * *)DAT_00586dc8)[0] + 916));
    o.vt = DAT_005398d0;
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

void FUN_00340bb0(void)
{
    igMetaObject_RunStaticInit(beWaterPlainInfo_Register);
}

void *beWaterPlainInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWaterPlainInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beWaterPlainInfo_GetMetaObject,
        beWaterPlainInfo_className,
        0x1c, /* instance size */
        beWaterPlainInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beWaterPlainInfo_GetMetaObject(void)
{
    FUN_00340af0();
}

int FUN_00340c60(void) {
    if (DAT_00587be8[0] == 0) {
        DAT_00587be8[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c3348[0], &DAT_00587bf0[0], 1);
    }
    return DAT_00587be8[0];
}

