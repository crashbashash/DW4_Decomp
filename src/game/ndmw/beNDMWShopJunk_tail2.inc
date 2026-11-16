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
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWShopJunk_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWShopJunk_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beNDMWShopJunk_fieldTable, g_beNDMWShopJunk_fieldHandles, g_beNDMWShopJunk_fieldOffsets, temp_s2);
}

