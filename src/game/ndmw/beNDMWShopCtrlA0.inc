void beNDMWShopCtrlA0_Create(int arg0) {
    FUN_003b8060();
    igMetaObject_CreateInstance(*(int *)0x58ADA0, arg0);
}

void *FUN_003b7ef0(void) {
    igMetaObject *g = g_beNDMWShopCtrlA0_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b8060();
    }
    return g_beNDMWShopCtrlA0_metaObject[0];
}

int beNDMWShopCtrlA0_GetVTable(void) {
    struct Obj_3b7f40 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.vt = &DAT_0053fc70[0];
    obj.w21 = 0;
    obj.w22 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053fc70[0];
    ObjectRef_Destruct_00150eb0(&obj.w22, -1);
    FUN_003b7fe0((O *)&obj.w21, (short)(-1));
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return t;
}

O *FUN_003b7fe0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void FUN_003b8060(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlA0_Register);
}

void *beNDMWShopCtrlA0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlA0_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlA0_GetMetaObject,
        beNDMWShopCtrlA0_className,
        0x5c, /* instance size */
        beNDMWShopCtrlA0_GetVTable,
        beNDMWShopCtrlA0_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlA0_callbackList /* callback list */
    );
}

void beNDMWShopCtrlA0_GetMetaObject(void)
{
    FUN_003b7ef0();
}

void beNDMWShopCtrlA0_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWShopCtrlA0_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWShopCtrlA0_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003b3730();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beNDMWShopCtrlA0_fieldTable[0], &DAT_004c9b60[0], &DAT_004c9b68[0], temp_s2);
}

