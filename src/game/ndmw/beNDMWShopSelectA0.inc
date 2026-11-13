void beNDMWShopSelectA0_Create(int arg0) {
    FUN_003b4360();
    igMetaObject_CreateInstance(*(int *)0x58AB88, arg0);
}

void *FUN_003b4290(void) {
    igMetaObject *g = g_beNDMWShopSelectA0_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b4360();
    }
    return g_beNDMWShopSelectA0_metaObject[0];
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
    o.vt = &DAT_0053ff80[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_0053ff80[0];
    
    FUN_003b4050((struct S_3b4050 *)&o, (short)0);
    return r;
}

void FUN_003b4360(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelectA0_Register);
}

void *beNDMWShopSelectA0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopSelectA0_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelectA0_GetMetaObject,
        beNDMWShopSelectA0_className,
        0x70, /* instance size */
        beNDMWShopSelectA0_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelectA0_GetMetaObject(void)
{
    FUN_003b4290();
}

