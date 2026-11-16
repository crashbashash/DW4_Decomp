igMetaObject *g_beModelCtrlInfoRideOn3_metaObject;
int g_beModelCtrlInfoRideOn3_modelRamNoStorage;
igMetaField *g_beModelCtrlInfoRideOn3_worldPositionMetaField;
igMetaField *g_beModelCtrlInfoRideOn3_minSpeedMetaField;
igMetaField *g_beModelCtrlInfoRideOn3_maxSpeedMetaField;
igMetaField *g_beModelCtrlInfoRideOn3_minKyoriMetaField;
igMetaField *g_beModelCtrlInfoRideOn3_maxKyoriMetaField;

void beModelCtrlInfoRideOn3_Create(int arg0) {
    beModelCtrlInfoRideOn3_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588A58, arg0);
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
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    T_3519c0 *temp_v0_2;

    temp_s1 = (void *)(((void * *)&g_beModelCtrlInfoRideOn3_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beModelCtrlInfoRideOn3_ctorTable, 5);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_modelRamNo"));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T_3519c0 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igIntMetaField_SetDefault(temp_v0_2, 0x67);
    temp_v0_2->f1c = &g_beModelCtrlInfoRideOn3_modelRamNoStorage;
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->refs = temp_v0_2->refs - 1;
    if (((unsigned long long) ((long long) temp_v0_2->refs << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igMetaObject_NameFields(temp_s1, g_beModelCtrlInfoRideOn3_fieldTable, g_beModelCtrlInfoRideOn3_fieldHandles, g_beModelCtrlInfoRideOn3_fieldOffsets, temp_s2);
}

