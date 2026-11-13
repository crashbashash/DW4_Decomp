void beNDMWStatusMainSlot_Create(int arg0) {
    FUN_003ba850();
    igMetaObject_CreateInstance(*(int *)0x58AF20, arg0);
}

void *FUN_003ba7a0(void) {
    igMetaObject *g = g_beNDMWStatusMainSlot_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003ba850();
    }
    return g_beNDMWStatusMainSlot_metaObject[0];
}

int beNDMWStatusMainSlot_GetVTable(void) {
    struct Obj_3ba7f0 obj;
    int t;

    beNDMWStatusCtrlBaseEquip_Construct((beNDMWStatusCtrlBaseEquip *)&obj);
    obj.vt = &DAT_0053eff0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053eff0[0];
    FUN_003ba3d0((S_arg0 *)&obj, (long long)0);
    return t;
}

void FUN_003ba850(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusMainSlot_Register);
}

void *beNDMWStatusMainSlot_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusMainSlot_metaObject,
        beNDMWStatusCtrlBaseEquip_Register,
        beNDMWStatusCtrlBaseEquip_GetPublishedMetaObject,
        beNDMWStatusMainSlot_GetMetaObject,
        beNDMWStatusMainSlot_className,
        0x7c, /* instance size */
        beNDMWStatusMainSlot_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusMainSlot_GetMetaObject(void)
{
    FUN_003ba7a0();
}

