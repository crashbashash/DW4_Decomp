void *FUN_003bcf40(void) {
    unsigned char b;
    if (g_beNDMWSaveCtrlInfo_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_beNDMWSaveCtrlInfo_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003bd000();
done:
    return g_beNDMWSaveCtrlInfo_metaObject[0];
}

int beNDMWSaveCtrlInfo_GetVTable(void) {
    Obj_3bcf90 o;
    int r;

    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f20 = 0;
    o.f24 = 0;
    o.vt = &DAT_0053d760[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_0053d760[0];
    FUN_0033ec80(&o, 0);
    return r;
}

void FUN_003bd000(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveCtrlInfo_Register);
}

void *beNDMWSaveCtrlInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWSaveCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWSaveCtrlInfo_GetMetaObject,
        beNDMWSaveCtrlInfo_className,
        0x1c, /* instance size */
        beNDMWSaveCtrlInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWSaveCtrlInfo_GetMetaObject(void)
{
    FUN_003bcf40();
}

