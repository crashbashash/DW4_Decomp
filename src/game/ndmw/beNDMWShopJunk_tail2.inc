static FieldFactory g_beNDMWShopJunk_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWShopJunk_fieldTable[] = {
    "_junkMenu",
    "_totalGift",
    "_junkItemList",
};
static igMetaField **g_beNDMWShopJunk_fieldHandles[] = {
    &g_beNDMWShopJunk_junkMenuMetaField,
    &g_beNDMWShopJunk_totalGiftMetaField,
    &g_beNDMWShopJunk_junkItemListMetaField,
};
static int g_beNDMWShopJunk_fieldOffsets[] = {
    84,
    88,
    92,
};

void beNDMWShopJunk_InitFields(void) {
    int base;
    void *junkItemList;
    igMetaObject *meta;

    meta = g_beNDMWShopJunk_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopJunk_ctorTable, 3);
    junkItemList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)junkItemList)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWShopJunk_fieldTable, g_beNDMWShopJunk_fieldHandles, g_beNDMWShopJunk_fieldOffsets, base);
}

