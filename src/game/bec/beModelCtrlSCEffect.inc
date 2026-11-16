igMetaObject *g_beModelCtrlSCEffect_metaObject;
igMetaField *g_beModelCtrlSCEffect_geneRamNoMetaField;
igMetaField *g_beModelCtrlSCEffect_modelNameMetaField;
igMetaField *g_beModelCtrlSCEffect_seqNameMetaField;
igMetaField *g_beModelCtrlSCEffect_offsetMetaField;
igMetaField *g_beModelCtrlSCEffect_rotationMetaField;
igMetaField *g_beModelCtrlSCEffect_isSeqDeadMetaField;
igMetaField *g_beModelCtrlSCEffect_isPositionLockMetaField;

beModelCtrlSCEffect *beModelCtrlSCEffect_Create(int allocator) {
    beModelCtrlSCEffect_EnsureRegistered();
    return (beModelCtrlSCEffect *)igMetaObject_CreateInstance(*(int *)0x588800, allocator);
}

void *beModelCtrlSCEffect_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlSCEffect_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlSCEffect_EnsureRegistered();
    }
    return g_beModelCtrlSCEffect_metaObject;
}

int beModelCtrlSCEffect_GetVTable(void) {
    beModelCtrlSCEffect obj;
    int vtable;
    char **seqNameSlot;
    char **modelNameSlot;

    igObject_InitHeader(&obj);
    modelNameSlot = (char **)&obj._modelName;
    seqNameSlot = (char **)&obj._seqName;
    obj._vtable = (int)&g_beModelCtrlSCEffect_vtable[0];
    *modelNameSlot = 0;
    *seqNameSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beModelCtrlSCEffect_vtable[0];
    igStringRef_Release(seqNameSlot);
    igStringRef_Release(modelNameSlot);
    return vtable;
}

void beModelCtrlSCEffect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSCEffect_Register);
}

void *beModelCtrlSCEffect_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlSCEffect_metaObject,
        beModelCtrlSubComBase_Register,
        beModelCtrlSubComBase_GetPublishedMetaObject,
        beModelCtrlSCEffect_GetMetaObjectFunction,
        "beModelCtrlSCEffect",
        0x3c, /* instance size */
        beModelCtrlSCEffect_GetVTable,
        beModelCtrlSCEffect_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlSCEffect_GetMetaObjectFunction(void)
{
    beModelCtrlSCEffect_GetMetaObject();
}

static FieldFactory g_beModelCtrlSCEffect_ctorTable[] = {
    igIntMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igVec3fMetaField_CreateInstance,
    igVec3fMetaField_CreateInstance,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beModelCtrlSCEffect_fieldTable[] = {
    "_geneRamNo",
    "_modelName",
    "_seqName",
    "_offset",
    "_rotation",
    "_isSeqDead",
    "_isPositionLock",
};
static igMetaField **g_beModelCtrlSCEffect_fieldHandles[] = {
    &g_beModelCtrlSCEffect_geneRamNoMetaField,
    &g_beModelCtrlSCEffect_modelNameMetaField,
    &g_beModelCtrlSCEffect_seqNameMetaField,
    &g_beModelCtrlSCEffect_offsetMetaField,
    &g_beModelCtrlSCEffect_rotationMetaField,
    &g_beModelCtrlSCEffect_isSeqDeadMetaField,
    &g_beModelCtrlSCEffect_isPositionLockMetaField,
};
static int g_beModelCtrlSCEffect_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    44,
    56,
    57,
};

void beModelCtrlSCEffect_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beModelCtrlSCEffect_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlSCEffect_ctorTable, 7);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(meta, base)), -1);
    igMetaObject_NameFields(meta, g_beModelCtrlSCEffect_fieldTable, g_beModelCtrlSCEffect_fieldHandles, g_beModelCtrlSCEffect_fieldOffsets, base);
}

