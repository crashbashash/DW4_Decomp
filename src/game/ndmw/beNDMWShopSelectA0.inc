igMetaObject *g_beNDMWShopSelectA0_metaObject;

void beNDMWShopSelectA0_Create(int arg0) {
    beNDMWShopSelectA0_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopSelectA0_metaObject, arg0);
}

void *beNDMWShopSelectA0_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopSelectA0_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopSelectA0_EnsureRegistered();
    }
    return g_beNDMWShopSelectA0_metaObject;
}

int beNDMWShopSelectA0_GetVTable(void) {
    struct Obj_3b42e0 o;
    int r;
    igObject_InitHeader(&o);
    o.f52 = 0;
    o.f56 = 0;
    o.f60 = 0;
    o.f64 = 0;
    o.f68 = 0;
    o.f72 = 0;
    o.f76 = 0;
    o.f80 = 0;
    o.f108 = 0;
    o.vt = &g_beNDMWShopSelectA0_vtable[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beNDMWShopSelectA0_vtable[0];
    
    FUN_003b4050((struct S_3b4050 *)&o, (short)0);
    return r;
}

void beNDMWShopSelectA0_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelectA0_Register);
}

void *beNDMWShopSelectA0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopSelectA0_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelectA0_GetMetaObjectFunction,
        "beNDMWShopSelectA0",
        0x70, /* instance size */
        beNDMWShopSelectA0_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelectA0_GetMetaObjectFunction(void)
{
    beNDMWShopSelectA0_GetMetaObject();
}

