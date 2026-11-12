void FUN_003b7a40(int arg0) {
    FUN_003b7b50();
    igMetaObject_CreateInstance(*(int *)0x58AD80, arg0);
}

S *FUN_003b7a80(void) {
    S *g = DAT_0058ad80[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_003b7b50();
done:
    return DAT_0058ad80[0];
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
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
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

