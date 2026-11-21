igMetaObject *g_beModelCtrlInfoDataAIH_metaObject;
int g_beModelCtrlInfoDataAIH_nameStorage;
igMetaField *g_beModelCtrlInfoDataAIH_isXHomingMetaField;
igMetaField *g_beModelCtrlInfoDataAIH_isYHomingMetaField;
igMetaField *g_beModelCtrlInfoDataAIH_firstFrameMetaField;
igMetaField *g_beModelCtrlInfoDataAIH_secondFrameMetaField;
igMetaField *g_beModelCtrlInfoDataAIH_areaSquareMetaField;
igMetaField *g_beModelCtrlInfoDataAIH_limitRotXMetaField;
igMetaField *g_beModelCtrlInfoDataAIH_limitRotYMetaField;
igMetaField *g_beModelCtrlInfoDataAIH_limitCountMetaField;

void *beModelCtrlInfoDataAIH_GetMetaObject(void) {
    unsigned char b;
    if (g_beModelCtrlInfoDataAIH_metaObject != 0) {
        b = (g_beModelCtrlInfoDataAIH_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beModelCtrlInfoDataAIH_EnsureRegistered();
done:
    return g_beModelCtrlInfoDataAIH_metaObject;
}

int beModelCtrlInfoDataAIH_GetVTable(void) {
    beModelCtrlInfoDataAIH obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beModelCtrlInfoDataAIH_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlInfoDataAIH_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataAIH_Register);
}

CallbackArray *beModelCtrlInfoDataAIH_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoDataAIH_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataAIH_GetMetaObjectFunction,
        "beModelCtrlInfoDataAIH",
        0x2c, /* instance size */
        beModelCtrlInfoDataAIH_GetVTable,
        beModelCtrlInfoDataAIH_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfoDataAIH_GetMetaObjectFunction(void)
{
    beModelCtrlInfoDataAIH_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoDataAIH_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beModelCtrlInfoDataAIH_fieldTable[] = {
    "_isXHoming",
    "_isYHoming",
    "_firstFrame",
    "_secondFrame",
    "_areaSquare",
    "_limitRotX",
    "_limitRotY",
    "_limitCount",
};
static igMetaField **g_beModelCtrlInfoDataAIH_fieldHandles[] = {
    &g_beModelCtrlInfoDataAIH_isXHomingMetaField,
    &g_beModelCtrlInfoDataAIH_isYHomingMetaField,
    &g_beModelCtrlInfoDataAIH_firstFrameMetaField,
    &g_beModelCtrlInfoDataAIH_secondFrameMetaField,
    &g_beModelCtrlInfoDataAIH_areaSquareMetaField,
    &g_beModelCtrlInfoDataAIH_limitRotXMetaField,
    &g_beModelCtrlInfoDataAIH_limitRotYMetaField,
    &g_beModelCtrlInfoDataAIH_limitCountMetaField,
};
static int g_beModelCtrlInfoDataAIH_fieldOffsets[] = {
    16,
    17,
    20,
    24,
    28,
    32,
    36,
    40,
};

void beModelCtrlInfoDataAIH_InitFields(void) {
    int base;
    int index;
    void **found;
    void *meta;
    igStringMetaField *clone;

    meta = (void *)g_beModelCtrlInfoDataAIH_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beModelCtrlInfoDataAIH_ctorTable, 8);
    found = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(((igMetaObject *)meta)->_metaFields), (int)found);
    clone = (igStringMetaField *)(((igObjectDispatchView *)found)->CloneViaMetadata(1));
    ((Gap::Core::igStringMetaField *)clone)->setDefault("AIH");
    clone->_externalEnumStorage = (int)(&g_beModelCtrlInfoDataAIH_nameStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, index, (igMetaField *)clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    igMetaObject_NameFields((igMetaObject *)meta, g_beModelCtrlInfoDataAIH_fieldTable, g_beModelCtrlInfoDataAIH_fieldHandles, g_beModelCtrlInfoDataAIH_fieldOffsets, base);
}

