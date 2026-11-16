igMetaObject *g_beNDMWStatusCtrlSkill_metaObject;
igMetaField *g_beNDMWStatusCtrlSkill_skillMenuMetaField;
igMetaField *g_beNDMWStatusCtrlSkill_shinkaCtrlMetaField;
igMetaField *g_beNDMWStatusCtrlSkill_skillListMetaField;

beNDMWStatusCtrlSkill *beNDMWStatusCtrlSkill_Create(int allocator) {
    beNDMWStatusCtrlSkill_EnsureRegistered();
    return (beNDMWStatusCtrlSkill *)igMetaObject_CreateInstance(g_beNDMWStatusCtrlSkill_metaObject, allocator);
}

void *beNDMWStatusCtrlSkill_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusCtrlSkill_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusCtrlSkill_EnsureRegistered();
    }
    return g_beNDMWStatusCtrlSkill_metaObject;
}

int beNDMWStatusCtrlSkill_GetVTable(void) {
    beNDMWStatusCtrlSkill obj;
    int vtable;
    int *shinkaCtrlRef;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWStatusCtrlSkill_vtable[0];
    shinkaCtrlRef = &obj._shinkaCtrl;
    *shinkaCtrlRef = 0;
    obj._skillList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusCtrlSkill_vtable[0];
    igSmartPointer_igIntList_Destruct(&obj._skillList, -1);
    igSmartPointer_beNDMWShinkaCtrl_Destruct((igSmartPointer<igObject> *)shinkaCtrlRef, -1);
    beNDMWListCtrl_Destroy((beNDMWListCtrl *)&obj, 0);
    return vtable;
}

void beNDMWStatusCtrlSkill_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlSkill_Register);
}

static igMetaObjectCallback g_beNDMWStatusCtrlSkill_callbackList[] = { beNDMWShinkaCtrl_EnsureRegistered, igIntList_EnsureRegistered, 0 };

void *beNDMWStatusCtrlSkill_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusCtrlSkill_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlSkill_GetMetaObjectFunction,
        "beNDMWStatusCtrlSkill",
        0x6c, /* instance size */
        beNDMWStatusCtrlSkill_GetVTable,
        beNDMWStatusCtrlSkill_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlSkill_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlSkill_GetMetaObjectFunction(void)
{
    beNDMWStatusCtrlSkill_GetMetaObject();
}

static FieldFactory g_beNDMWStatusCtrlSkill_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWStatusCtrlSkill_fieldTable[] = {
    "_skillMenu",
    "_shinkaCtrl",
    "_skillList",
};
static igMetaField **g_beNDMWStatusCtrlSkill_fieldHandles[] = {
    &g_beNDMWStatusCtrlSkill_skillMenuMetaField,
    &g_beNDMWStatusCtrlSkill_shinkaCtrlMetaField,
    &g_beNDMWStatusCtrlSkill_skillListMetaField,
};
static int g_beNDMWStatusCtrlSkill_fieldOffsets[] = {
    96,
    100,
    104,
};

void beNDMWStatusCtrlSkill_InitFields(void) {
    int base;
    void *skillList;
    void *shinkaCtrl;
    igMetaObject *meta;

    meta = g_beNDMWStatusCtrlSkill_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStatusCtrlSkill_ctorTable, 3);
    shinkaCtrl = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)shinkaCtrl)->_metaObject = (int)beNDMWShinkaCtrl_GetOrCreateMetaObject();
    ((igRefMetaField *)shinkaCtrl)->_construct = 1;
    skillList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)skillList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)skillList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWStatusCtrlSkill_fieldTable, g_beNDMWStatusCtrlSkill_fieldHandles, g_beNDMWStatusCtrlSkill_fieldOffsets, base);
}

