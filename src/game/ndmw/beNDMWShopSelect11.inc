void FUN_003b4790(int arg0) {
    FUN_003b48a0();
    igMetaObject_CreateInstance(*(int *)0x58ABA0, arg0);
}

void *FUN_003b47d0(void) {
    unsigned char b;
    if (g_beNDMWShopSelect11_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_beNDMWShopSelect11_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003b48a0();
done:
    return g_beNDMWShopSelect11_metaObject[0];
}

int beNDMWShopSelect11_GetVTable(void) {
    struct Obj_3b4820 obj;
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
    obj.vt = &DAT_005400d0[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_005400d0[0];
    FUN_003b4050((struct S_3b4050 *)&obj, (short)0);
    return r;
}

void FUN_003b48a0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect11_Register);
}

void *beNDMWShopSelect11_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopSelect11_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect11_GetMetaObject,
        beNDMWShopSelect11_className,
        0x70, /* instance size */
        beNDMWShopSelect11_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect11_GetMetaObject(void)
{
    FUN_003b47d0();
}

