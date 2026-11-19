igMetaObject *g_beModelCtrlInfoRideOn_metaObject;
igMetaField *g_beModelCtrlInfoRideOn_modelNameMetaField;
igMetaField *g_beModelCtrlInfoRideOn_modelRamNoMetaField;
igMetaField *g_beModelCtrlInfoRideOn_modelNodeMetaField;
igMetaField *g_beModelCtrlInfoRideOn_oldMatrixMetaField;

beModelCtrlInfoRideOn *beModelCtrlInfoRideOn_Create(int allocator) {
    beModelCtrlInfoRideOn_EnsureRegistered();
    return (beModelCtrlInfoRideOn *)igMetaObject_CreateInstance(g_beModelCtrlInfoRideOn_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beModelCtrlInfoRideOn_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlInfoRideOn_metaObject == 0) {
        g_beModelCtrlInfoRideOn_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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
    return *(int *)((char *)&info + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlInfoRideOn_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoRideOn_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoRideOn_callbackList[] = { beModelCtrlNode2_EnsureRegistered, 0 };

CallbackArray *beModelCtrlInfoRideOn_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoRideOn_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
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
    igMatrix44fMetaField_CreateInstance,
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
    int base;
    void *modelNode;
    igMetaObject *meta;

    meta = g_beModelCtrlInfoRideOn_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlInfoRideOn_ctorTable, 4);
    modelNode = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)modelNode)->_metaObject = (int)beModelCtrlNode2_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beModelCtrlInfoRideOn_fieldTable, g_beModelCtrlInfoRideOn_fieldHandles, g_beModelCtrlInfoRideOn_fieldOffsets, base);
}

