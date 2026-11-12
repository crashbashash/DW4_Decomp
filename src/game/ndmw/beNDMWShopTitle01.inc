void FUN_003b31b0(int arg0) {
    FUN_003b32c0();
    igMetaObject_CreateInstance(*(int *)0x58AB40, arg0);
}

void *FUN_003b31f0(void) {
    struct G *g = DAT_0058ab40[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b32c0();
    }
    return DAT_0058ab40[0];
}

int beNDMWShopTitle01_GetVTable(void) {
    struct Obj_3b3240 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[12] = 0;
    obj.w[13] = 0;
    obj.w[14] = 0;
    obj.w[15] = 0;
    obj.w[16] = 0;
    obj.w[17] = 0;
    obj.w[18] = 0;
    obj.vt = &DAT_00540370[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00540370[0];
    FUN_003b3030((int **)&obj, (long long)0);
    return r;
}

void FUN_003b32c0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopTitle01_Register);
}

void *beNDMWShopTitle01_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopTitle01_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWShopTitle01_GetMetaObject,
        beNDMWShopTitle01_className,
        0x50, /* instance size */
        beNDMWShopTitle01_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopTitle01_GetMetaObject(void)
{
    FUN_003b31f0();
}

