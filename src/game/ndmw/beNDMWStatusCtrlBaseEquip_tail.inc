void *FUN_003baaa0(void) {
    bool ok;
    if (g_beNDMWStatusCtrlBaseEquip_metaObject[0] == 0) goto make;
    ok = !!(g_beNDMWStatusCtrlBaseEquip_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_003baaf0();
done:;
    return g_beNDMWStatusCtrlBaseEquip_metaObject[0];
}

void FUN_003baaf0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlBaseEquip_Register);
}

void *beNDMWStatusCtrlBaseEquip_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWStatusCtrlBaseEquip_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlBaseEquip_GetMetaObject,
        beNDMWStatusCtrlBaseEquip_className,
        0x7c, /* instance size */
        0,
        beNDMWStatusCtrlBaseEquip_InitFields,
        0, /* extra callback item */
        pA6_2 /* callback list */
    );
}

void beNDMWStatusCtrlBaseEquip_GetMetaObject(void)
{
    FUN_003baaa0();
}

void beNDMWStatusCtrlBaseEquip_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s1;

    temp_s1 = (void *)g_beNDMWStatusCtrlBaseEquip_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c9ea0[0], 0xA);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1), 1);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00364090();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_003c9130();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_003c9130();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_003c9130();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_003c9130();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_003c9130();
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)FUN_003c9130();
    igMetaObject_NameFields(temp_s1, &DAT_004c9ed0[0], &DAT_004c9f00[0], &DAT_004c9f30[0], temp_s0);
}

