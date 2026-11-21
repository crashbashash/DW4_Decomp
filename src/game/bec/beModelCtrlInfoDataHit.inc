igMetaObject *g_beModelCtrlInfoDataHit_metaObject;
int g_beModelCtrlInfoDataHit_nameStorage;
igMetaField *g_beModelCtrlInfoDataHit_isHitPlayerBulletMetaField;
igMetaField *g_beModelCtrlInfoDataHit_isHitEnemyBulletMetaField;
igMetaField *g_beModelCtrlInfoDataHit_hitBulletAABoxListMetaField;
igMetaField *g_beModelCtrlInfoDataHit_isHitPlayerTalkMetaField;

void *beModelCtrlInfoDataHit_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlInfoDataHit_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlInfoDataHit_EnsureRegistered();
    }
    return g_beModelCtrlInfoDataHit_metaObject;
}

int beModelCtrlInfoDataHit_GetVTable(void) {
    beModelCtrlInfoDataHit obj;
    int vtable;
    igObject **hitBulletAABoxListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beModelCtrlInfoDataHit_vtable[0];
    hitBulletAABoxListSlot = (igObject **)&obj._hitBulletAABoxList;
    *hitBulletAABoxListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beModelCtrlInfoDataHit_vtable[0];
    igObjectRef_Release(hitBulletAABoxListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlInfoDataHit_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataHit_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoDataHit_callbackList[] = { igAABoxList_EnsureRegistered, 0 };

CallbackArray *beModelCtrlInfoDataHit_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoDataHit_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataHit_GetMetaObjectFunction,
        "beModelCtrlInfoDataHit",
        0x1c, /* instance size */
        beModelCtrlInfoDataHit_GetVTable,
        beModelCtrlInfoDataHit_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoDataHit_callbackList /* callback list */
    );
}

void beModelCtrlInfoDataHit_GetMetaObjectFunction(void)
{
    beModelCtrlInfoDataHit_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoDataHit_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beModelCtrlInfoDataHit_fieldTable[] = {
    "_isHitPlayerBullet",
    "_isHitEnemyBullet",
    "_hitBulletAABoxList",
    "_isHitPlayerTalk",
};
static igMetaField **g_beModelCtrlInfoDataHit_fieldHandles[] = {
    &g_beModelCtrlInfoDataHit_isHitPlayerBulletMetaField,
    &g_beModelCtrlInfoDataHit_isHitEnemyBulletMetaField,
    &g_beModelCtrlInfoDataHit_hitBulletAABoxListMetaField,
    &g_beModelCtrlInfoDataHit_isHitPlayerTalkMetaField,
};
static int g_beModelCtrlInfoDataHit_fieldOffsets[] = {
    16,
    17,
    20,
    24,
};

void beModelCtrlInfoDataHit_InitFields(void) {
    int base;
    int index;
    void **found;
    void *hitBulletAABoxList;
    void *meta;
    igStringMetaField *clone;

    meta = (void *)g_beModelCtrlInfoDataHit_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beModelCtrlInfoDataHit_ctorTable, 4);
    found = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    index = ((Gap::Core::__internalNonRefCountedObjectList *)(((igMetaObject *)meta)->_metaFields))->find((Gap::Core::igObject *)found);
    clone = (igStringMetaField *)(((igObjectDispatchView *)found)->CloneViaMetadata(1));
    ((Gap::Core::igStringMetaField *)clone)->setDefault("HIT");
    clone->_externalEnumStorage = (int)(&g_beModelCtrlInfoDataHit_nameStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, index, (igMetaField *)clone);
    clone->release();
    hitBulletAABoxList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2));
    ((igObjectRefMetaField *)hitBulletAABoxList)->_metaObject = (int)igAABoxList_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_beModelCtrlInfoDataHit_fieldTable, g_beModelCtrlInfoDataHit_fieldHandles, g_beModelCtrlInfoDataHit_fieldOffsets, base);
}

