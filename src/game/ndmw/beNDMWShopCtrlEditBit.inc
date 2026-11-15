igMetaObject *g_beNDMWShopCtrlEditBit_metaObject;
igMetaField *g_beNDMWShopCtrlEditBit_editBitMetaField;
igMetaField *g_beNDMWShopCtrlEditBit_editMaxMetaField;

void beNDMWShopCtrlEditBit_Create(int arg0) {
    FUN_003b7630();
    igMetaObject_CreateInstance(g_beNDMWShopCtrlEditBit_metaObject, arg0);
}

igMetaObject *FUN_003b7560(void)
{
    igMetaObject *g = g_beNDMWShopCtrlEditBit_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003b7630();
    return g_beNDMWShopCtrlEditBit_metaObject;
}

int beNDMWShopCtrlEditBit_GetVTable(void) {
    Obj_3b75b0 o;
    int r;

    igObject_InitHeader(&o);
    o.w[12] = 0;
    o.w[13] = 0;
    o.w[14] = 0;
    o.w[15] = 0;
    o.w[16] = 0;
    o.w[17] = 0;
    o.w[18] = 0;
    o.vt = &DAT_0053fa80[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_0053fa80[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&o, (long long)0);
    return r;
}

void FUN_003b7630(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlEditBit_Register);
}

void *beNDMWShopCtrlEditBit_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlEditBit_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlEditBit_GetMetaObject,
        "beNDMWShopCtrlEditBit",
        0x5c, /* instance size */
        beNDMWShopCtrlEditBit_GetVTable,
        beNDMWShopCtrlEditBit_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrlEditBit_GetMetaObject(void)
{
    FUN_003b7560();
}

static FieldFactory g_beNDMWShopCtrlEditBit_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWShopCtrlEditBit_fieldTable[] = {
    "_editBit",
    "_editMax",
};
static igMetaField **g_beNDMWShopCtrlEditBit_fieldHandles[] = {
    &g_beNDMWShopCtrlEditBit_editBitMetaField,
    &g_beNDMWShopCtrlEditBit_editMaxMetaField,
};
static int g_beNDMWShopCtrlEditBit_fieldOffsets[] = {
    84,
    88,
};

void beNDMWShopCtrlEditBit_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWShopCtrlEditBit_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWShopCtrlEditBit_ctorTable, 2);
    igMetaObject_NameFields(temp_s0, g_beNDMWShopCtrlEditBit_fieldTable, g_beNDMWShopCtrlEditBit_fieldHandles, g_beNDMWShopCtrlEditBit_fieldOffsets, temp_s1);
}

