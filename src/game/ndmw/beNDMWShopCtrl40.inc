void FUN_003b8400(int arg0) {
    FUN_003b8510();
    igMetaObject_CreateInstance(*(int *)0x58ADE8, arg0);
}

void *FUN_003b8440(void) {
    bool ok;
    if (DAT_0058ade8[0] == 0) goto make;
    ok = !!(DAT_0058ade8[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003b8510();
done:;
    return DAT_0058ade8[0];
}

int beNDMWShopCtrl40_GetVTable(void) {
    union U_3b8490 u;
    int t;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&DAT_0053fd90[0];
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053fd90[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)u.b, (long long)0);
    return t;
}

void FUN_003b8510(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrl40_Register);
}

void *beNDMWShopCtrl40_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrl40_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl40_GetMetaObject,
        beNDMWShopCtrl40_className,
        0x58, /* instance size */
        beNDMWShopCtrl40_GetVTable,
        beNDMWShopCtrl40_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrl40_GetMetaObject(void)
{
    FUN_003b8440();
}

void beNDMWShopCtrl40_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058ade8)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9be8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c9bf0[0], &DAT_004c9bf8[0], &DAT_004c9c00[0], temp_s1);
}

