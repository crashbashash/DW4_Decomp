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
    union U u;
    int temp_s1;
    char *p1;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&g_beSoundInfo_vtable[0];
    p1 = &u.b[28];
    *(int *)p1 = 0;
    *(int *)&u.b[32] = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beSoundInfo_vtable[0];
    igStringRef_Destruct(&u.b[32], -1);
    FUN_00199450(p1, -1);
    FUN_0033ec80((struct S_33ec80 *)u.b, (short)0);
    return temp_s1;
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

