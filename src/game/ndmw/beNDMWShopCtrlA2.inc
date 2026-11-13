void beNDMWShopCtrlA2_Create(int arg0) {
    FUN_003b7b50();
    igMetaObject_CreateInstance(*(int *)0x58AD80, arg0);
}

igMetaObject *FUN_003b7a80(void) {
    igMetaObject *g = g_beNDMWShopCtrlA2_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_003b7b50();
done:
    return g_beNDMWShopCtrlA2_metaObject[0];
}

int beNDMWShopCtrlA2_GetVTable(void) {
    struct Obj_3b7ad0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.vt = &DAT_0053fbb0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053fbb0[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return t;
}

void FUN_003b7b50(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlA2_Register);
}

void *beNDMWShopCtrlA2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlA2_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlA2_GetMetaObject,
        beNDMWShopCtrlA2_className,
        0x54, /* instance size */
        beNDMWShopCtrlA2_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrlA2_GetMetaObject(void)
{
    FUN_003b7a80();
}

