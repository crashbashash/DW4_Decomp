void FUN_003ba6a0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSubSlot_Register);
}

void *beNDMWStatusSubSlot_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusSubSlot_metaObject,
        beNDMWStatusCtrlBaseEquip_Register,
        beNDMWStatusCtrlBaseEquip_GetPublishedMetaObject,
        beNDMWStatusSubSlot_GetMetaObject,
        beNDMWStatusSubSlot_className,
        0x7c, /* instance size */
        beNDMWStatusSubSlot_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusSubSlot_GetMetaObject(void)
{
    FUN_003ba2a0();
}

igMetaObject *FUN_003ba750(void) {
    return g_beNDMWStatusCtrlBaseEquip_metaObject[0];
}

