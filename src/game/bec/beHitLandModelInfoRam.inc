igMetaObject *FUN_0035d300(void) {
    igMetaObject *g = g_beHitLandModelInfoRam_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_0035d3f0();
done:
    return g_beHitLandModelInfoRam_metaObject[0];
}

int beHitLandModelInfoRam_GetVTable(void) {
    Obj_35d350 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.ref = 0;
    obj.vt = &DAT_00539e90[0];
    obj.vt = &DAT_00536440[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00539e90[0];
    obj.releaseRef();
    return r;
}

void FUN_0035d3f0(void)
{
    igMetaObject_RunStaticInit(beHitLandModelInfoRam_Register);
}

void *beHitLandModelInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandModelInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beHitLandModelInfoRam_GetMetaObject,
        beHitLandModelInfoRam_className,
        0x2c, /* instance size */
        beHitLandModelInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beHitLandModelInfoRam_GetMetaObject(void)
{
    FUN_0035d300();
}

