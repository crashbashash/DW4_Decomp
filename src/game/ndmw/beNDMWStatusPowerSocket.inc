igMetaObject *g_beNDMWStatusPowerSocket_metaObject;

void beNDMWStatusPowerSocket_Create(int allocator) {
    beNDMWStatusPowerSocket_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusPowerSocket_metaObject, allocator);
}

void *beNDMWStatusPowerSocket_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusPowerSocket_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusPowerSocket_EnsureRegistered();
    }
    return g_beNDMWStatusPowerSocket_metaObject;
}

int beNDMWStatusPowerSocket_GetVTable(void) {
    union U_3ba990 u;
    int temp_s0;

    beNDMWStatusCtrlBaseEquip_Construct((beNDMWStatusCtrlBaseEquip *)u.b);
    u.vt = (int)&g_beNDMWStatusPowerSocket_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beNDMWStatusPowerSocket_vtable[0];
    FUN_003ba3d0((S_arg0 *)u.b, (long long)0);
    return temp_s0;
}

void beNDMWStatusPowerSocket_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusPowerSocket_Register);
}

void *beNDMWStatusPowerSocket_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusPowerSocket_metaObject,
        beNDMWStatusCtrlBaseEquip_Register,
        beNDMWStatusCtrlBaseEquip_GetPublishedMetaObject,
        beNDMWStatusPowerSocket_GetMetaObjectFunction,
        "beNDMWStatusPowerSocket",
        0x7c, /* instance size */
        beNDMWStatusPowerSocket_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusPowerSocket_GetMetaObjectFunction(void)
{
    beNDMWStatusPowerSocket_GetMetaObject();
}

