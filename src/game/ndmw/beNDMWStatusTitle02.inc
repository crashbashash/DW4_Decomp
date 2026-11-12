void FUN_003b3900(int arg0) {
    FUN_003b3a10();
    igMetaObject_CreateInstance(*(int *)0x58AB60, arg0);
}

igMetaObject *FUN_003b3940(void)
{
    igMetaObject *g = g_beNDMWStatusTitle02_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003b3a10();
    return g_beNDMWStatusTitle02_metaObject[0];
}

int beNDMWStatusTitle02_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.f[12] = 0;
    o.f[13] = 0;
    o.f[14] = 0;
    o.f[15] = 0;
    o.f[16] = 0;
    o.f[17] = 0;
    o.f[18] = 0;
    o.vt = DAT_0053f640;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_0053f640;
    FUN_003b3030((int **)&o, (long long)0);
    return r;
}

void FUN_003b3a10(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle02_Register);
}

void *beNDMWStatusTitle02_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusTitle02_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle02_GetMetaObject,
        beNDMWStatusTitle02_className,
        0x50, /* instance size */
        beNDMWStatusTitle02_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusTitle02_GetMetaObject(void)
{
    FUN_003b3940();
}

