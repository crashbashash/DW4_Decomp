igMetaObject *g_beNDMWStatusCtrlBaseEquip_metaObject;
igMetaField *g_beNDMWStatusCtrlBaseEquip_kindListPosMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_kindListMaxMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_pocketPosMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_playerListMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_powerSocketMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_mainSlotMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_subSlotMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_wpuPocketMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_apuPocketMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_deviceFolderMetaField;

void *beNDMWStatusCtrlBaseEquip_GetMetaObject(void) {
    bool ok;
    if (g_beNDMWStatusCtrlBaseEquip_metaObject == 0) goto make;
    ok = !!(g_beNDMWStatusCtrlBaseEquip_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWStatusCtrlBaseEquip_EnsureRegistered();
done:;
    return g_beNDMWStatusCtrlBaseEquip_metaObject;
}

void beNDMWStatusCtrlBaseEquip_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlBaseEquip_Register);
}

static igMetaObjectCallback g_beNDMWStatusCtrlBaseEquip_callbackList[] = { beDataObjList_EnsureRegistered, beNDMWItemBaseList_EnsureRegistered, 0 };

CallbackArray *beNDMWStatusCtrlBaseEquip_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWStatusCtrlBaseEquip_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlBaseEquip_GetMetaObjectFunction,
        "beNDMWStatusCtrlBaseEquip",
        0x7c, /* instance size */
        0,
        beNDMWStatusCtrlBaseEquip_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlBaseEquip_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlBaseEquip_GetMetaObjectFunction(void)
{
    beNDMWStatusCtrlBaseEquip_GetMetaObject();
}

static FieldFactory g_beNDMWStatusCtrlBaseEquip_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWStatusCtrlBaseEquip_fieldTable[] = {
    "_kindListPos",
    "_kindListMax",
    "_pocketPos",
    "_playerList",
    "_powerSocket",
    "_mainSlot",
    "_subSlot",
    "_wpuPocket",
    "_apuPocket",
    "_deviceFolder",
};
static igMetaField **g_beNDMWStatusCtrlBaseEquip_fieldHandles[] = {
    &g_beNDMWStatusCtrlBaseEquip_kindListPosMetaField,
    &g_beNDMWStatusCtrlBaseEquip_kindListMaxMetaField,
    &g_beNDMWStatusCtrlBaseEquip_pocketPosMetaField,
    &g_beNDMWStatusCtrlBaseEquip_playerListMetaField,
    &g_beNDMWStatusCtrlBaseEquip_powerSocketMetaField,
    &g_beNDMWStatusCtrlBaseEquip_mainSlotMetaField,
    &g_beNDMWStatusCtrlBaseEquip_subSlotMetaField,
    &g_beNDMWStatusCtrlBaseEquip_wpuPocketMetaField,
    &g_beNDMWStatusCtrlBaseEquip_apuPocketMetaField,
    &g_beNDMWStatusCtrlBaseEquip_deviceFolderMetaField,
};
static int g_beNDMWStatusCtrlBaseEquip_fieldOffsets[] = {
    84,
    88,
    92,
    96,
    100,
    104,
    108,
    112,
    116,
    120,
};

void beNDMWStatusCtrlBaseEquip_InitFields(void) {
    int base;
    void *playerList;
    void *powerSocket;
    void *mainSlot;
    void *subSlot;
    void *wpuPocket;
    void *apuPocket;
    void *deviceFolder;
    igMetaObject *meta;

    meta = g_beNDMWStatusCtrlBaseEquip_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStatusCtrlBaseEquip_ctorTable, 0xA);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 1), 1);
    playerList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)playerList)->_metaObject = (int)beDataObjList_GetOrCreateMetaObject();
    powerSocket = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)powerSocket)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    mainSlot = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)mainSlot)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    subSlot = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)subSlot)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    wpuPocket = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)wpuPocket)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    apuPocket = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)apuPocket)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    deviceFolder = (void *)(igMetaObject_GetFieldAt(meta, base + 9));
    ((igObjectRefMetaField *)deviceFolder)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWStatusCtrlBaseEquip_fieldTable, g_beNDMWStatusCtrlBaseEquip_fieldHandles, g_beNDMWStatusCtrlBaseEquip_fieldOffsets, base);
}

