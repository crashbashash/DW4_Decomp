igMetaObject *g_beSvPlatDataGC_metaObject;
int g_beSvPlatDataGC_connectMaxStorage;
igMetaField *g_beSvPlatDataGC_fileNameMetaField;
igMetaField *g_beSvPlatDataGC_imageSizeMetaField;
igMetaField *g_beSvPlatDataGC_dataOffSetMetaField;
igMetaField *g_beSvPlatDataGC_bannerTypeMetaField;
igMetaField *g_beSvPlatDataGC_iconTypeMetaField;
igMetaField *g_beSvPlatDataGC_iconKazMetaField;
igMetaField *g_beSvPlatDataGC_iconSpeedMetaField;
igMetaField *g_beSvPlatDataGC_iconLoopTypeMetaField;
igMetaField *g_beSvPlatDataGC_banTplSizeMetaField;
igMetaField *g_beSvPlatDataGC_banTplDataMetaField;
igMetaField *g_beSvPlatDataGC_iconTplSizeMetaField;
igMetaField *g_beSvPlatDataGC_iconTplDataMetaField;
igMetaField *g_beSvPlatDataGC_commentMetaField;

void *beSvPlatDataGC_GetMetaObject(void) {
    igMetaObject *g = g_beSvPlatDataGC_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvPlatDataGC_EnsureRegistered();
    }
    return g_beSvPlatDataGC_metaObject;
}

int beSvPlatDataGC_GetVTable(void) {
    beSvPlatDataGC obj;
    int vtable;
    char **fileNameSlot;
    igObject **slotListSlot;

    igObject_InitHeader(&obj);
    slotListSlot = (igObject **)&obj._slotList;
    *slotListSlot = 0;
    obj._vtable = (int)&g_beSvPlatDataGC_vtable[0];
    fileNameSlot = (char **)&obj._fileName;
    *fileNameSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSvPlatDataGC_vtable[0];
    igStringRef_Release(fileNameSlot);
    obj._vtable = (int)&g_beSvPlatBaseData_vtable[0];
    igObjectRef_Release(slotListSlot);
    return vtable;
}

void beSvPlatDataGC_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataGC_Register);
}

CallbackArray *beSvPlatDataGC_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvPlatDataGC_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataGC_GetMetaObjectFunction,
        "beSvPlatDataGC",
        0x8c, /* instance size */
        beSvPlatDataGC_GetVTable,
        beSvPlatDataGC_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvPlatDataGC_GetMetaObjectFunction(void)
{
    beSvPlatDataGC_GetMetaObject();
}

static FieldFactory g_beSvPlatDataGC_ctorTable[] = {
    igStringMetaField_Create,
    igIntMetaField_Create,
    igIntArrayMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igMemoryRefMetaField_Create,
    igIntMetaField_Create,
    igMemoryRefMetaField_Create,
    igCharArrayMetaField_Create,
};
static const char *g_beSvPlatDataGC_fieldTable[] = {
    "_fileName",
    "_imageSize",
    "_dataOffSet",
    "_bannerType",
    "_iconType",
    "_iconKaz",
    "_iconSpeed",
    "_iconLoopType",
    "_banTplSize",
    "_banTplData",
    "_iconTplSize",
    "_iconTplData",
    "_comment",
};
static igMetaField **g_beSvPlatDataGC_fieldHandles[] = {
    &g_beSvPlatDataGC_fileNameMetaField,
    &g_beSvPlatDataGC_imageSizeMetaField,
    &g_beSvPlatDataGC_dataOffSetMetaField,
    &g_beSvPlatDataGC_bannerTypeMetaField,
    &g_beSvPlatDataGC_iconTypeMetaField,
    &g_beSvPlatDataGC_iconKazMetaField,
    &g_beSvPlatDataGC_iconSpeedMetaField,
    &g_beSvPlatDataGC_iconLoopTypeMetaField,
    &g_beSvPlatDataGC_banTplSizeMetaField,
    &g_beSvPlatDataGC_banTplDataMetaField,
    &g_beSvPlatDataGC_iconTplSizeMetaField,
    &g_beSvPlatDataGC_iconTplDataMetaField,
    &g_beSvPlatDataGC_commentMetaField,
};
static int g_beSvPlatDataGC_fieldOffsets[] = {
    104,
    108,
    24,
    112,
    116,
    120,
    124,
    128,
    132,
    32,
    136,
    36,
    40,
};

void beSvPlatDataGC_InitFields(void) {
    int base;
    int index;
    void **found;
    void *banTplData;
    void *comment;
    void *dataOffSet;
    void *iconTplData;
    void *meta;
    igIntMetaField *clone;

    meta = (void *)g_beSvPlatDataGC_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beSvPlatDataGC_ctorTable, 0xD);
    found = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_connectMax"));
    index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(((igMetaObject *)meta)->_metaFields), (int)found);
    clone = (igIntMetaField *)(((igObjectDispatchView *)found)->CloneViaMetadata(1));
    ((Gap::Core::igIntMetaField *)clone)->setDefault(2);
    clone->_externalEnumStorage = (int)(&g_beSvPlatDataGC_connectMaxStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, index, (igMetaField *)clone);
    clone->release();
    dataOffSet = igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2);
    ((igIntArrayMetaField *)dataOffSet)->_num = 2;
    banTplData = (igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9));
    ((igMemoryRefMetaField *)banTplData)->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    iconTplData = (igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xB));
    ((igMemoryRefMetaField *)iconTplData)->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    comment = igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xC);
    ((igCharArrayMetaField *)comment)->_num = 0x40;
    igMetaObject_NameFields((igMetaObject *)meta, g_beSvPlatDataGC_fieldTable, g_beSvPlatDataGC_fieldHandles, g_beSvPlatDataGC_fieldOffsets, base);
}

