igMetaObject *g_beNDMWPanelWazaInfoWork_metaObject;
igMetaField *g_beNDMWPanelWazaInfoWork_pageMetaField;
igMetaField *g_beNDMWPanelWazaInfoWork_isWindowGenerateMetaField;
igMetaField *g_beNDMWPanelWazaInfoWork_isCursorGenerateMetaField;
igMetaField *g_beNDMWPanelWazaInfoWork_panelWazaMetaField;
igMetaField *g_beNDMWPanelWazaInfoWork_panelItemMetaField;
igMetaField *g_beNDMWPanelWazaInfoWork_panelStatMetaField;
igMetaField *g_beNDMWPanelWazaInfoWork_retIsFireMetaField;
igMetaField *g_beNDMWPanelWazaInfoWork_retWazaLabelMetaField;
igMetaField *g_beNDMWPanelWazaInfoWork_playerWorkMetaField;
igMetaField *g_beNDMWPanelWazaInfoWork_textSetListMetaField;
igMetaField *g_beNDMWPanelWazaInfoWork_textColorListMetaField;

void beNDMWPanelWazaInfoWork_Create(int allocator) {
    beNDMWPanelWazaInfoWork_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWPanelWazaInfoWork_metaObject, allocator);
}

igMetaObject *beNDMWPanelWazaInfoWork_GetOrCreateMetaObject(void) {
    if (g_beNDMWPanelWazaInfoWork_metaObject == 0) {
        g_beNDMWPanelWazaInfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWPanelWazaInfoWork_metaObject;
}

igMetaObject *beNDMWPanelWazaInfoWork_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWPanelWazaInfoWork_metaObject != 0) {
        ready = (g_beNDMWPanelWazaInfoWork_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    beNDMWPanelWazaInfoWork_EnsureRegistered();
done:
    return g_beNDMWPanelWazaInfoWork_metaObject;
}

int beNDMWPanelWazaInfoWork_GetVTable(void) {
    struct Obj_3bdbf0 obj;
    int temp_s5;

    igObject_InitHeader(&obj);
    obj.vt = (&g_beNDMWPanelWazaInfoWork_vtable[0]);
    obj.f10 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.f20 = 0;
    obj.f24 = 0;
    obj.f28 = 0;
    obj.f2C = 0;
    temp_s5 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&g_beNDMWPanelWazaInfoWork_vtable[0]);
    igSmartPointer_igIntList_Destruct(&obj.f2C, -1);
    igSmartPointer_igStringRefList_Destruct(&obj.f28, -1);
    FUN_003bde80((igSmartPointer<igObject> *)&obj.f24, -1);
    igStringRef_Destruct(&obj.f20, -1);
    FUN_003bde00((igSmartPointer<igObject> *)&obj.f18, -1);
    FUN_003bdd80((igSmartPointer<igObject> *)&obj.f14, -1);
    FUN_003bdd00((igSmartPointer<igObject> *)&obj.f10, -1);
    return temp_s5;
}

igSmartPointer<igObject> *FUN_003bdd00(igSmartPointer<igObject> *self,int delete_storage) {
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

igSmartPointer<igObject> *FUN_003bdd80(igSmartPointer<igObject> *self,int delete_storage) {
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

igSmartPointer<igObject> *FUN_003bde00(igSmartPointer<igObject> *self,int delete_storage) {
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

igSmartPointer<igObject> *FUN_003bde80(igSmartPointer<igObject> *self,int delete_storage) {
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

void beNDMWPanelWazaInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelWazaInfoWork_Register);
}

static igMetaObjectCallback g_beNDMWPanelWazaInfoWork_callbackList[] = { beNDMWPanelObjectWaza_EnsureRegistered, beNDMWPanelObjectItem_EnsureRegistered, beNDMWPanelObjectStat_EnsureRegistered, beNDMWMdlPlayerInfoWork_EnsureRegistered, igStringRefList_EnsureRegistered, igIntList_EnsureRegistered, 0 };

void *beNDMWPanelWazaInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWPanelWazaInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWPanelWazaInfoWork_GetMetaObject,
        "beNDMWPanelWazaInfoWork",
        0x30, /* instance size */
        beNDMWPanelWazaInfoWork_GetVTable,
        beNDMWPanelWazaInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelWazaInfoWork_callbackList /* callback list */
    );
}

void beNDMWPanelWazaInfoWork_GetMetaObject(void)
{
    beNDMWPanelWazaInfoWork_ResolveMetaObject();
}

static FieldFactory g_beNDMWPanelWazaInfoWork_ctorTable[] = {
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWPanelWazaInfoWork_fieldTable[] = {
    "_page",
    "_isWindowGenerate",
    "_isCursorGenerate",
    "_panelWaza",
    "_panelItem",
    "_panelStat",
    "_retIsFire",
    "_retWazaLabel",
    "_playerWork",
    "_textSetList",
    "_textColorList",
};
static igMetaField **g_beNDMWPanelWazaInfoWork_fieldHandles[] = {
    &g_beNDMWPanelWazaInfoWork_pageMetaField,
    &g_beNDMWPanelWazaInfoWork_isWindowGenerateMetaField,
    &g_beNDMWPanelWazaInfoWork_isCursorGenerateMetaField,
    &g_beNDMWPanelWazaInfoWork_panelWazaMetaField,
    &g_beNDMWPanelWazaInfoWork_panelItemMetaField,
    &g_beNDMWPanelWazaInfoWork_panelStatMetaField,
    &g_beNDMWPanelWazaInfoWork_retIsFireMetaField,
    &g_beNDMWPanelWazaInfoWork_retWazaLabelMetaField,
    &g_beNDMWPanelWazaInfoWork_playerWorkMetaField,
    &g_beNDMWPanelWazaInfoWork_textSetListMetaField,
    &g_beNDMWPanelWazaInfoWork_textColorListMetaField,
};
static int g_beNDMWPanelWazaInfoWork_fieldOffsets[] = {
    8,
    12,
    13,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
};

void beNDMWPanelWazaInfoWork_InitFields(void) {
    void *panelWaza;
    void *panelItem;
    void *panelStat;
    void *playerWork;
    void *textSetList;
    void *textColorList;
    void *meta;
    int base;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)g_beNDMWPanelWazaInfoWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWPanelWazaInfoWork_ctorTable, 0xB);
    panelWaza = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)panelWaza)->_metaObject = (int)beNDMWPanelObjectWaza_GetOrCreateMetaObject();
    ((igRefMetaField *)panelWaza)->_construct = 1;
    panelItem = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)panelItem)->_metaObject = (int)beNDMWPanelObjectItem_GetOrCreateMetaObject();
    ((igRefMetaField *)panelItem)->_construct = 1;
    panelStat = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)panelStat)->_metaObject = (int)beNDMWPanelObjectStat_GetOrCreateMetaObject();
    ((igRefMetaField *)panelStat)->_construct = 1;
    playerWork = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)playerWork)->_metaObject = (int)beNDMWMdlPlayerInfoWork_GetOrCreateMetaObject();
    textSetList = (void *)(igMetaObject_GetFieldAt(meta, base + 9));
    ((igObjectRefMetaField *)textSetList)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)textSetList)->_construct = 1;
    textColorList = (void *)(igMetaObject_GetFieldAt(meta, base + 0xA));
    ((igObjectRefMetaField *)textColorList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)textColorList)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWPanelWazaInfoWork_fieldTable, g_beNDMWPanelWazaInfoWork_fieldHandles, g_beNDMWPanelWazaInfoWork_fieldOffsets, base);
}

