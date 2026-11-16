igMetaObject *g_beNDMWStatusMainSlot_metaObject;

void beNDMWStatusMainSlot_Create(int arg0) {
    beNDMWStatusMainSlot_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusMainSlot_metaObject, arg0);
}

void *beNDMWStatusMainSlot_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusMainSlot_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusMainSlot_EnsureRegistered();
    }
    return g_beNDMWStatusMainSlot_metaObject;
}

int beNDMWStatusMainSlot_GetVTable(void) {
    struct Obj_3ba7f0 obj;
    int t;

    beNDMWStatusCtrlBaseEquip_Construct((beNDMWStatusCtrlBaseEquip *)&obj);
    obj.vt = &g_beNDMWStatusMainSlot_vtable[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWStatusMainSlot_vtable[0];
    FUN_003ba3d0((S_arg0 *)&obj, (long long)0);
    return t;
}

void beNDMWStatusMainSlot_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusMainSlot_Register);
}

void *beNDMWStatusMainSlot_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusMainSlot_metaObject,
        beNDMWStatusCtrlBaseEquip_Register,
        beNDMWStatusCtrlBaseEquip_GetPublishedMetaObject,
        beNDMWStatusMainSlot_GetMetaObjectFunction,
        "beNDMWStatusMainSlot",
        0x7c, /* instance size */
        beNDMWStatusMainSlot_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusMainSlot_GetMetaObjectFunction(void)
{
    beNDMWStatusMainSlot_GetMetaObject();
}

