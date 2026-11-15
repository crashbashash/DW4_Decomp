igMetaObject *g_beLayerCtl_metaObject;
igMetaField *g_beLayerCtl_isOrderedMetaField;
igMetaField *g_beLayerCtl_layerSwtMetaField;

void beLayerCtl_CreateInstance(int arg0) {
    FUN_0035cbf0();
    igMetaObject_CreateInstance(*(int *)0x589298, arg0);
}

igMetaObject *FUN_0035cae0(void) {
    if (g_beLayerCtl_metaObject == 0) {
        g_beLayerCtl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beLayerCtl_metaObject;
}

void *FUN_0035cb30(void) {
    igMetaObject *g = g_beLayerCtl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035cbf0();
    }
    return g_beLayerCtl_metaObject;
}

int beLayerCtl_GetVTable(void) {
    union U u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_0053a940[0];
    p = (int *)&u.b[36];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053a940[0];
    FUN_00343260((ObjectRefWord *)p, -1);
    FUN_0033f5e0((O_33f5e0 *)u.b, (short)0);
    return temp_s0;
}

void FUN_0035cbf0(void)
{
    igMetaObject_RunStaticInit(beLayerCtl_Register);
}

static igMetaObjectCallback g_beLayerCtl_callbackList[] = { FUN_00196ad0, 0 };

void *beLayerCtl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLayerCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beLayerCtl_GetMetaObject,
        "beLayerCtl",
        0x28, /* instance size */
        beLayerCtl_GetVTable,
        beLayerCtl_InitFields,
        0, /* extra callback item */
        g_beLayerCtl_callbackList /* callback list */
    );
}

void beLayerCtl_GetMetaObject(void)
{
    FUN_0035cb30();
}

static FieldFactory g_beLayerCtl_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beLayerCtl_fieldTable[] = {
    "_isOrdered",
    "_layerSwt",
};
static igMetaField **g_beLayerCtl_fieldHandles[] = {
    &g_beLayerCtl_isOrderedMetaField,
    &g_beLayerCtl_layerSwtMetaField,
};
static int g_beLayerCtl_fieldOffsets[] = {
    32,
    36,
};

void beLayerCtl_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beLayerCtl_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beLayerCtl_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196930();
    igMetaObject_NameFields(temp_s0, g_beLayerCtl_fieldTable, g_beLayerCtl_fieldHandles, g_beLayerCtl_fieldOffsets, temp_s2);
}

