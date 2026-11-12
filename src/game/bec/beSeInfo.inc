void *FUN_00345d30(void) {
    struct G *g = DAT_00587fb0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00345df0();
    }
    return DAT_00587fb0[0];
}

int beSeInfo_GetVTable(void) {
    struct W_345d80 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[4] = 0;
    o.w[5] = 0;
    o.vt = DAT_00538fa0;
    r = *(int *)((char *)&o + *(int *)(((char * *)DAT_00586dc8)[0] + 916));
    o.vt = DAT_00538fa0;
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

void FUN_00345df0(void)
{
    igMetaObject_RunStaticInit(beSeInfo_Register);
}

void *beSeInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSeInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSeInfo_GetMetaObject,
        beSeInfo_className,
        0x1c, /* instance size */
        beSeInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSeInfo_GetMetaObject(void)
{
    FUN_00345d30();
}

