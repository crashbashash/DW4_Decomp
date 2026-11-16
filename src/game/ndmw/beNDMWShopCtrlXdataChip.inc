igMetaObject *g_beNDMWShopCtrlXdataChip_metaObject;
igMetaField *g_beNDMWShopCtrlXdataChip_itemBaseListMetaField;

void beNDMWShopCtrlXdataChip_Create(int arg0) {
    beNDMWShopCtrlXdataChip_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopCtrlXdataChip_metaObject, arg0);
}

void *beNDMWShopCtrlXdataChip_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrlXdataChip_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopCtrlXdataChip_EnsureRegistered();
    }
    return g_beNDMWShopCtrlXdataChip_metaObject;
}

int beNDMWShopCtrlXdataChip_GetVTable(void) {
    struct Obj_3b69d0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[12] = 0;
    obj.w[13] = 0;
    obj.w[14] = 0;
    obj.w[15] = 0;
    obj.w[16] = 0;
    obj.w[17] = 0;
    obj.w[18] = 0;
    obj.vt = &g_beNDMWShopCtrlXdataChip_vtable[0];
    obj.w[23] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWShopCtrlXdataChip_vtable[0];
    igSmartPointer_beNDMWItemBaseList_Destruct((void **)(&obj.w[23]), (long long)(-1));
    FUN_003b6770((int **)&obj, (long long)0);
    return r;
}

void beNDMWShopCtrlXdataChip_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlXdataChip_Register);
}

static igMetaObjectCallback g_beNDMWShopCtrlXdataChip_callbackList[] = { beNDMWItemBaseList_EnsureRegistered, 0 };

void *beNDMWShopCtrlXdataChip_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlXdataChip_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlXdataChip_GetMetaObjectFunction,
        "beNDMWShopCtrlXdataChip",
        0x64, /* instance size */
        beNDMWShopCtrlXdataChip_GetVTable,
        beNDMWShopCtrlXdataChip_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlXdataChip_callbackList /* callback list */
    );
}

void beNDMWShopCtrlXdataChip_GetMetaObjectFunction(void)
{
    beNDMWShopCtrlXdataChip_GetMetaObject();
}

static FieldFactory g_beNDMWShopCtrlXdataChip_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWShopCtrlXdataChip_fieldTable[] = {
    "_itemBaseList",
};
static igMetaField **g_beNDMWShopCtrlXdataChip_fieldHandles[] = {
    &g_beNDMWShopCtrlXdataChip_itemBaseListMetaField,
};
static int g_beNDMWShopCtrlXdataChip_fieldOffsets[] = {
    96,
};

void beNDMWShopCtrlXdataChip_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWShopCtrlXdataChip_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWShopCtrlXdataChip_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beNDMWShopCtrlXdataChip_fieldTable, g_beNDMWShopCtrlXdataChip_fieldHandles, g_beNDMWShopCtrlXdataChip_fieldOffsets, temp_s2);
}

