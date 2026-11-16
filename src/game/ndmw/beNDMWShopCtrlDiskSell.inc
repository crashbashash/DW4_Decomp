igMetaObject *g_beNDMWShopCtrlDiskSell_metaObject;
igMetaField *g_beNDMWShopCtrlDiskSell_diskIdListMetaField;
igMetaField *g_beNDMWShopCtrlDiskSell_cursorMetaField;
igMetaField *g_beNDMWShopCtrlDiskSell_maxSellMetaField;
igMetaField *g_beNDMWShopCtrlDiskSell_kazuMetaField;
igMetaField *g_beNDMWShopCtrlDiskSell_tankaMetaField;

void beNDMWShopCtrlDiskSell_Create(int allocator) {
    beNDMWShopCtrlDiskSell_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopCtrlDiskSell_metaObject, allocator);
}

void *beNDMWShopCtrlDiskSell_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrlDiskSell_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopCtrlDiskSell_EnsureRegistered();
    }
    return g_beNDMWShopCtrlDiskSell_metaObject;
}

int beNDMWShopCtrlDiskSell_GetVTable(void) {
    union U_3b6ef0 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[13] = 0;
    u.w[14] = 0;
    u.w[15] = 0;
    u.w[16] = 0;
    u.w[17] = 0;
    u.w[18] = 0;
    u.w[19] = 0;
    u.w[0] = (int)(&g_beNDMWShopCtrlDiskSell_vtable[0]);
    u.w[21] = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beNDMWShopCtrlDiskSell_vtable[0]);
    igSmartPointer_igIntList_Destruct(&u.w[21], -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)(&u.w[0]), (long long)0);
    return temp_s0;
}

void beNDMWShopCtrlDiskSell_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlDiskSell_Register);
}

static igMetaObjectCallback g_beNDMWShopCtrlDiskSell_callbackList[] = { igIntList_EnsureRegistered, 0 };

void *beNDMWShopCtrlDiskSell_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlDiskSell_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlDiskSell_GetMetaObjectFunction,
        "beNDMWShopCtrlDiskSell",
        0x68, /* instance size */
        beNDMWShopCtrlDiskSell_GetVTable,
        beNDMWShopCtrlDiskSell_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlDiskSell_callbackList /* callback list */
    );
}

void beNDMWShopCtrlDiskSell_GetMetaObjectFunction(void)
{
    beNDMWShopCtrlDiskSell_GetMetaObject();
}

static FieldFactory g_beNDMWShopCtrlDiskSell_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWShopCtrlDiskSell_fieldTable[] = {
    "_diskIdList",
    "_cursor",
    "_maxSell",
    "_kazu",
    "_tanka",
};
static igMetaField **g_beNDMWShopCtrlDiskSell_fieldHandles[] = {
    &g_beNDMWShopCtrlDiskSell_diskIdListMetaField,
    &g_beNDMWShopCtrlDiskSell_cursorMetaField,
    &g_beNDMWShopCtrlDiskSell_maxSellMetaField,
    &g_beNDMWShopCtrlDiskSell_kazuMetaField,
    &g_beNDMWShopCtrlDiskSell_tankaMetaField,
};
static int g_beNDMWShopCtrlDiskSell_fieldOffsets[] = {
    84,
    88,
    92,
    96,
    100,
};

void beNDMWShopCtrlDiskSell_InitFields(void) {
    int base;
    void *diskIdList;
    igMetaObject *meta;

    meta = g_beNDMWShopCtrlDiskSell_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopCtrlDiskSell_ctorTable, 5);
    diskIdList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)diskIdList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)diskIdList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWShopCtrlDiskSell_fieldTable, g_beNDMWShopCtrlDiskSell_fieldHandles, g_beNDMWShopCtrlDiskSell_fieldOffsets, base);
}

