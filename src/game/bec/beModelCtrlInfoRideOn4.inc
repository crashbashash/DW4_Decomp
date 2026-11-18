igMetaObject *g_beModelCtrlInfoRideOn4_metaObject;
int g_beModelCtrlInfoRideOn4_modelRamNoStorage;
igMetaField *g_beModelCtrlInfoRideOn4_oldPlayerPosMetaField;
igMetaField *g_beModelCtrlInfoRideOn4_vectorMetaField;
igMetaField *g_beModelCtrlInfoRideOn4_scalarMetaField;
igMetaField *g_beModelCtrlInfoRideOn4_limitterMetaField;
igMetaField *g_beModelCtrlInfoRideOn4_isFirstMetaField;

beModelCtrlInfoRideOn4 *beModelCtrlInfoRideOn4_Create(int allocator) {
    beModelCtrlInfoRideOn4_EnsureRegistered();
    return (beModelCtrlInfoRideOn4 *)igMetaObject_CreateInstance(g_beModelCtrlInfoRideOn4_metaObject, (igMemoryPoolView *)allocator);
}

void *beModelCtrlInfoRideOn4_GetMetaObject(void) {
    unsigned char b;
    if (g_beModelCtrlInfoRideOn4_metaObject != 0) {
        b = (g_beModelCtrlInfoRideOn4_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beModelCtrlInfoRideOn4_EnsureRegistered();
done:
    return g_beModelCtrlInfoRideOn4_metaObject;
}

int beModelCtrlInfoRideOn4_GetVTable(void) {
    RideOn4View info;
    return *(int *)((char *)&info + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlInfoRideOn4_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoRideOn4_Register);
}

CallbackArray *beModelCtrlInfoRideOn4_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoRideOn4_metaObject,
        beModelCtrlInfoRideOn_Register,
        beModelCtrlInfoRideOn_GetPublishedMetaObject,
        beModelCtrlInfoRideOn4_GetMetaObjectFunction,
        "beModelCtrlInfoRideOn4",
        0x78, /* instance size */
        beModelCtrlInfoRideOn4_GetVTable,
        beModelCtrlInfoRideOn4_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfoRideOn4_GetMetaObjectFunction(void)
{
    beModelCtrlInfoRideOn4_GetMetaObject();
}

igMetaObject *beModelCtrlInfoRideOn_GetPublishedMetaObject(void) {
    return g_beModelCtrlInfoRideOn_metaObject;
}

static FieldFactory g_beModelCtrlInfoRideOn4_ctorTable[] = {
    igVec3fMetaField_CreateInstance,
    igVec3fMetaField_CreateInstance,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beModelCtrlInfoRideOn4_fieldTable[] = {
    "_oldPlayerPos",
    "_vector",
    "_scalar",
    "_limitter",
    "_isFirst",
};
static igMetaField **g_beModelCtrlInfoRideOn4_fieldHandles[] = {
    &g_beModelCtrlInfoRideOn4_oldPlayerPosMetaField,
    &g_beModelCtrlInfoRideOn4_vectorMetaField,
    &g_beModelCtrlInfoRideOn4_scalarMetaField,
    &g_beModelCtrlInfoRideOn4_limitterMetaField,
    &g_beModelCtrlInfoRideOn4_isFirstMetaField,
};
static int g_beModelCtrlInfoRideOn4_fieldOffsets[] = {
    84,
    96,
    108,
    112,
    116,
};

void beModelCtrlInfoRideOn4_InitFields(void) {
    int base;
    int index;
    void **found;
    void *meta;
    igIntMetaField *clone;

    meta = (void *)g_beModelCtrlInfoRideOn4_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beModelCtrlInfoRideOn4_ctorTable, 5);
    found = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_modelRamNo"));
    index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(((igMetaObject *)meta)->_metaFields), (int)found);
    clone = (igIntMetaField *)(((igObjectDispatchView *)found)->CloneViaMetadata(1));
    igIntMetaField_SetDefault((igMetaField *)clone, 0x68);
    clone->_externalEnumStorage = (int)(&g_beModelCtrlInfoRideOn4_modelRamNoStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, index, (igMetaField *)clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    igMetaObject_NameFields((igMetaObject *)meta, g_beModelCtrlInfoRideOn4_fieldTable, g_beModelCtrlInfoRideOn4_fieldHandles, g_beModelCtrlInfoRideOn4_fieldOffsets, base);
}

