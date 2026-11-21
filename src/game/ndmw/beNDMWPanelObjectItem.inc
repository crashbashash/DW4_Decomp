igMetaObject *g_beNDMWPanelObjectItem_metaObject;
int g_beNDMWPanelObjectItem_nameExternalEnumStorage;
igMetaField *g_beNDMWPanelObjectItem_listFolderMetaField;
igMetaField *g_beNDMWPanelObjectItem_listColorMetaField;

igMetaObject *beNDMWPanelObjectItem_GetOrCreateMetaObject(void) {
    if (g_beNDMWPanelObjectItem_metaObject == 0) {
        g_beNDMWPanelObjectItem_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWPanelObjectItem_metaObject;
}

igMetaObject *beNDMWPanelObjectItem_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWPanelObjectItem_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWPanelObjectItem_EnsureRegistered();
    return g_beNDMWPanelObjectItem_metaObject;
}

int beNDMWPanelObjectItem_GetVTable(void) {
    beNDMWPanelObjectItem obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._playerDataList = 0;
    obj._textSetList = 0;
    obj._textColorList = 0;
    *(int **)&obj._vtable = &g_beNDMWPanelObjectItem_vtable[0];
    obj._listFolder = 0;
    obj._listColor = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWPanelObjectItem_vtable[0];
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._listColor, -1);
    igSmartPointer_igObjectList_Destruct((igSmartPointer<igObject> *)&obj._listFolder, -1);
    beNDMWPanelObject_Destroy((beNDMWPanelObject *)&obj, 0);
    return vtable;
}

void beNDMWPanelObjectItem_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObjectItem_Register);
}

static igMetaObjectCallback g_beNDMWPanelObjectItem_callbackList[] = { Gap::Core::igObjectList::arkRegister, igIntList_EnsureRegistered, 0 };

CallbackArray *beNDMWPanelObjectItem_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWPanelObjectItem_metaObject,
        beNDMWPanelObject_Register,
        beNDMWPanelObject_GetPublishedMetaObject,
        beNDMWPanelObjectItem_GetMetaObject,
        "beNDMWPanelObjectItem",
        0x44, /* instance size */
        beNDMWPanelObjectItem_GetVTable,
        beNDMWPanelObjectItem_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelObjectItem_callbackList /* callback list */
    );
}

void beNDMWPanelObjectItem_GetMetaObject(void)
{
    beNDMWPanelObjectItem_ResolveMetaObject();
}

static FieldFactory g_beNDMWPanelObjectItem_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWPanelObjectItem_fieldTable[] = {
    "_listFolder",
    "_listColor",
};
static igMetaField **g_beNDMWPanelObjectItem_fieldHandles[] = {
    &g_beNDMWPanelObjectItem_listFolderMetaField,
    &g_beNDMWPanelObjectItem_listColorMetaField,
};
static int g_beNDMWPanelObjectItem_fieldOffsets[] = {
    60,
    64,
};

void beNDMWPanelObjectItem_InitFields(void) {
    int base;
    int pageIndex;
    void **inheritedPage;
    void *listFolder;
    void *listColor;
    void *meta;
    igIntMetaField *pageField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWPanelObjectItem_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWPanelObjectItem_ctorTable, 2);
    inheritedPage = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_page"));
    pageIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)((char *)((igMetaObject *)meta)->_metaFields), (int)inheritedPage);
    pageField = (igIntMetaField *)((igObjectDispatchView *)inheritedPage)->CloneViaMetadata(1);
    ((Gap::Core::igIntMetaField *)pageField)->setDefault(1);
    pageField->_externalEnumStorage = (int)(&g_beNDMWPanelObjectItem_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, pageIndex, (igMetaField *)pageField);
    pageField->_refCount = pageField->_refCount - 1;
    if (((unsigned long long)(long long)pageField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(pageField);
    }
    listFolder = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base));
    ((igObjectRefMetaField *)listFolder)->_metaObject = (int)Gap::Core::igObjectList::getClassTypeLazy();
    ((igObjectRefMetaField *)listFolder)->_construct = 1;
    listColor = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    ((igObjectRefMetaField *)listColor)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)listColor)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWPanelObjectItem_fieldTable, g_beNDMWPanelObjectItem_fieldHandles, g_beNDMWPanelObjectItem_fieldOffsets, base);
}

