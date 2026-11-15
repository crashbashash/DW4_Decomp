igMetaObject *g_beModelCtrl_metaObject;
igMetaField *g_beModelCtrl_luaManagerMetaField;
igMetaField *g_beModelCtrl_targetObjMetaField;
igMetaField *g_beModelCtrl_isDebugHitBoxMetaField;

igMetaObject *FUN_00356b10(void) {
    if (g_beModelCtrl_metaObject == 0 || !isValid(g_beModelCtrl_metaObject)) FUN_00356b60();
    return g_beModelCtrl_metaObject;
}

void FUN_00356b60(void)
{
    igMetaObject_RunStaticInit(beModelCtrl_Register);
}

static igMetaObjectCallback g_beModelCtrl_callbackList[] = { FUN_0035b9c0, FUN_00342b00, 0 };

void *beModelCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beModelCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beModelCtrl_GetMetaObject,
        "beModelCtrl",
        0x2c, /* instance size */
        0,
        beModelCtrl_InitFields,
        0, /* extra callback item */
        g_beModelCtrl_callbackList /* callback list */
    );
}

void beModelCtrl_GetMetaObject(void)
{
    FUN_00356b10();
}

static FieldFactory g_beModelCtrl_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beModelCtrl_fieldTable[] = {
    "_luaManager",
    "_targetObj",
    "_isDebugHitBox",
};
static igMetaField **g_beModelCtrl_fieldHandles[] = {
    &g_beModelCtrl_luaManagerMetaField,
    &g_beModelCtrl_targetObjMetaField,
    &g_beModelCtrl_isDebugHitBoxMetaField,
};
static int g_beModelCtrl_fieldOffsets[] = {
    32,
    36,
    40,
};

void beModelCtrl_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrl_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beModelCtrl_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0035b770();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_003429b0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, g_beModelCtrl_fieldTable, g_beModelCtrl_fieldHandles, g_beModelCtrl_fieldOffsets, temp_s2);
}

