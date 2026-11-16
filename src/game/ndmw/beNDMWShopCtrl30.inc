igMetaObject *g_beNDMWShopCtrl30_metaObject;
igMetaField *g_beNDMWShopCtrl30_bankMenuMetaField;

void beNDMWShopCtrl30_Create(int arg0) {
    beNDMWShopCtrl30_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopCtrl30_metaObject, arg0);
}

void *beNDMWShopCtrl30_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrl30_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopCtrl30_EnsureRegistered();
    }
    return g_beNDMWShopCtrl30_metaObject;
}

int beNDMWShopCtrl30_GetVTable(void) {
    struct F_3b86c0 f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[12] = 0;
    f.w[13] = 0;
    f.w[14] = 0;
    f.w[15] = 0;
    f.w[16] = 0;
    f.w[17] = 0;
    f.w[18] = 0;
    f.vt = &g_beNDMWShopCtrl30_vtable[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &g_beNDMWShopCtrl30_vtable[0];
    FUN_003b6430(&f, 0);
    return temp_s0;
}

void beNDMWShopCtrl30_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrl30_Register);
}

void *beNDMWShopCtrl30_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrl30_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl30_GetMetaObjectFunction,
        "beNDMWShopCtrl30",
        0x58, /* instance size */
        beNDMWShopCtrl30_GetVTable,
        beNDMWShopCtrl30_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrl30_GetMetaObjectFunction(void)
{
    beNDMWShopCtrl30_GetMetaObject();
}

static FieldFactory g_beNDMWShopCtrl30_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWShopCtrl30_fieldTable[] = {
    "_bankMenu",
};
static igMetaField **g_beNDMWShopCtrl30_fieldHandles[] = {
    &g_beNDMWShopCtrl30_bankMenuMetaField,
};
static int g_beNDMWShopCtrl30_fieldOffsets[] = {
    84,
};

void beNDMWShopCtrl30_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWShopCtrl30_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWShopCtrl30_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beNDMWShopCtrl30_fieldTable, g_beNDMWShopCtrl30_fieldHandles, g_beNDMWShopCtrl30_fieldOffsets, temp_s1);
}

