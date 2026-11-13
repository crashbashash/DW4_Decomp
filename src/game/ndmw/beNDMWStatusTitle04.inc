void beNDMWStatusTitle04_Create(int arg0) {
    FUN_003b3640();
    igMetaObject_CreateInstance(*(int *)0x58AB50, arg0);
}

void *FUN_003b3570(void) {
    igMetaObject *g = g_beNDMWStatusTitle04_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b3640();
    }
    return g_beNDMWStatusTitle04_metaObject[0];
}

int beNDMWStatusTitle04_GetVTable(void) {
    Obj_3b35c0 o;
    int r;

    igObject_InitHeader(&o);
    o.w[12] = 0;
    o.w[13] = 0;
    o.w[14] = 0;
    o.w[15] = 0;
    o.w[16] = 0;
    o.w[17] = 0;
    o.w[18] = 0;
    o.vt = &DAT_0053f560[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_0053f560[0];
    FUN_003b3030((int **)&o, (long long)0);
    return r;
}

void FUN_003b3640(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle04_Register);
}

void *beNDMWStatusTitle04_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusTitle04_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle04_GetMetaObject,
        beNDMWStatusTitle04_className,
        0x50, /* instance size */
        beNDMWStatusTitle04_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusTitle04_GetMetaObject(void)
{
    FUN_003b3570();
}

