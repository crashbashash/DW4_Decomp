igMetaObject *g_beNDMWPanelObjectStat_metaObject;
int g_beNDMWPanelObjectStat_nameExternalEnumStorage;
igMetaField *g_beNDMWPanelObjectStat_listFolderMetaField;
igMetaField *g_beNDMWPanelObjectStat_listColorMetaField;
igMetaField *g_beNDMWPanelObjectStat_playerWorkMetaField;

igMetaObject *beNDMWPanelObjectStat_GetOrCreateMetaObject(void) {
    if (g_beNDMWPanelObjectStat_metaObject == 0) {
        g_beNDMWPanelObjectStat_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWPanelObjectStat_metaObject;
}

igMetaObject *beNDMWPanelObjectStat_ResolveMetaObject(void)
{
    igMetaObject *g = g_beNDMWPanelObjectStat_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWPanelObjectStat_EnsureRegistered();
    return g_beNDMWPanelObjectStat_metaObject;
}

int beNDMWPanelObjectStat_GetVTable(void) {
    beNDMWPanelObjectStat obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._playerDataList = 0;
    obj._textSetList = 0;
    obj._textColorList = 0;
    *(int **)&obj._vtable = &g_beNDMWPanelObjectStat_vtable[0];
    obj._listFolder = 0;
    obj._listColor = 0;
    obj._playerWork = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWPanelObjectStat_vtable[0];
    igSmartPointer_beNDMWMdlPlayerInfoWork_Destruct((igSmartPointer<igObject> *)&obj._playerWork, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._listColor, -1);
    igSmartPointer_igStringRefList_Destruct((igSmartPointer<igObject> *)&obj._listFolder, -1);
    beNDMWPanelObject_Destroy((beNDMWPanelObject *)&obj, 0);
    return vtable;
}

beNDMWPanelObject *beNDMWPanelObject_Destroy(beNDMWPanelObject *self, short flags) {
    if (self) {
        *(int **)&self->_vtable = &g_beNDMWPanelObject_vtable[0];
        if (&self->_textColorList != 0) {
            igRelease((igObject *)self->_textColorList);
        }
        if (&self->_textSetList != 0) {
            igRelease((igObject *)self->_textSetList);
        }
        if (&self->_playerDataList != 0) {
            igRelease((igObject *)self->_playerDataList);
        }
        if (flags > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

void beNDMWPanelObjectStat_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObjectStat_Register);
}

static igMetaObjectCallback g_beNDMWPanelObjectStat_callbackList[] = { igStringRefList_EnsureRegistered, Gap::Core::igIntList::arkRegister, beNDMWMdlPlayerInfoWork_EnsureRegistered, 0 };

CallbackArray *beNDMWPanelObjectStat_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWPanelObjectStat_metaObject,
        beNDMWPanelObject_Register,
        beNDMWPanelObject_GetPublishedMetaObject,
        beNDMWPanelObjectStat_GetMetaObject,
        "beNDMWPanelObjectStat",
        0x48, /* instance size */
        beNDMWPanelObjectStat_GetVTable,
        beNDMWPanelObjectStat_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelObjectStat_callbackList /* callback list */
    );
}

void beNDMWPanelObjectStat_GetMetaObject(void)
{
    beNDMWPanelObjectStat_ResolveMetaObject();
}

igMetaObject *beNDMWPanelObject_GetPublishedMetaObject(void) {
    return g_beNDMWPanelObject_metaObject;
}

static FieldFactory g_beNDMWPanelObjectStat_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWPanelObjectStat_fieldTable[] = {
    "_listFolder",
    "_listColor",
    "_playerWork",
};
static igMetaField **g_beNDMWPanelObjectStat_fieldHandles[] = {
    &g_beNDMWPanelObjectStat_listFolderMetaField,
    &g_beNDMWPanelObjectStat_listColorMetaField,
    &g_beNDMWPanelObjectStat_playerWorkMetaField,
};
static int g_beNDMWPanelObjectStat_fieldOffsets[] = {
    60,
    64,
    68,
};

void beNDMWPanelObjectStat_InitFields(void) {
    int base;
    int pageIndex;
    void **inheritedPage;
    igObjectRefMetaField *listFolder;
    igObjectRefMetaField *listColor;
    igObjectRefMetaField *playerWork;
    igMetaObject *meta;
    igIntMetaField *pageField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (igMetaObject *)(g_beNDMWPanelObjectStat_metaObject);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWPanelObjectStat_ctorTable, 3);
    inheritedPage = (void **)(igMetaObject_FindFieldByName(meta, "_page"));
    pageIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)meta->_metaFields, (int)inheritedPage);
    pageField = (igIntMetaField *)((igObjectDispatchView *)inheritedPage)->CloneViaMetadata(1);
    ((Gap::Core::igIntMetaField *)pageField)->setDefault(2);
    pageField->_externalEnumStorage = (int)(&g_beNDMWPanelObjectStat_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, pageIndex, (igMetaField *)pageField);
    pageField->release();
    listFolder = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base));
    listFolder->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    listFolder->_construct = 1;
    listColor = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base + 1));
    listColor->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    listColor->_construct = 1;
    playerWork = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base + 2));
    playerWork->_metaObject = (int)beNDMWMdlPlayerInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWPanelObjectStat_fieldTable, g_beNDMWPanelObjectStat_fieldHandles, g_beNDMWPanelObjectStat_fieldOffsets, base);
}

