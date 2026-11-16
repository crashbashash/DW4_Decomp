igMetaObject *g_beNDMWShopCtrlA0_metaObject;
igMetaField *g_beNDMWShopCtrlA0_accountMetaField;
igMetaField *g_beNDMWShopCtrlA0_playerNoListMetaField;

void beNDMWShopCtrlA0_Create(int arg0) {
    beNDMWShopCtrlA0_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopCtrlA0_metaObject, arg0);
}

void *beNDMWShopCtrlA0_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrlA0_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopCtrlA0_EnsureRegistered();
    }
    return g_beNDMWShopCtrlA0_metaObject;
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
    obj.vt = &g_beNDMWShopCtrlA0_vtable[0];
    obj.w21 = 0;
    obj.w22 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWShopCtrlA0_vtable[0];
    igSmartPointer_igIntList_Destruct(&obj.w22, -1);
    igSmartPointer_beNDMWStatusTitle03_Destruct((O *)&obj.w21, (short)(-1));
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return t;
}

O *igSmartPointer_beNDMWStatusTitle03_Destruct(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void beNDMWShopCtrlA0_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlA0_Register);
}

static igMetaObjectCallback g_beNDMWShopCtrlA0_callbackList[] = { beNDMWStatusTitle03_EnsureRegistered, igIntList_EnsureRegistered, 0 };

void *beNDMWShopCtrlA0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlA0_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlA0_GetMetaObjectFunction,
        "beNDMWShopCtrlA0",
        0x5c, /* instance size */
        beNDMWShopCtrlA0_GetVTable,
        beNDMWShopCtrlA0_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlA0_callbackList /* callback list */
    );
}

void beNDMWShopCtrlA0_GetMetaObjectFunction(void)
{
    beNDMWShopCtrlA0_GetMetaObject();
}

static FieldFactory g_beNDMWShopCtrlA0_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWShopCtrlA0_fieldTable[] = {
    "_account",
    "_playerNoList",
};
static igMetaField **g_beNDMWShopCtrlA0_fieldHandles[] = {
    &g_beNDMWShopCtrlA0_accountMetaField,
    &g_beNDMWShopCtrlA0_playerNoListMetaField,
};
static int g_beNDMWShopCtrlA0_fieldOffsets[] = {
    84,
    88,
};

void beNDMWShopCtrlA0_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWShopCtrlA0_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWShopCtrlA0_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beNDMWStatusTitle03_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beNDMWShopCtrlA0_fieldTable, g_beNDMWShopCtrlA0_fieldHandles, g_beNDMWShopCtrlA0_fieldOffsets, temp_s2);
}

