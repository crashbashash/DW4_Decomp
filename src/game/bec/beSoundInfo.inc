igMetaObject *g_beSoundInfo_metaObject;
igMetaField *g_beSoundInfo_fnameListMetaField;
igMetaField *g_beSoundInfo_dataTypeMetaField;
igMetaField *g_beSoundInfo_baseVolumeMetaField;
igMetaField *g_beSoundInfo_sndfVolumeMetaField;

igMetaObject *beSoundInfo_GetMetaObject(void)
{
    igMetaObject *g = g_beSoundInfo_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beSoundInfo_EnsureRegistered();
    return g_beSoundInfo_metaObject;
}

int beSoundInfo_GetVTable(void) {
    beSoundInfo obj;
    int vtable;
    char *fnameListSlot;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beSoundInfo_vtable[0];
    fnameListSlot = (char *)&obj._fnameList;
    *(int *)fnameListSlot = 0;
    obj._dataType = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beSoundInfo_vtable[0];
    igStringRef_Destruct(&obj._dataType, -1);
    igSmartPointer_igNamedObjectList_Destruct(fnameListSlot, -1);
    beBaseInfo_Destroy((struct S_33ec80 *)&obj, (short)0);
    return vtable;
}

void beSoundInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSoundInfo_Register);
}

static igMetaObjectCallback g_beSoundInfo_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

void *beSoundInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSoundInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSoundInfo_GetMetaObjectFunction,
        "beSoundInfo",
        0x28, /* instance size */
        beSoundInfo_GetVTable,
        beSoundInfo_InitFields,
        0, /* extra callback item */
        g_beSoundInfo_callbackList /* callback list */
    );
}

void beSoundInfo_GetMetaObjectFunction(void)
{
    beSoundInfo_GetMetaObject();
}

static FieldFactory g_beSoundInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
    igShortMetaField_Create,
    igShortMetaField_Create,
};
static const char *g_beSoundInfo_fieldTable[] = {
    "_fnameList",
    "_dataType",
    "_baseVolume",
    "_sndfVolume",
};
static igMetaField **g_beSoundInfo_fieldHandles[] = {
    &g_beSoundInfo_fnameListMetaField,
    &g_beSoundInfo_dataTypeMetaField,
    &g_beSoundInfo_baseVolumeMetaField,
    &g_beSoundInfo_sndfVolumeMetaField,
};
static int g_beSoundInfo_fieldOffsets[] = {
    28,
    32,
    36,
    38,
};

void beSoundInfo_InitFields(void) {
    int base;
    void *fnameList;
    void *meta;

    meta = (void *)g_beSoundInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSoundInfo_ctorTable, 4);
    fnameList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)fnameList)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beSoundInfo_fieldTable, g_beSoundInfo_fieldHandles, g_beSoundInfo_fieldOffsets, base);
}

