void beNDMWShopSelect02_Create(int arg0) {
    FUN_003b4c30();
    igMetaObject_CreateInstance(*(int *)0x58ABB0, arg0);
}

void *FUN_003b4b50(void) {
    igMetaObject *g = g_beNDMWShopSelect02_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b4c30();
    }
    return g_beNDMWShopSelect02_metaObject[0];
}

int beNDMWShopSelect02_GetVTable(void) {
    struct Obj_3b4ba0 o;
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
    o.vt = &DAT_005401b0[0];
    o.f112 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_005401b0[0];
    ObjectRef_Destruct_00150eb0(&o.f112, -1);
    FUN_003b4050((struct S_3b4050 *)&o, (short)0);
    return r;
}

void FUN_003b4c30(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect02_Register);
}

void *beNDMWShopSelect02_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopSelect02_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect02_GetMetaObject,
        beNDMWShopSelect02_className,
        0x74, /* instance size */
        beNDMWShopSelect02_GetVTable,
        beNDMWShopSelect02_InitFields,
        0, /* extra callback item */
        g_beNDMWShopSelect02_callbackList /* callback list */
    );
}

void beNDMWShopSelect02_GetMetaObject(void)
{
    FUN_003b4b50();
}

void beNDMWShopSelect02_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWShopSelect02_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWShopSelect02_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beNDMWShopSelect02_fieldTable[0], &DAT_004c9788[0], &DAT_004c9790[0], temp_s2);
}

