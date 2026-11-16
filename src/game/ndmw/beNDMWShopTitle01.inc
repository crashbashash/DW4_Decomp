igMetaObject *g_beNDMWShopTitle01_metaObject;

void beNDMWShopTitle01_Create(int arg0) {
    beNDMWShopTitle01_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopTitle01_metaObject, arg0);
}

void *beNDMWShopTitle01_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopTitle01_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopTitle01_EnsureRegistered();
    }
    return g_beNDMWShopTitle01_metaObject;
}

int beNDMWShopTitle01_GetVTable(void) {
    struct Obj_3b3240 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[12] = 0;
    obj.w[13] = 0;
    obj.w[14] = 0;
    obj.w[15] = 0;
    obj.w[16] = 0;
    obj.w[17] = 0;
    obj.w[18] = 0;
    obj.vt = &g_beNDMWShopTitle01_vtable[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWShopTitle01_vtable[0];
    FUN_003b3030((int **)&obj, (long long)0);
    return r;
}

void beNDMWShopTitle01_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopTitle01_Register);
}

void *beNDMWShopTitle01_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopTitle01_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWShopTitle01_GetMetaObjectFunction,
        "beNDMWShopTitle01",
        0x50, /* instance size */
        beNDMWShopTitle01_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopTitle01_GetMetaObjectFunction(void)
{
    beNDMWShopTitle01_GetMetaObject();
}

