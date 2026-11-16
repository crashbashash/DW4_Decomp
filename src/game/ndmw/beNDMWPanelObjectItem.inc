igMetaObject *g_beNDMWPanelObjectItem_metaObject;
int g_beNDMWPanelObjectItem_nameExternalEnumStorage;
igMetaField *g_beNDMWPanelObjectItem_listFolderMetaField;
igMetaField *g_beNDMWPanelObjectItem_listColorMetaField;

igMetaObject *beNDMWPanelObjectItem_GetOrCreateMetaObject(void) {
    if (g_beNDMWPanelObjectItem_metaObject == 0) {
        g_beNDMWPanelObjectItem_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    struct Obj_3be640 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w9 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.vt = &g_beNDMWPanelObjectItem_vtable[0];
    obj.w15 = 0;
    obj.w16 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWPanelObjectItem_vtable[0];
    igSmartPointer_igIntList_Destruct(&obj.w16, -1);
    igSmartPointer_igObjectList_Destruct(&obj.w15, -1);
    FUN_003be240((Obj_3be240 *)&obj, (short)0);
    return t;
}

void beNDMWPanelObjectItem_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObjectItem_Register);
}

static igMetaObjectCallback g_beNDMWPanelObjectItem_callbackList[] = { igObjectList_EnsureRegistered, igIntList_EnsureRegistered, 0 };

void *beNDMWPanelObjectItem_Register(void) {
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
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWPanelObjectItem_ctorTable, 2);
    inheritedPage = (void **)(igMetaObject_FindFieldByName(meta, "_page"));
    pageIndex = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, inheritedPage);
    pageField = (igIntMetaField *)(((DW4VC_84_1 *)(inheritedPage))->vX((int)(1)));
    igIntMetaField_SetDefault(pageField, 1);
    pageField->_externalEnumStorage = (int)(&g_beNDMWPanelObjectItem_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, pageIndex, pageField);
    pageField->_refCount = pageField->_refCount - 1;
    if (((unsigned long long)(long long)pageField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(pageField);
    }
    listFolder = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((FT *)listFolder)->meta = igObjectList_GetOrCreateMetaObject();
    ((FT *)listFolder)->flag = 1;
    listColor = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((FT *)listColor)->meta = igIntList_GetOrCreateMetaObject();
    ((FT *)listColor)->flag = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWPanelObjectItem_fieldTable, g_beNDMWPanelObjectItem_fieldHandles, g_beNDMWPanelObjectItem_fieldOffsets, base);
}

