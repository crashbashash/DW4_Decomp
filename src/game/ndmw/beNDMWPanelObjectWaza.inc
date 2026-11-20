igMetaObject *g_beNDMWPanelObjectWaza_metaObject;
int g_beNDMWPanelObjectWaza_nameExternalEnumStorage;
igMetaField *g_beNDMWPanelObjectWaza_listFolderMetaField;
igMetaField *g_beNDMWPanelObjectWaza_listColorMetaField;

igMetaObject *beNDMWPanelObjectWaza_GetOrCreateMetaObject(void) {
    if (g_beNDMWPanelObjectWaza_metaObject == 0) {
        g_beNDMWPanelObjectWaza_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWPanelObjectWaza_metaObject;
}

igMetaObject *beNDMWPanelObjectWaza_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWPanelObjectWaza_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWPanelObjectWaza_EnsureRegistered();
done:
    return g_beNDMWPanelObjectWaza_metaObject;
}

int beNDMWPanelObjectWaza_GetVTable(void) {
    beNDMWPanelObjectWaza obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._playerDataList = 0;
    obj._textSetList = 0;
    obj._textColorList = 0;
    *(int **)&obj._vtable = &g_beNDMWPanelObjectWaza_vtable[0];
    obj._listFolder = 0;
    obj._listColor = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWPanelObjectWaza_vtable[0];
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._listColor, -1);
    igSmartPointer_igObjectList_Destruct((igSmartPointer<igObject> *)&obj._listFolder, -1);
    beNDMWPanelObject_Destroy((beNDMWPanelObject *)&obj, 0);
    return vtable;
}

void beNDMWPanelObjectWaza_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObjectWaza_Register);
}

static igMetaObjectCallback g_beNDMWPanelObjectWaza_callbackList[] = { igObjectList_EnsureRegistered, igIntList_EnsureRegistered, 0 };

CallbackArray *beNDMWPanelObjectWaza_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWPanelObjectWaza_metaObject,
        beNDMWPanelObject_Register,
        beNDMWPanelObject_GetPublishedMetaObject,
        beNDMWPanelObjectWaza_GetMetaObject,
        "beNDMWPanelObjectWaza",
        0x44, /* instance size */
        beNDMWPanelObjectWaza_GetVTable,
        beNDMWPanelObjectWaza_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelObjectWaza_callbackList /* callback list */
    );
}

void beNDMWPanelObjectWaza_GetMetaObject(void)
{
    beNDMWPanelObjectWaza_ResolveMetaObject();
}

static FieldFactory g_beNDMWPanelObjectWaza_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWPanelObjectWaza_fieldTable[] = {
    "_listFolder",
    "_listColor",
};
static igMetaField **g_beNDMWPanelObjectWaza_fieldHandles[] = {
    &g_beNDMWPanelObjectWaza_listFolderMetaField,
    &g_beNDMWPanelObjectWaza_listColorMetaField,
};
static int g_beNDMWPanelObjectWaza_fieldOffsets[] = {
    60,
    64,
};

void beNDMWPanelObjectWaza_InitFields(void) {
    int base;
    int pageIndex;
    void **inheritedPage;
    void *listFolder;
    void *listColor;
    void *meta;
    igIntMetaField *pageField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWPanelObjectWaza_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWPanelObjectWaza_ctorTable, 2);
    inheritedPage = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_page"));
    pageIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)((char *)((igMetaObject *)meta)->_metaFields), (int)inheritedPage);
    pageField = (igIntMetaField *)((igObjectDispatchView *)inheritedPage)->CloneViaMetadata(1);
    ((Gap::Core::igIntMetaField *)pageField)->setDefault(0);
    pageField->_externalEnumStorage = (int)(&g_beNDMWPanelObjectWaza_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, pageIndex, (igMetaField *)pageField);
    pageField->_refCount = pageField->_refCount - 1;
    if (((unsigned long long)(long long)pageField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(pageField);
    }
    listFolder = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base));
    ((igObjectRefMetaField *)listFolder)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)listFolder)->_construct = 1;
    listColor = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    ((igObjectRefMetaField *)listColor)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)listColor)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWPanelObjectWaza_fieldTable, g_beNDMWPanelObjectWaza_fieldHandles, g_beNDMWPanelObjectWaza_fieldOffsets, base);
}

