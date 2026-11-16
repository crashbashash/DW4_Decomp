igMetaObject *g_beModelCtrl_metaObject;
igMetaField *g_beModelCtrl_luaManagerMetaField;
igMetaField *g_beModelCtrl_targetObjMetaField;
igMetaField *g_beModelCtrl_isDebugHitBoxMetaField;

igMetaObject *beModelCtrl_GetMetaObject(void) {
    if (g_beModelCtrl_metaObject == 0 || !isValid(g_beModelCtrl_metaObject)) beModelCtrl_EnsureRegistered();
    return g_beModelCtrl_metaObject;
}

void beModelCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrl_Register);
}

static igMetaObjectCallback g_beModelCtrl_callbackList[] = { beLua_EnsureRegistered, beTargetObj_EnsureRegistered, 0 };

void *beModelCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beModelCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beModelCtrl_GetMetaObjectFunction,
        "beModelCtrl",
        0x2c, /* instance size */
        0,
        beModelCtrl_InitFields,
        0, /* extra callback item */
        g_beModelCtrl_callbackList /* callback list */
    );
}

void beModelCtrl_GetMetaObjectFunction(void)
{
    beModelCtrl_GetMetaObject();
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
    int base;
    void *targetObj;
    void *luaManager;
    void *meta;

    meta = (void *)g_beModelCtrl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrl_ctorTable, 3);
    luaManager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)luaManager)->_metaObject = (int)beLua_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)luaManager)->_refCounted = 0;
    targetObj = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)targetObj)->_metaObject = (int)beTargetObj_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)targetObj)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beModelCtrl_fieldTable, g_beModelCtrl_fieldHandles, g_beModelCtrl_fieldOffsets, base);
}

