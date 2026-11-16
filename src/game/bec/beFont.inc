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

void beFont_CreateInstance(int allocator) {
    beFont_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589678, allocator);
}

igMetaObject *beFont_GetOrCreateMetaObject(void) {
    if (g_beFont_metaObject == 0) {
        g_beFont_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    struct Obj_361f30 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &g_beFont_vtable[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beFont_vtable[0];
    igStringRef_Destruct(&obj.w16, -1);
    igStringRef_Destruct(&obj.w15, -1);
    igSmartPointer_igStringObj_Destruct(&obj.w14, -1);
    FUN_001354b0(&obj.w13, -1);
    igSmartPointer_igIntList_Destruct(&obj.w12, -1);
    FUN_003620f0((igSmartPointer<igObject> *)&obj.w11, (short)(-1));
    FUN_00362070((igSmartPointer<igObject> *)&obj.w9, -1);
    FUN_001d97f0(&obj.w8, -1);
    FUN_0033f5e0((O_33f5e0 *)&obj, (short)0);
    return t;
}

igSmartPointer<igObject> *FUN_00362070(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_003620f0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beFont_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFont_Register);
}

static igMetaObjectCallback g_beFont_callbackList[] = { igAttrSet_EnsureRegistered, beFontImageList_EnsureRegistered, beFontGeomAttrPairList_EnsureRegistered, igIntList_EnsureRegistered, igFloatList_EnsureRegistered, igStringObj_EnsureRegistered, 0 };

void *beFont_Register(void) {
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
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beFont_ctorTable, 0xA);
    root = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)root)->_metaObject = igAttrSet_GetOrCreateMetaObject();
    fonts = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)fonts)->_metaObject = (int)beFontImageList_GetOrCreateMetaObject();
    ((igRefMetaField *)fonts)->_construct = 1;
    gaPairList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)gaPairList)->_metaObject = (int)beFontGeomAttrPairList_GetOrCreateMetaObject();
    ((igRefMetaField *)gaPairList)->_construct = 1;
    lineFeedList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)lineFeedList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)lineFeedList)->_construct = 1;
    alignList = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)alignList)->_metaObject = igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)alignList)->_construct = 1;
    convertData = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)convertData)->_metaObject = igStringObj_GetOrCreateMetaObject();
    ((igRefMetaField *)convertData)->_construct = 1;
    igMetaObject_NameFields(meta, g_beFont_fieldTable, g_beFont_fieldHandles, g_beFont_fieldOffsets, base);
}

