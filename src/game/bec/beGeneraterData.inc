igMetaObject *g_beGeneraterData_metaObject;
igMetaField *g_beGeneraterData_posMetaField;
igMetaField *g_beGeneraterData_genePosIsGlobalMetaField;
igMetaField *g_beGeneraterData_genePosListMetaField;
igMetaField *g_beGeneraterData_geneRotYRadianListMetaField;
igMetaField *g_beGeneraterData_geneEnemyIdMetaField;
igMetaField *g_beGeneraterData_geneEnemySeqMetaField;
igMetaField *g_beGeneraterData_startModeStrMetaField;
igMetaField *g_beGeneraterData_startDataMetaField;
igMetaField *g_beGeneraterData_fillModeStrMetaField;
igMetaField *g_beGeneraterData_fillDataMetaField;
igMetaField *g_beGeneraterData_callLuaMetaField;
igMetaField *g_beGeneraterData_playerDataListMetaField;

void *beGeneraterData_GetMetaObject(void) {
    igMetaObject *g = g_beGeneraterData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beGeneraterData_EnsureRegistered();
    }
    return g_beGeneraterData_metaObject;
}

int beGeneraterData_GetVTable(void) {
    beGeneraterData obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beGeneraterData_vtable[0];
    obj._genePosList = 0;
    obj._geneRotYRadianList = 0;
    obj._geneEnemySeq = 0;
    obj._startModeStr = 0;
    obj._fillModeStr = 0;
    obj._callLua = 0;
    obj._playerDataList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beGeneraterData_vtable[0];
    igSmartPointer_beGeneraterPlayerDataList_Destruct((igSmartPointer<igObject> *)&obj._playerDataList, (short)(-1));
    igStringRef_Destruct(&obj._callLua, -1);
    igStringRef_Destruct(&obj._fillModeStr, -1);
    igStringRef_Destruct(&obj._startModeStr, -1);
    igStringRef_Destruct(&obj._geneEnemySeq, -1);
    igSmartPointer_igFloatList_Destruct(&obj._geneRotYRadianList, -1);
    igSmartPointer_igVec3fList_Destruct(&obj._genePosList, -1);
    igNamedObject_Destroy(&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beGeneraterPlayerDataList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void beGeneraterData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterData_Register);
}

static igMetaObjectCallback g_beGeneraterData_callbackList[] = { igVec3fList_EnsureRegistered, igFloatList_EnsureRegistered, beGeneraterPlayerDataList_EnsureRegistered, 0 };

CallbackArray *beGeneraterData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beGeneraterData_GetMetaObjectFunction,
        "beGeneraterData",
        0x44, /* instance size */
        beGeneraterData_GetVTable,
        beGeneraterData_InitFields,
        0, /* extra callback item */
        g_beGeneraterData_callbackList /* callback list */
    );
}

void beGeneraterData_GetMetaObjectFunction(void)
{
    beGeneraterData_GetMetaObject();
}

static FieldFactory g_beGeneraterData_ctorTable[] = {
    igVec3fMetaField_CreateInstance,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igFloatMetaField_Create,
    igStringMetaField_Create,
    igFloatMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beGeneraterData_fieldTable[] = {
    "_pos",
    "_genePosIsGlobal",
    "_genePosList",
    "_geneRotYRadianList",
    "_geneEnemyId",
    "_geneEnemySeq",
    "_startModeStr",
    "_startData",
    "_fillModeStr",
    "_fillData",
    "_callLua",
    "_playerDataList",
};
static igMetaField **g_beGeneraterData_fieldHandles[] = {
    &g_beGeneraterData_posMetaField,
    &g_beGeneraterData_genePosIsGlobalMetaField,
    &g_beGeneraterData_genePosListMetaField,
    &g_beGeneraterData_geneRotYRadianListMetaField,
    &g_beGeneraterData_geneEnemyIdMetaField,
    &g_beGeneraterData_geneEnemySeqMetaField,
    &g_beGeneraterData_startModeStrMetaField,
    &g_beGeneraterData_startDataMetaField,
    &g_beGeneraterData_fillModeStrMetaField,
    &g_beGeneraterData_fillDataMetaField,
    &g_beGeneraterData_callLuaMetaField,
    &g_beGeneraterData_playerDataListMetaField,
};
static int g_beGeneraterData_fieldOffsets[] = {
    12,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
};

void beGeneraterData_InitFields(void) {
    int base;
    void *genePosList;
    void *geneRotYRadianList;
    void *playerDataList;
    igMetaObject *meta;

    meta = g_beGeneraterData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beGeneraterData_ctorTable, 0xC);
    genePosList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)genePosList)->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    ((igRefMetaField *)genePosList)->_construct = 1;
    geneRotYRadianList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)geneRotYRadianList)->_metaObject = (int)igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)geneRotYRadianList)->_construct = 1;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 5), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 0xA), 0);
    playerDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 0xB));
    ((igObjectRefMetaField *)playerDataList)->_metaObject = (int)beGeneraterPlayerDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)playerDataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beGeneraterData_fieldTable, g_beGeneraterData_fieldHandles, g_beGeneraterData_fieldOffsets, base);
}

