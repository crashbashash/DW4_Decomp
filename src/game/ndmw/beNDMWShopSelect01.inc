igMetaObject *g_beNDMWShopSelect01_metaObject;

void beNDMWShopSelect01_Create(int arg0) {
    beNDMWShopSelect01_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopSelect01_metaObject, arg0);
}

void *beNDMWShopSelect01_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopSelect01_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopSelect01_EnsureRegistered();
    }
    return g_beNDMWShopSelect01_metaObject;
}

int beNDMWShopSelect01_GetVTable(void) {
    union U_3b4e20 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[13] = 0;
    u.w[14] = 0;
    u.w[15] = 0;
    u.w[16] = 0;
    u.w[17] = 0;
    u.w[18] = 0;
    u.w[19] = 0;
    u.w[20] = 0;
    u.w[27] = 0;
    u.w[0] = (int)(&g_beNDMWShopSelect01_vtable[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beNDMWShopSelect01_vtable[0]);
    FUN_003b4050((struct S_3b4050 *)(&u.w[0]), (short)0);
    return temp_s0;
}

void beNDMWShopSelect01_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect01_Register);
}

void *beNDMWShopSelect01_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopSelect01_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect01_GetMetaObjectFunction,
        "beNDMWShopSelect01",
        0x70, /* instance size */
        beNDMWShopSelect01_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect01_GetMetaObjectFunction(void)
{
    beNDMWShopSelect01_GetMetaObject();
}

