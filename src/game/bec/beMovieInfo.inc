void *FUN_0034eb10(void) {
    struct G *g = DAT_00588758[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034ebd0();
    }
    return DAT_00588758[0];
}

int beMovieInfo_GetVTable(void) {
    struct W_34eb60 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[4] = 0;
    o.w[5] = 0;
    o.vt = DAT_005380a0;
    r = *(int *)((char *)&o + *(int *)(((char * *)DAT_00586dc8)[0] + 916));
    o.vt = DAT_005380a0;
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

void FUN_0034ebd0(void)
{
    igMetaObject_RunStaticInit(beMovieInfo_Register);
}

void *beMovieInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMovieInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beMovieInfo_GetMetaObject,
        beMovieInfo_className,
        0x1c, /* instance size */
        beMovieInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beMovieInfo_GetMetaObject(void)
{
    FUN_0034eb10();
}

