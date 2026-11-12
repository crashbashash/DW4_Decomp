void FUN_003b7750(int arg0) {
    FUN_003b78a0();
    igMetaObject_CreateInstance(*(int *)0x58AD40, arg0);
}

G_3b7790 *FUN_003b7790(void) {
    G_3b7790 *g = DAT_0058ad40[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003b78a0();
    return DAT_0058ad40[0];
}

int beNDMWShopCtrlDigilabo_GetVTable(void) {
    struct Obj_3b77e0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.vt = &DAT_0053fae0[0];
    obj.w21 = 0;
    obj.w22 = 0;
    obj.w23 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053fae0[0];
    FUN_0019d200(&obj.w23, -1);
    ObjectRef_Destruct_00150eb0(&obj.w22, -1);
    ObjectRef_Destruct_00150eb0(&obj.w21, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return t;
}

void FUN_003b78a0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlDigilabo_Register);
}

void *beNDMWShopCtrlDigilabo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlDigilabo_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlDigilabo_GetMetaObject,
        beNDMWShopCtrlDigilabo_className,
        0x6c, /* instance size */
        beNDMWShopCtrlDigilabo_GetVTable,
        beNDMWShopCtrlDigilabo_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlDigilabo_callbackList /* callback list */
    );
}

void beNDMWShopCtrlDigilabo_GetMetaObject(void)
{
    FUN_003b7790();
}

void beNDMWShopCtrlDigilabo_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058ad40)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9a90[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_002c8980();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c9ab0[0], &DAT_004c9ad0[0], &DAT_004c9af0[0], temp_s2);
}

