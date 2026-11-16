igMetaObject *g_beNDMWStatusSubSlot_metaObject;

void beNDMWStatusSubSlot_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSubSlot_Register);
}

CallbackArray *beNDMWStatusSubSlot_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusSubSlot_metaObject,
        beNDMWStatusCtrlBaseEquip_Register,
        beNDMWStatusCtrlBaseEquip_GetPublishedMetaObject,
        beNDMWStatusSubSlot_GetMetaObjectFunction,
        "beNDMWStatusSubSlot",
        0x7c, /* instance size */
        beNDMWStatusSubSlot_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusSubSlot_GetMetaObjectFunction(void)
{
    beNDMWStatusSubSlot_GetMetaObject();
}

igMetaObject *beNDMWStatusCtrlBaseEquip_GetPublishedMetaObject(void) {
    return g_beNDMWStatusCtrlBaseEquip_metaObject;
}

