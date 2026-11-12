S_35d300 *FUN_0035d300(void) {
    S_35d300 *g = DAT_00589318[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_0035d3f0();
done:
    return DAT_00589318[0];
}

int beHitLandModelInfoRam_GetVTable(void) {
    Obj_35d350 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.ref = 0;
    obj.vt = &DAT_00539e90[0];
    obj.vt = &DAT_00536440[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
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

