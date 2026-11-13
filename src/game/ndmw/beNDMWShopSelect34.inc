void beNDMWShopSelect34_Create(int arg0) {
    FUN_003b46e0();
    igMetaObject_CreateInstance(*(int *)0x58AB98, arg0);
}

void *FUN_003b4610(void) {
    igMetaObject *g = g_beNDMWShopSelect34_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b46e0();
    }
    return g_beNDMWShopSelect34_metaObject[0];
}

int beNDMWShopSelect34_GetVTable(void) {
    struct Obj_3b4660 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[12] = 0;
    obj.w[13] = 0;
    obj.w[14] = 0;
    obj.w[15] = 0;
    obj.w[16] = 0;
    obj.w[17] = 0;
    obj.w[18] = 0;
    obj.w[19] = 0;
    obj.w[26] = 0;
    obj.vt = &DAT_00540060[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00540060[0];
    FUN_003b4050((struct S_3b4050 *)&obj, (short)0);
    return r;
}

void FUN_003b46e0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect34_Register);
}

void *beNDMWShopSelect34_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopSelect34_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect34_GetMetaObject,
        beNDMWShopSelect34_className,
        0x70, /* instance size */
        beNDMWShopSelect34_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect34_GetMetaObject(void)
{
    FUN_003b4610();
}

