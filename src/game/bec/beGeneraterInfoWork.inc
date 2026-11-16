igMetaObject *g_beGeneraterInfoWork_metaObject;
igMetaField *g_beGeneraterInfoWork_isSystemFreezeMetaField;
igMetaField *g_beGeneraterInfoWork_isFreezeMetaField;
igMetaField *g_beGeneraterInfoWork_playerCountMetaField;
igMetaField *g_beGeneraterInfoWork_nokoriKazuMetaField;
igMetaField *g_beGeneraterInfoWork_enemyRamListMetaField;
igMetaField *g_beGeneraterInfoWork_genePointMetaField;
igMetaField *g_beGeneraterInfoWork_geneEnemyNameMetaField;
igMetaField *g_beGeneraterInfoWork_geneEnemyRecNoMetaField;
igMetaField *g_beGeneraterInfoWork_geneEnemyMHpMetaField;

beGeneraterInfoWork *beGeneraterInfoWork_Create(int allocator) {
    beGeneraterInfoWork_EnsureRegistered();
    return (beGeneraterInfoWork *)igMetaObject_CreateInstance(*(int *)0x589478, allocator);
}

igMetaObject *beGeneraterInfoWork_GetOrCreateMetaObject(void) {
    if (g_beGeneraterInfoWork_metaObject == 0) {
        g_beGeneraterInfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beGeneraterInfoWork_metaObject;
}

igMetaObject *beGeneraterInfoWork_GetMetaObject(void)
{
    igMetaObject *g = g_beGeneraterInfoWork_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beGeneraterInfoWork_EnsureRegistered();
    return g_beGeneraterInfoWork_metaObject;
}

int beGeneraterInfoWork_GetVTable(void) {
    beGeneraterInfoWork obj;
    int vtable;
    char **geneEnemyNameSlot;
    igObject **enemyRamListSlot;

    igObject_InitHeader(&obj);
    enemyRamListSlot = (igObject **)&obj._enemyRamList;
    geneEnemyNameSlot = (char **)&obj._geneEnemyName;
    obj._vtable = (int)&g_beGeneraterInfoWork_vtable[0];
    *enemyRamListSlot = 0;
    *geneEnemyNameSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beGeneraterInfoWork_vtable[0];
    igStringRef_Release(geneEnemyNameSlot);
    igObjectRef_Release(enemyRamListSlot);
    return vtable;
}

void beGeneraterInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterInfoWork_Register);
}

static igMetaObjectCallback g_beGeneraterInfoWork_callbackList[] = { beBaseInfoRamList_EnsureRegistered, 0 };

void *beGeneraterInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beGeneraterInfoWork_GetMetaObjectFunction,
        "beGeneraterInfoWork",
        0x28, /* instance size */
        beGeneraterInfoWork_GetVTable,
        beGeneraterInfoWork_InitFields,
        0, /* extra callback item */
        g_beGeneraterInfoWork_callbackList /* callback list */
    );
}

void beGeneraterInfoWork_GetMetaObjectFunction(void)
{
    beGeneraterInfoWork_GetMetaObject();
}

static FieldFactory g_beGeneraterInfoWork_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igStringMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beGeneraterInfoWork_fieldTable[] = {
    "_isSystemFreeze",
    "_isFreeze",
    "_playerCount",
    "_nokoriKazu",
    "_enemyRamList",
    "_genePoint",
    "_geneEnemyName",
    "_geneEnemyRecNo",
    "_geneEnemyMHp",
};
static igMetaField **g_beGeneraterInfoWork_fieldHandles[] = {
    &g_beGeneraterInfoWork_isSystemFreezeMetaField,
    &g_beGeneraterInfoWork_isFreezeMetaField,
    &g_beGeneraterInfoWork_playerCountMetaField,
    &g_beGeneraterInfoWork_nokoriKazuMetaField,
    &g_beGeneraterInfoWork_enemyRamListMetaField,
    &g_beGeneraterInfoWork_genePointMetaField,
    &g_beGeneraterInfoWork_geneEnemyNameMetaField,
    &g_beGeneraterInfoWork_geneEnemyRecNoMetaField,
    &g_beGeneraterInfoWork_geneEnemyMHpMetaField,
};
static int g_beGeneraterInfoWork_fieldOffsets[] = {
    8,
    9,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
};

void beGeneraterInfoWork_InitFields(void) {
    int base;
    void *enemyRamList;
    void *meta;

    meta = (void *)g_beGeneraterInfoWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beGeneraterInfoWork_ctorTable, 9);
    enemyRamList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)enemyRamList)->_metaObject = (int)beBaseInfoRamList_GetOrCreateMetaObject();
    ((igRefMetaField *)enemyRamList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beGeneraterInfoWork_fieldTable, g_beGeneraterInfoWork_fieldHandles, g_beGeneraterInfoWork_fieldOffsets, base);
}

