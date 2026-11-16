igMetaObject *g_beTargetObj_metaObject;
igMetaField *g_beTargetObj_playerPosListMetaField;
igMetaField *g_beTargetObj_playerRamNoListMetaField;
igMetaField *g_beTargetObj_enemyPosListMetaField;

beTargetObj *beTargetObj_CreateInstance(int allocator) {
    beTargetObj_EnsureRegistered();
    return (beTargetObj *)igMetaObject_CreateInstance(*(int *)0x587CE8, allocator);
}

igMetaObject *beTargetObj_GetOrCreateMetaObject(void) {
    if (g_beTargetObj_metaObject == 0) {
        g_beTargetObj_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beTargetObj_metaObject;
}

void *beTargetObj_GetMetaObject(void) {
    igMetaObject *g = g_beTargetObj_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beTargetObj_EnsureRegistered();
    }
    return g_beTargetObj_metaObject;
}

int beTargetObj_GetVTable(void) {
    beTargetObj obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beTargetObj_vtable[0];
    obj._playerPosList = 0;
    obj._playerRamNoList = 0;
    obj._enemyPosList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beTargetObj_vtable[0];
    igSmartPointer_igVec3fList_Destruct(&obj._enemyPosList, -1);
    igSmartPointer_igIntList_Destruct(&obj._playerRamNoList, -1);
    igSmartPointer_igVec3fList_Destruct(&obj._playerPosList, -1);
    igInfoManager_Destroy(&obj, 0);
    return vtable;
}

void beTargetObj_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTargetObj_Register);
}

static igMetaObjectCallback g_beTargetObj_callbackList[] = { igVec3fList_EnsureRegistered, igIntList_EnsureRegistered, 0 };

void *beTargetObj_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTargetObj_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beTargetObj_GetMetaObjectFunction,
        "beTargetObj",
        0x1c, /* instance size */
        beTargetObj_GetVTable,
        beTargetObj_InitFields,
        0, /* extra callback item */
        g_beTargetObj_callbackList /* callback list */
    );
}

void beTargetObj_GetMetaObjectFunction(void)
{
    beTargetObj_GetMetaObject();
}

static FieldFactory g_beTargetObj_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beTargetObj_fieldTable[] = {
    "_playerPosList",
    "_playerRamNoList",
    "_enemyPosList",
};
static igMetaField **g_beTargetObj_fieldHandles[] = {
    &g_beTargetObj_playerPosListMetaField,
    &g_beTargetObj_playerRamNoListMetaField,
    &g_beTargetObj_enemyPosListMetaField,
};
static int g_beTargetObj_fieldOffsets[] = {
    16,
    20,
    24,
};

void beTargetObj_InitFields(void) {
    int base;
    void *enemyPosList;
    void *playerRamNoList;
    void *playerPosList;
    void *meta;

    meta = (void *)g_beTargetObj_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beTargetObj_ctorTable, 3);
    playerPosList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)playerPosList)->_metaObject = igVec3fList_GetOrCreateMetaObject();
    ((igRefMetaField *)playerPosList)->_construct = 1;
    playerRamNoList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)playerRamNoList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)playerRamNoList)->_construct = 1;
    enemyPosList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)enemyPosList)->_metaObject = igVec3fList_GetOrCreateMetaObject();
    ((igRefMetaField *)enemyPosList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beTargetObj_fieldTable, g_beTargetObj_fieldHandles, g_beTargetObj_fieldOffsets, base);
}

