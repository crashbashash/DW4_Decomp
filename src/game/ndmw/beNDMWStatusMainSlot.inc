igMetaObject *g_beNDMWStatusMainSlot_metaObject;

beNDMWStatusMainSlot *beNDMWStatusMainSlot_Create(int allocator) {
    beNDMWStatusMainSlot_EnsureRegistered();
    return (beNDMWStatusMainSlot *)igMetaObject_CreateInstance(g_beNDMWStatusMainSlot_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWStatusMainSlot_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusMainSlot_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusMainSlot_EnsureRegistered();
    }
    return g_beNDMWStatusMainSlot_metaObject;
}

int beNDMWStatusMainSlot_GetVTable(void) {
    beNDMWStatusMainSlot obj;
    int vtable;

    beNDMWStatusCtrlBaseEquip_Construct((beNDMWStatusCtrlBaseEquip *)&obj);
    *(int **)&obj._vtable = &g_beNDMWStatusMainSlot_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusMainSlot_vtable[0];
    beNDMWStatusCtrlBaseEquip_Destroy((beNDMWStatusCtrlBaseEquip *)&obj, 0);
    return vtable;
}

void beNDMWStatusMainSlot_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusMainSlot_Register);
}

CallbackArray *beNDMWStatusMainSlot_Register(void) {
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

