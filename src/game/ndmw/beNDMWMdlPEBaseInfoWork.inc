igMetaObject *g_beNDMWMdlPEBaseInfoWork_metaObject;
igMetaField *g_beNDMWMdlPEBaseInfoWork_isPlayerMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_dispRamNoListMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_dispPosNoListMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_timerListMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_isFirstListMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_poisonDamageMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_poisonEnduranceMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_downDataListMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_upDataListMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_messengerMetaField;

void *beNDMWMdlPEBaseInfoWork_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlPEBaseInfoWork_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlPEBaseInfoWork_EnsureRegistered();
    }
    return g_beNDMWMdlPEBaseInfoWork_metaObject;
}

int beNDMWMdlPEBaseInfoWork_GetVTable(void) {
    PEBaseInfoWorkObj work;
    return *(int *)((char *)&work + g_objectSystem->vtableProbeOffset);
}

igSmartPointer<igObject> *igSmartPointer_igBoolList_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

void beNDMWMdlPEBaseInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPEBaseInfoWork_Register);
}

static igMetaObjectCallback g_beNDMWMdlPEBaseInfoWork_callbackList[] = { Gap::Core::igIntList::arkRegister, Gap::Core::igBoolList::arkRegister, beMessenger_EnsureRegistered, 0 };

CallbackArray *beNDMWMdlPEBaseInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlPEBaseInfoWork_metaObject,
        beModelCtrlInfoWork_Register,
        beModelCtrlInfoWork_GetPublishedMetaObject,
        beNDMWMdlPEBaseInfoWork_GetMetaObject,
        "beNDMWMdlPEBaseInfoWork",
        0x114, /* instance size */
        beNDMWMdlPEBaseInfoWork_GetVTable,
        beNDMWMdlPEBaseInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlPEBaseInfoWork_callbackList /* callback list */
    );
}

void beNDMWMdlPEBaseInfoWork_GetMetaObject(void)
{
    beNDMWMdlPEBaseInfoWork_ResolveMetaObject();
}

static FieldFactory g_beNDMWMdlPEBaseInfoWork_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWMdlPEBaseInfoWork_fieldTable[] = {
    "_isPlayer",
    "_dispRamNoList",
    "_dispPosNoList",
    "_timerList",
    "_isFirstList",
    "_poisonDamage",
    "_poisonEndurance",
    "_downDataList",
    "_upDataList",
    "_messenger",
};
static igMetaField **g_beNDMWMdlPEBaseInfoWork_fieldHandles[] = {
    &g_beNDMWMdlPEBaseInfoWork_isPlayerMetaField,
    &g_beNDMWMdlPEBaseInfoWork_dispRamNoListMetaField,
    &g_beNDMWMdlPEBaseInfoWork_dispPosNoListMetaField,
    &g_beNDMWMdlPEBaseInfoWork_timerListMetaField,
    &g_beNDMWMdlPEBaseInfoWork_isFirstListMetaField,
    &g_beNDMWMdlPEBaseInfoWork_poisonDamageMetaField,
    &g_beNDMWMdlPEBaseInfoWork_poisonEnduranceMetaField,
    &g_beNDMWMdlPEBaseInfoWork_downDataListMetaField,
    &g_beNDMWMdlPEBaseInfoWork_upDataListMetaField,
    &g_beNDMWMdlPEBaseInfoWork_messengerMetaField,
};
static int g_beNDMWMdlPEBaseInfoWork_fieldOffsets[] = {
    236,
    240,
    244,
    248,
    252,
    256,
    260,
    264,
    268,
    272,
};

void beNDMWMdlPEBaseInfoWork_InitFields(void) {
    void *messenger;
    void *upDataList;
    void *downDataList;
    void *isFirstList;
    void *timerList;
    void *dispPosNoList;
    void *dispRamNoList;
    void *meta;
    int base;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)g_beNDMWMdlPEBaseInfoWork_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWMdlPEBaseInfoWork_ctorTable, 0xA);
    dispRamNoList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    ((igObjectRefMetaField *)dispRamNoList)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    dispPosNoList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2));
    ((igObjectRefMetaField *)dispPosNoList)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    timerList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3));
    ((igObjectRefMetaField *)timerList)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    isFirstList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4));
    ((igObjectRefMetaField *)isFirstList)->_metaObject = (int)Gap::Core::igBoolList::getClassTypeLazy();
    downDataList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7));
    ((igObjectRefMetaField *)downDataList)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    upDataList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8));
    ((igObjectRefMetaField *)upDataList)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    messenger = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWMdlPEBaseInfoWork_fieldTable, g_beNDMWMdlPEBaseInfoWork_fieldHandles, g_beNDMWMdlPEBaseInfoWork_fieldOffsets, base);
}

