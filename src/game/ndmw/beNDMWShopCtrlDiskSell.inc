void beNDMWShopCtrlDiskSell_Create(int arg0) {
    FUN_003b6f80();
    igMetaObject_CreateInstance(*(int *)0x58ACE0, arg0);
}

void *FUN_003b6ea0(void) {
    igMetaObject *g = g_beNDMWShopCtrlDiskSell_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b6f80();
    }
    return g_beNDMWShopCtrlDiskSell_metaObject[0];
}

int beNDMWShopCtrlDiskSell_GetVTable(void) {
    union U_3b6ef0 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[13] = 0;
    u.w[14] = 0;
    u.w[15] = 0;
    u.w[16] = 0;
    u.w[17] = 0;
    u.w[18] = 0;
    u.w[19] = 0;
    u.w[0] = (int)(&DAT_0053f950[0]);
    u.w[21] = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_0053f950[0]);
    ObjectRef_Destruct_00150eb0(&u.w[21], -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)(&u.w[0]), (long long)0);
    return temp_s0;
}

void FUN_003b6f80(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlDiskSell_Register);
}

void *beNDMWShopCtrlDiskSell_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlDiskSell_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlDiskSell_GetMetaObject,
        beNDMWShopCtrlDiskSell_className,
        0x68, /* instance size */
        beNDMWShopCtrlDiskSell_GetVTable,
        beNDMWShopCtrlDiskSell_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlDiskSell_callbackList /* callback list */
    );
}

void beNDMWShopCtrlDiskSell_GetMetaObject(void)
{
    FUN_003b6ea0();
}

void beNDMWShopCtrlDiskSell_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWShopCtrlDiskSell_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWShopCtrlDiskSell_ctorTable[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beNDMWShopCtrlDiskSell_fieldTable[0], &DAT_004c9a00[0], &DAT_004c9a20[0], temp_s2);
}

