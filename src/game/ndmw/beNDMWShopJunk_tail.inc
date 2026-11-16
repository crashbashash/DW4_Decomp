igMetaObject *g_beNDMWShopJunk_metaObject;
igMetaField *g_beNDMWShopJunk_junkMenuMetaField;
igMetaField *g_beNDMWShopJunk_totalGiftMetaField;
igMetaField *g_beNDMWShopJunk_junkItemListMetaField;

void beNDMWShopJunk_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopJunk_Register);
}

static igMetaObjectCallback g_beNDMWShopJunk_callbackList[] = { beNDMWItemBaseList_EnsureRegistered, 0 };

void *beNDMWShopJunk_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopJunk_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopJunk_GetMetaObjectFunction,
        "beNDMWShopJunk",
        0x60, /* instance size */
        beNDMWShopJunk_GetVTable,
        beNDMWShopJunk_InitFields,
        0, /* extra callback item */
        g_beNDMWShopJunk_callbackList /* callback list */
    );
}

void beNDMWShopJunk_GetMetaObjectFunction(void)
{
    beNDMWShopJunk_GetMetaObject();
}

