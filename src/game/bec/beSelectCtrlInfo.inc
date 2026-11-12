void *FUN_00345170(void) {
    unsigned char b;
    if (g_beSelectCtrlInfo_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_beSelectCtrlInfo_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00345230();
done:
    return g_beSelectCtrlInfo_metaObject[0];
}

int beSelectCtrlInfo_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.w[4] = 0;
    f.w[5] = 0;
    f.vt = &DAT_005390d0[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &DAT_005390d0[0];
    FUN_0033ec80((struct S_33ec80 *)&f, (short)0);
    return temp_s0;
}

void FUN_00345230(void)
{
    igMetaObject_RunStaticInit(beSelectCtrlInfo_Register);
}

void *beSelectCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSelectCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSelectCtrlInfo_GetMetaObject,
        beSelectCtrlInfo_className,
        0x1c, /* instance size */
        beSelectCtrlInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSelectCtrlInfo_GetMetaObject(void)
{
    FUN_00345170();
}

