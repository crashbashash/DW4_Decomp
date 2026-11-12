void beNDMWShopJunk_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058ac88)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c98f8[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003c9130();
    igMetaObject_NameFields(temp_s0, &DAT_004c9908[0], &DAT_004c9918[0], &DAT_004c9928[0], temp_s2);
}

