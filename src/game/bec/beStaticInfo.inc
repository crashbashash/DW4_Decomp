void *FUN_00343a10(void) {
    igMetaObject *g = g_beStaticInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00343ad0();
    }
    return g_beStaticInfo_metaObject[0];
}

int beStaticInfo_GetVTable(void) {
    union U_343a60 u;
    int t;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_00539420[0];
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00539420[0];
    FUN_0033ec80((struct S_33ec80 *)u.b, (short)0);
    return t;
}

void FUN_00343ad0(void)
{
    igMetaObject_RunStaticInit(beStaticInfo_Register);
}

void *beStaticInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beStaticInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beStaticInfo_GetMetaObject,
        beStaticInfo_className,
        0x1c, /* instance size */
        beStaticInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beStaticInfo_GetMetaObject(void)
{
    FUN_00343a10();
}

