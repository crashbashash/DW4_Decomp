igMetaObject *g_beModelCtrlInfoRideOn3_metaObject;
int g_beModelCtrlInfoRideOn3_modelRamNoStorage;
igMetaField *g_beModelCtrlInfoRideOn3_worldPositionMetaField;
igMetaField *g_beModelCtrlInfoRideOn3_minSpeedMetaField;
igMetaField *g_beModelCtrlInfoRideOn3_maxSpeedMetaField;
igMetaField *g_beModelCtrlInfoRideOn3_minKyoriMetaField;
igMetaField *g_beModelCtrlInfoRideOn3_maxKyoriMetaField;

void beModelCtrlInfoRideOn3_Create(int allocator) {
    beModelCtrlInfoRideOn3_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588A58, allocator);
}

void *beModelCtrlInfoRideOn3_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlInfoRideOn3_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlInfoRideOn3_EnsureRegistered();
    }
    return g_beModelCtrlInfoRideOn3_metaObject;
}

int beModelCtrlInfoRideOn3_GetVTable(void) {
    RideOn3View info;
    return *(int *)((char *)&info + *(int *)((char *)g_objectSystem[0] + 916));
}

void beModelCtrlInfoRideOn3_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoRideOn3_Register);
}

void *beModelCtrlInfoRideOn3_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoRideOn3_metaObject,
        beModelCtrlInfoRideOn_Register,
        beModelCtrlInfoRideOn_GetPublishedMetaObject,
        beModelCtrlInfoRideOn3_GetMetaObjectFunction,
        "beModelCtrlInfoRideOn3",
        0x70, /* instance size */
        beModelCtrlInfoRideOn3_GetVTable,
        beModelCtrlInfoRideOn3_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfoRideOn3_GetMetaObjectFunction(void)
{
    beModelCtrlInfoRideOn3_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoRideOn3_ctorTable[] = {
    FUN_00187890,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_beModelCtrlInfoRideOn3_fieldTable[] = {
    "_worldPosition",
    "_minSpeed",
    "_maxSpeed",
    "_minKyori",
    "_maxKyori",
};
static igMetaField **g_beModelCtrlInfoRideOn3_fieldHandles[] = {
    &g_beModelCtrlInfoRideOn3_worldPositionMetaField,
    &g_beModelCtrlInfoRideOn3_minSpeedMetaField,
    &g_beModelCtrlInfoRideOn3_maxSpeedMetaField,
    &g_beModelCtrlInfoRideOn3_minKyoriMetaField,
    &g_beModelCtrlInfoRideOn3_maxKyoriMetaField,
};
static int g_beModelCtrlInfoRideOn3_fieldOffsets[] = {
    84,
    96,
    100,
    104,
    108,
};

void beModelCtrlInfoRideOn3_InitFields(void) {
    int base;
    int index;
    void **found;
    void *meta;
    igIntMetaField *clone;

    meta = (void *)g_beModelCtrlInfoRideOn3_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlInfoRideOn3_ctorTable, 5);
    found = (void **)(igMetaObject_FindFieldByName(meta, "_modelRamNo"));
    index = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, found);
    clone = (igIntMetaField *)(((DW4VC_84_1 *)(found))->vX((int)(1)));
    igIntMetaField_SetDefault(clone, 0x67);
    clone->_externalEnumStorage = (int)(&g_beModelCtrlInfoRideOn3_modelRamNoStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    igMetaObject_NameFields(meta, g_beModelCtrlInfoRideOn3_fieldTable, g_beModelCtrlInfoRideOn3_fieldHandles, g_beModelCtrlInfoRideOn3_fieldOffsets, base);
}

