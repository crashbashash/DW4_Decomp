igMetaObject *g_beModelCtrlInfoRideOn_metaObject;
igMetaField *g_beModelCtrlInfoRideOn_modelNameMetaField;
igMetaField *g_beModelCtrlInfoRideOn_modelRamNoMetaField;
igMetaField *g_beModelCtrlInfoRideOn_modelNodeMetaField;
igMetaField *g_beModelCtrlInfoRideOn_oldMatrixMetaField;

void beModelCtrlInfoRideOn_Create(int arg0) {
    beModelCtrlInfoRideOn_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588AA8, arg0);
}

igMetaObject *beModelCtrlInfoRideOn_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlInfoRideOn_metaObject == 0) {
        g_beModelCtrlInfoRideOn_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beModelCtrlInfoRideOn_metaObject;
}

void *beModelCtrlInfoRideOn_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlInfoRideOn_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlInfoRideOn_EnsureRegistered();
    }
    return g_beModelCtrlInfoRideOn_metaObject;
}

int beModelCtrlInfoRideOn_GetVTable(void) {
    RideOnView info;
    return *(int *)((char *)&info + *(int *)((char *)g_objectSystem[0] + 916));
}

void beModelCtrlInfoRideOn_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoRideOn_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoRideOn_callbackList[] = { beModelCtrlNode2_EnsureRegistered, 0 };

void *beModelCtrlInfoRideOn_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoRideOn_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlInfoRideOn_GetMetaObjectFunction,
        "beModelCtrlInfoRideOn",
        0x54, /* instance size */
        beModelCtrlInfoRideOn_GetVTable,
        beModelCtrlInfoRideOn_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoRideOn_callbackList /* callback list */
    );
}

void beModelCtrlInfoRideOn_GetMetaObjectFunction(void)
{
    beModelCtrlInfoRideOn_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoRideOn_ctorTable[] = {
    igStringMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    FUN_00188660,
};
static const char *g_beModelCtrlInfoRideOn_fieldTable[] = {
    "_modelName",
    "_modelRamNo",
    "_modelNode",
    "_oldMatrix",
};
static igMetaField **g_beModelCtrlInfoRideOn_fieldHandles[] = {
    &g_beModelCtrlInfoRideOn_modelNameMetaField,
    &g_beModelCtrlInfoRideOn_modelRamNoMetaField,
    &g_beModelCtrlInfoRideOn_modelNodeMetaField,
    &g_beModelCtrlInfoRideOn_oldMatrixMetaField,
};
static int g_beModelCtrlInfoRideOn_fieldOffsets[] = {
    8,
    12,
    16,
    20,
};

void beModelCtrlInfoRideOn_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlInfoRideOn_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beModelCtrlInfoRideOn_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beModelCtrlNode2_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beModelCtrlInfoRideOn_fieldTable, g_beModelCtrlInfoRideOn_fieldHandles, g_beModelCtrlInfoRideOn_fieldOffsets, temp_s2);
}

