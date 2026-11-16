igMetaObject *g_beNDMWShopCtrlA2_metaObject;

void beNDMWShopCtrlA2_Create(int allocator) {
    beNDMWShopCtrlA2_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopCtrlA2_metaObject, allocator);
}

igMetaObject *beNDMWShopCtrlA2_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrlA2_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWShopCtrlA2_EnsureRegistered();
done:
    return g_beNDMWShopCtrlA2_metaObject;
}

int beNDMWShopCtrlA2_GetVTable(void) {
    struct Obj_3b7ad0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.vt = &g_beNDMWShopCtrlA2_vtable[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWShopCtrlA2_vtable[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return t;
}

void beNDMWShopCtrlA2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlA2_Register);
}

void *beNDMWShopCtrlA2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlA2_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlA2_GetMetaObjectFunction,
        "beNDMWShopCtrlA2",
        0x54, /* instance size */
        beNDMWShopCtrlA2_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrlA2_GetMetaObjectFunction(void)
{
    beNDMWShopCtrlA2_GetMetaObject();
}

