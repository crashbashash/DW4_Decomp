igMetaObject *g_beModelCtrlInfoRideOn2_metaObject;
int g_beModelCtrlInfoRideOn2_modelRamNoStorage;
igMetaField *g_beModelCtrlInfoRideOn2_vectorMetaField;

beModelCtrlInfoRideOn2 *beModelCtrlInfoRideOn2_Create(int allocator) {
    beModelCtrlInfoRideOn2_EnsureRegistered();
    return (beModelCtrlInfoRideOn2 *)igMetaObject_CreateInstance(g_beModelCtrlInfoRideOn2_metaObject, (igMemoryPoolView *)allocator);
}

void *beModelCtrlInfoRideOn2_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlInfoRideOn2_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlInfoRideOn2_EnsureRegistered();
    }
    return g_beModelCtrlInfoRideOn2_metaObject;
}

int beModelCtrlInfoRideOn2_GetVTable(void) {
    RideOn2View info;
    return *(int *)((char *)&info + *(int *)((char *)g_objectSystem + 916));
}

void beModelCtrlInfoRideOn2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoRideOn2_Register);
}

CallbackArray *beModelCtrlInfoRideOn2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoRideOn2_metaObject,
        beModelCtrlInfoRideOn_Register,
        beModelCtrlInfoRideOn_GetPublishedMetaObject,
        beModelCtrlInfoRideOn2_GetMetaObjectFunction,
        "beModelCtrlInfoRideOn2",
        0x60, /* instance size */
        beModelCtrlInfoRideOn2_GetVTable,
        beModelCtrlInfoRideOn2_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfoRideOn2_GetMetaObjectFunction(void)
{
    beModelCtrlInfoRideOn2_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoRideOn2_ctorTable[] = {
    igVec3fMetaField_CreateInstance,
};
static const char *g_beModelCtrlInfoRideOn2_fieldTable[] = {
    "_vector",
};
static igMetaField **g_beModelCtrlInfoRideOn2_fieldHandles[] = {
    &g_beModelCtrlInfoRideOn2_vectorMetaField,
};
static int g_beModelCtrlInfoRideOn2_fieldOffsets[] = {
    84,
};

void beModelCtrlInfoRideOn2_InitFields(void) {
    int base;
    int index;
    void **found;
    void *meta;
    igIntMetaField *clone;

    meta = (void *)g_beModelCtrlInfoRideOn2_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beModelCtrlInfoRideOn2_ctorTable, 1);
    found = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_modelRamNo"));
    index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(((igMetaObject *)meta)->_metaFields), (int)found);
    clone = (igIntMetaField *)(((igObjectDispatchView *)found)->CloneViaMetadata(1));
    igIntMetaField_SetDefault((igMetaField *)clone, 0x66);
    clone->_externalEnumStorage = (int)(&g_beModelCtrlInfoRideOn2_modelRamNoStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, index, (igMetaField *)clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    igMetaObject_NameFields((igMetaObject *)meta, g_beModelCtrlInfoRideOn2_fieldTable, g_beModelCtrlInfoRideOn2_fieldHandles, g_beModelCtrlInfoRideOn2_fieldOffsets, base);
}

