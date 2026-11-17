igMetaObject *g_beFont_metaObject;
igMetaField *g_beFont_rootMetaField;
igMetaField *g_beFont_fontsMetaField;
igMetaField *g_beFont_fontIdxMetaField;
igMetaField *g_beFont_gaPairListMetaField;
igMetaField *g_beFont_lineFeedListMetaField;
igMetaField *g_beFont_alignListMetaField;
igMetaField *g_beFont_convertDataMetaField;
igMetaField *g_beFont_condition00MetaField;
igMetaField *g_beFont_condition01MetaField;
igMetaField *g_beFont_historyMetaField;

beFont *beFont_CreateInstance(int allocator) {
    beFont_EnsureRegistered();
    return (beFont *)igMetaObject_CreateInstance(g_beFont_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beFont_GetOrCreateMetaObject(void) {
    if (g_beFont_metaObject == 0) {
        g_beFont_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beFont_metaObject;
}

void *beFont_GetMetaObject(void) {
    igMetaObject *g = g_beFont_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beFont_EnsureRegistered();
    }
    return g_beFont_metaObject;
}

int beFont_GetVTable(void) {
    beFont obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    obj._vtable = (int)&g_beFont_vtable[0];
    obj._root = 0;
    obj._fonts = 0;
    obj._gaPairList = 0;
    obj._lineFeedList = 0;
    obj._alignList = 0;
    obj._convertData = 0;
    obj._condition00 = 0;
    obj._condition01 = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beFont_vtable[0];
    igStringRef_Destruct((igStringRef *)&obj._condition01, -1);
    igStringRef_Destruct((igStringRef *)&obj._condition00, -1);
    igSmartPointer_igStringObj_Destruct((igSmartPointer<igObject> *)&obj._convertData, -1);
    igSmartPointer_igFloatList_Destruct((igSmartPointer<igObject> *)&obj._alignList, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._lineFeedList, -1);
    igSmartPointer_beFontGeomAttrPairList_Destruct((igSmartPointer<igObject> *)&obj._gaPairList, (short)(-1));
    igSmartPointer_beFontImageList_Destruct((igSmartPointer<igObject> *)&obj._fonts, -1);
    igSmartPointer_igAttrSet_Destruct((igSmartPointer<igObject> *)&obj._root, -1);
    beBaseInfoManager_Destroy((beBaseInfoManager *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beFontImageList_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beFontGeomAttrPairList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void beFont_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFont_Register);
}

static igMetaObjectCallback g_beFont_callbackList[] = { igAttrSet_EnsureRegistered, beFontImageList_EnsureRegistered, beFontGeomAttrPairList_EnsureRegistered, igIntList_EnsureRegistered, igFloatList_EnsureRegistered, igStringObj_EnsureRegistered, 0 };

CallbackArray *beFont_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFont_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beFont_GetMetaObjectFunction,
        "beFont",
        0x48, /* instance size */
        beFont_GetVTable,
        beFont_InitFields,
        0, /* extra callback item */
        g_beFont_callbackList /* callback list */
    );
}

void beFont_GetMetaObjectFunction(void)
{
    beFont_GetMetaObject();
}

static FieldFactory g_beFont_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beFont_fieldTable[] = {
    "_root",
    "_fonts",
    "_fontIdx",
    "_gaPairList",
    "_lineFeedList",
    "_alignList",
    "_convertData",
    "_condition00",
    "_condition01",
    "_history",
};
static igMetaField **g_beFont_fieldHandles[] = {
    &g_beFont_rootMetaField,
    &g_beFont_fontsMetaField,
    &g_beFont_fontIdxMetaField,
    &g_beFont_gaPairListMetaField,
    &g_beFont_lineFeedListMetaField,
    &g_beFont_alignListMetaField,
    &g_beFont_convertDataMetaField,
    &g_beFont_condition00MetaField,
    &g_beFont_condition01MetaField,
    &g_beFont_historyMetaField,
};
static int g_beFont_fieldOffsets[] = {
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
};

void beFont_InitFields(void) {
    void *root;
    void *fonts;
    void *gaPairList;
    void *lineFeedList;
    void *alignList;
    void *convertData;
    void *meta;
    int base;

    meta = (void *)g_beFont_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beFont_ctorTable, 0xA);
    root = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base));
    ((igObjectRefMetaField *)root)->_metaObject = (int)igAttrSet_GetOrCreateMetaObject();
    fonts = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    ((igObjectRefMetaField *)fonts)->_metaObject = (int)beFontImageList_GetOrCreateMetaObject();
    ((igRefMetaField *)fonts)->_construct = 1;
    gaPairList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3));
    ((igObjectRefMetaField *)gaPairList)->_metaObject = (int)beFontGeomAttrPairList_GetOrCreateMetaObject();
    ((igRefMetaField *)gaPairList)->_construct = 1;
    lineFeedList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4));
    ((igObjectRefMetaField *)lineFeedList)->_metaObject = (int)igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)lineFeedList)->_construct = 1;
    alignList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5));
    ((igObjectRefMetaField *)alignList)->_metaObject = (int)igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)alignList)->_construct = 1;
    convertData = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6));
    ((igObjectRefMetaField *)convertData)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    ((igRefMetaField *)convertData)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beFont_fieldTable, g_beFont_fieldHandles, g_beFont_fieldOffsets, base);
}

