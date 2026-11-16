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
    struct Obj_35fbb0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &g_beGeneraterData_vtable[0];
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w13 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beGeneraterData_vtable[0];
    FUN_0035fcd0((igSmartPointer<igObject> *)&obj.w16, (short)(-1));
    igStringRef_Destruct(&obj.w15, -1);
    igStringRef_Destruct(&obj.w13, -1);
    igStringRef_Destruct(&obj.w11, -1);
    igStringRef_Destruct(&obj.w10, -1);
    FUN_001354b0(&obj.w8, -1);
    FUN_001374b0(&obj.w7, -1);
    FUN_00131bc0(&obj, 0);
    return t;
}

igSmartPointer<igObject> *FUN_0035fcd0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beGeneraterData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterData_Register);
}

static igMetaObjectCallback g_beGeneraterData_callbackList[] = { igVec3fList_EnsureRegistered, igFloatList_EnsureRegistered, beGeneraterPlayerDataList_EnsureRegistered, 0 };

void *beGeneraterData_Register(void) {
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
    FUN_00187890,
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
    void *meta;

    meta = (void *)g_beGeneraterData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beGeneraterData_ctorTable, 0xC);
    genePosList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)genePosList)->_metaObject = igVec3fList_GetOrCreateMetaObject();
    ((igRefMetaField *)genePosList)->_construct = 1;
    geneRotYRadianList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)geneRotYRadianList)->_metaObject = igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)geneRotYRadianList)->_construct = 1;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 5), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 0xA), 0);
    playerDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 0xB));
    ((igObjectRefMetaField *)playerDataList)->_metaObject = (int)beGeneraterPlayerDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)playerDataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beGeneraterData_fieldTable, g_beGeneraterData_fieldHandles, g_beGeneraterData_fieldOffsets, base);
}

