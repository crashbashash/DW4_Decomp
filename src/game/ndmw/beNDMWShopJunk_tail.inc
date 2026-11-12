void FUN_003b64f0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopJunk_Register);
}

void *beNDMWShopJunk_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopJunk_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopJunk_GetMetaObject,
        beNDMWShopJunk_className,
        0x60, /* instance size */
        beNDMWShopJunk_GetVTable,
        beNDMWShopJunk_InitFields,
        0, /* extra callback item */
        g_beNDMWShopJunk_callbackList /* callback list */
    );
}

void beNDMWShopJunk_GetMetaObject(void)
{
    FUN_003b6350();
}

