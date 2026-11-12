void FUN_003ba900(int arg0) {
    FUN_003ba9f0();
    igMetaObject_CreateInstance(*(int *)0x58AF28, arg0);
}

void *FUN_003ba940(void) {
    igMetaObject *g = g_beNDMWStatusPowerSocket_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003ba9f0();
    }
    return g_beNDMWStatusPowerSocket_metaObject[0];
}

int beNDMWStatusPowerSocket_GetVTable(void) {
    union U_3ba990 u;
    int temp_s0;

    beNDMWStatusCtrlBaseEquip_Construct((beNDMWStatusCtrlBaseEquip *)u.b);
    u.vt = (int)&DAT_0053f0a0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053f0a0[0];
    FUN_003ba3d0((S_arg0 *)u.b, (long long)0);
    return temp_s0;
}

void FUN_003ba9f0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusPowerSocket_Register);
}

void *beNDMWStatusPowerSocket_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusPowerSocket_metaObject,
        beNDMWStatusCtrlBaseEquip_Register,
        beNDMWStatusCtrlBaseEquip_GetPublishedMetaObject,
        beNDMWStatusPowerSocket_GetMetaObject,
        beNDMWStatusPowerSocket_className,
        0x7c, /* instance size */
        beNDMWStatusPowerSocket_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusPowerSocket_GetMetaObject(void)
{
    FUN_003ba940();
}

