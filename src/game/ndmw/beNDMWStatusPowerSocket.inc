igMetaObject *g_beNDMWStatusPowerSocket_metaObject;

beNDMWStatusPowerSocket *beNDMWStatusPowerSocket_Create(int allocator) {
    beNDMWStatusPowerSocket_EnsureRegistered();
    return (beNDMWStatusPowerSocket *)igMetaObject_CreateInstance(g_beNDMWStatusPowerSocket_metaObject, allocator);
}

void *beNDMWStatusPowerSocket_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusPowerSocket_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusPowerSocket_EnsureRegistered();
    }
    return g_beNDMWStatusPowerSocket_metaObject;
}

int beNDMWStatusPowerSocket_GetVTable(void) {
    beNDMWStatusPowerSocket obj;
    int vtable;

    beNDMWStatusCtrlBaseEquip_Construct((beNDMWStatusCtrlBaseEquip *)&obj);
    *(int **)&obj._vtable = &g_beNDMWStatusPowerSocket_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusPowerSocket_vtable[0];
    beNDMWStatusCtrlBaseEquip_Destroy((beNDMWStatusCtrlBaseEquip *)&obj, 0);
    return vtable;
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

