void beNDMWStatusSelectE0_Create(int arg0) {
    FUN_003b5480();
    igMetaObject_CreateInstance(*(int *)0x58ABE0, arg0);
}

igMetaObject *FUN_003b53b0(void)
{
    igMetaObject *g = g_beNDMWStatusSelectE0_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003b5480();
    return g_beNDMWStatusSelectE0_metaObject[0];
}

int beNDMWStatusSelectE0_GetVTable(void) {
    struct W_3b5400 o;
    int r;

    igObject_InitHeader(&o);
    o.f[12] = 0;
    o.f[13] = 0;
    o.f[14] = 0;
    o.f[15] = 0;
    o.f[16] = 0;
    o.f[17] = 0;
    o.f[18] = 0;
    o.f[19] = 0;
    o.f[26] = 0;
    o.vt = DAT_0053f3a0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_0053f3a0;
    FUN_003b4050((struct S_3b4050 *)&o, (short)0);
    return r;
}

void FUN_003b5480(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelectE0_Register);
}

void *beNDMWStatusSelectE0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusSelectE0_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelectE0_GetMetaObject,
        beNDMWStatusSelectE0_className,
        0x70, /* instance size */
        beNDMWStatusSelectE0_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusSelectE0_GetMetaObject(void)
{
    FUN_003b53b0();
}

