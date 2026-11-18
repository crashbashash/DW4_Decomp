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

beNDMWPanelWazaInfoWork *beNDMWPanelWazaInfoWork_Create(int allocator) {
    beNDMWPanelWazaInfoWork_EnsureRegistered();
    return (beNDMWPanelWazaInfoWork *)igMetaObject_CreateInstance(g_beNDMWPanelWazaInfoWork_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWPanelWazaInfoWork_GetOrCreateMetaObject(void) {
    if (g_beNDMWPanelWazaInfoWork_metaObject == 0) {
        g_beNDMWPanelWazaInfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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
    beNDMWPanelWazaInfoWork obj;
    int vtable;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWPanelWazaInfoWork_vtable[0];
    obj._panelWaza = 0;
    obj._panelItem = 0;
    obj._panelStat = 0;
    obj._retWazaLabel = 0;
    obj._playerWork = 0;
    obj._textSetList = 0;
    obj._textColorList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWPanelWazaInfoWork_vtable[0];
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._textColorList, -1);
    igSmartPointer_igStringRefList_Destruct((igSmartPointer<igObject> *)&obj._textSetList, -1);
    igSmartPointer_beNDMWMdlPlayerInfoWork_Destruct((igSmartPointer<igObject> *)&obj._playerWork, -1);
    igStringRef_Destruct((igStringRef *)&obj._retWazaLabel, -1);
    igSmartPointer_beNDMWPanelObjectStat_Destruct((igSmartPointer<igObject> *)&obj._panelStat, -1);
    igSmartPointer_beNDMWPanelObjectItem_Destruct((igSmartPointer<igObject> *)&obj._panelItem, -1);
    igSmartPointer_beNDMWPanelObjectWaza_Destruct((igSmartPointer<igObject> *)&obj._panelWaza, -1);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWPanelObjectWaza_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beNDMWPanelObjectItem_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beNDMWPanelObjectStat_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlPlayerInfoWork_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
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

void beNDMWPanelWazaInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelWazaInfoWork_Register);
}

static igMetaObjectCallback g_beNDMWPanelWazaInfoWork_callbackList[] = { beNDMWPanelObjectWaza_EnsureRegistered, beNDMWPanelObjectItem_EnsureRegistered, beNDMWPanelObjectStat_EnsureRegistered, beNDMWMdlPlayerInfoWork_EnsureRegistered, igStringRefList_EnsureRegistered, igIntList_EnsureRegistered, 0 };

CallbackArray *beNDMWPanelWazaInfoWork_Register(void) {
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
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWPanelWazaInfoWork_ctorTable, 0xB);
    panelWaza = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3));
    ((igObjectRefMetaField *)panelWaza)->_metaObject = (int)beNDMWPanelObjectWaza_GetOrCreateMetaObject();
    ((igRefMetaField *)panelWaza)->_construct = 1;
    panelItem = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4));
    ((igObjectRefMetaField *)panelItem)->_metaObject = (int)beNDMWPanelObjectItem_GetOrCreateMetaObject();
    ((igRefMetaField *)panelItem)->_construct = 1;
    panelStat = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5));
    ((igObjectRefMetaField *)panelStat)->_metaObject = (int)beNDMWPanelObjectStat_GetOrCreateMetaObject();
    ((igRefMetaField *)panelStat)->_construct = 1;
    playerWork = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8));
    ((igObjectRefMetaField *)playerWork)->_metaObject = (int)beNDMWMdlPlayerInfoWork_GetOrCreateMetaObject();
    textSetList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9));
    ((igObjectRefMetaField *)textSetList)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)textSetList)->_construct = 1;
    textColorList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xA));
    ((igObjectRefMetaField *)textColorList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)textColorList)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWPanelWazaInfoWork_fieldTable, g_beNDMWPanelWazaInfoWork_fieldHandles, g_beNDMWPanelWazaInfoWork_fieldOffsets, base);
}

