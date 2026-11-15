igMetaObject *g_beNDMWShopCtrl10_metaObject;
igMetaField *g_beNDMWShopCtrl10_xdataMenuMetaField;
igMetaField *g_beNDMWShopCtrl10_parameterMetaField;

void beNDMWShopCtrl10_Create(int arg0) {
    FUN_003b8c70();
    igMetaObject_CreateInstance(g_beNDMWShopCtrl10_metaObject, arg0);
}

void *FUN_003b8ba0(void) {
    igMetaObject *g = g_beNDMWShopCtrl10_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b8c70();
    }
    return g_beNDMWShopCtrl10_metaObject;
}

int beNDMWShopCtrl10_GetVTable(void) {
    struct W_3b8bf0 o;
    int r;

    igObject_InitHeader(&o);
    o.w[12] = 0;
    o.w[13] = 0;
    o.w[14] = 0;
    o.w[15] = 0;
    o.w[16] = 0;
    o.w[17] = 0;
    o.w[18] = 0;
    o.vt = DAT_0053fe50;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_0053fe50;
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&o, (long long)0);
    return r;
}

void FUN_003b8c70(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrl10_Register);
}

void *beNDMWShopCtrl10_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrl10_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl10_GetMetaObject,
        "beNDMWShopCtrl10",
        0x5c, /* instance size */
        beNDMWShopCtrl10_GetVTable,
        beNDMWShopCtrl10_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrl10_GetMetaObject(void)
{
    FUN_003b8ba0();
}

static FieldFactory g_beNDMWShopCtrl10_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWShopCtrl10_fieldTable[] = {
    "_xdataMenu",
    "_parameter",
};
static igMetaField **g_beNDMWShopCtrl10_fieldHandles[] = {
    &g_beNDMWShopCtrl10_xdataMenuMetaField,
    &g_beNDMWShopCtrl10_parameterMetaField,
};
static int g_beNDMWShopCtrl10_fieldOffsets[] = {
    84,
    88,
};

void beNDMWShopCtrl10_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWShopCtrl10_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWShopCtrl10_ctorTable, 2);
    igMetaObject_NameFields(temp_s0, g_beNDMWShopCtrl10_fieldTable, g_beNDMWShopCtrl10_fieldHandles, g_beNDMWShopCtrl10_fieldOffsets, temp_s1);
}

