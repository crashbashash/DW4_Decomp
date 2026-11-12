void *FUN_0036b1c0(void) {
    bool ok;
    if (g_beActionStarterInfoRam_metaObject[0] == 0) goto make;
    ok = !!(g_beActionStarterInfoRam_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_0036b2b0();
done:;
    return g_beActionStarterInfoRam_metaObject[0];
}

int beActionStarterInfoRam_GetVTable(void) {
    Obj_36b210 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.ref = 0;
    obj.vt = &DAT_00539e90[0];
    obj.vt = &DAT_00534680[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00539e90[0];
    obj.releaseRef();
    return r;
}

void FUN_0036b2b0(void)
{
    igMetaObject_RunStaticInit(beActionStarterInfoRam_Register);
}

void *beActionStarterInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beActionStarterInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beActionStarterInfoRam_GetMetaObject,
        beActionStarterInfoRam_className,
        0x2c, /* instance size */
        beActionStarterInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beActionStarterInfoRam_GetMetaObject(void)
{
    FUN_0036b1c0();
}

