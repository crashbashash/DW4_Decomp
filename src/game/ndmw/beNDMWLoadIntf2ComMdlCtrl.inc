igMetaObject *g_beNDMWLoadIntf2ComMdlCtrl_metaObject;
int g_beNDMWLoadIntf2ComMdlCtrl_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2ComMdlCtrl_messengerMetaField;
igMetaField *g_beNDMWLoadIntf2ComMdlCtrl_openDataListMetaField;
igMetaField *g_beNDMWLoadIntf2ComMdlCtrl_closeDataListMetaField;
igMetaField *g_beNDMWLoadIntf2ComMdlCtrl_posMetaField;

beNDMWLoadIntf2ComMdlCtrl *beNDMWLoadIntf2ComMdlCtrl_Create(int allocator) {
    beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered();
    return (beNDMWLoadIntf2ComMdlCtrl *)igMetaObject_CreateInstance(g_beNDMWLoadIntf2ComMdlCtrl_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWLoadIntf2ComMdlCtrl_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadIntf2ComMdlCtrl_metaObject == 0) {
        g_beNDMWLoadIntf2ComMdlCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWLoadIntf2ComMdlCtrl_metaObject;
}

void *beNDMWLoadIntf2ComMdlCtrl_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2ComMdlCtrl_metaObject;
    bool ready;
    if (g) {
        /* matching construct: the bool compared against false keeps the retail sltu normalisation under the
         * unit profile (exceptions on); `if (ready = ...)` folds it away */
        ready = g->_validity & 4;
        if (ready != false) goto end;
    }
    beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered();
end:
    return g_beNDMWLoadIntf2ComMdlCtrl_metaObject;
}

int beNDMWLoadIntf2ComMdlCtrl_GetVTable(void) {
    beNDMWLoadIntf2ComMdlCtrl obj;
    int vtable;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2ComMdlCtrl_vtable[0];
    obj._name = 0;
    obj._openDataList = 0;
    obj._closeDataList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2ComMdlCtrl_vtable[0];
    igSmartPointer_beLoadIntf2ComMdlDataList_Destruct((igSmartPointer<igObject> *)&obj._closeDataList, -1);
    igSmartPointer_beLoadIntf2ComMdlDataList_Destruct((igSmartPointer<igObject> *)&obj._openDataList, -1);
    beBaseInfoData_Destroy((beBaseInfoData *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beLoadIntf2ComMdlDataList_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
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

void beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2ComMdlCtrl_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2ComMdlCtrl_callbackList[] = { beMessenger_EnsureRegistered, beLoadIntf2ComMdlDataList_EnsureRegistered, 0 };

CallbackArray *beNDMWLoadIntf2ComMdlCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2ComMdlCtrl_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2ComMdlCtrl_GetMetaObject,
        "beNDMWLoadIntf2ComMdlCtrl",
        0x28, /* instance size */
        beNDMWLoadIntf2ComMdlCtrl_GetVTable,
        beNDMWLoadIntf2ComMdlCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2ComMdlCtrl_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2ComMdlCtrl_GetMetaObject(void)
{
    beNDMWLoadIntf2ComMdlCtrl_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2ComMdlCtrl_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igVec3fMetaField_CreateInstance,
};
static const char *g_beNDMWLoadIntf2ComMdlCtrl_fieldTable[] = {
    "_messenger",
    "_openDataList",
    "_closeDataList",
    "_pos",
};
static igMetaField **g_beNDMWLoadIntf2ComMdlCtrl_fieldHandles[] = {
    &g_beNDMWLoadIntf2ComMdlCtrl_messengerMetaField,
    &g_beNDMWLoadIntf2ComMdlCtrl_openDataListMetaField,
    &g_beNDMWLoadIntf2ComMdlCtrl_closeDataListMetaField,
    &g_beNDMWLoadIntf2ComMdlCtrl_posMetaField,
};
static int g_beNDMWLoadIntf2ComMdlCtrl_fieldOffsets[] = {
    16,
    20,
    24,
    28,
};

void beNDMWLoadIntf2ComMdlCtrl_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *messenger;
    void *openDataList;
    void *closeDataList;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWLoadIntf2ComMdlCtrl_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadIntf2ComMdlCtrl_ctorTable, 4);
    inheritedName = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)((char *)((igMetaObject *)meta)->_metaFields), (int)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    ((Gap::Core::igStringMetaField *)nameField)->setDefault("COMMDLCTRL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2ComMdlCtrl_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, nameIndex, (igMetaField *)nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    messenger = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    openDataList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    ((igObjectRefMetaField *)openDataList)->_metaObject = (int)beLoadIntf2ComMdlDataList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)openDataList)->_construct = 1;
    closeDataList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2));
    ((igObjectRefMetaField *)closeDataList)->_metaObject = (int)beLoadIntf2ComMdlDataList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)closeDataList)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadIntf2ComMdlCtrl_fieldTable, g_beNDMWLoadIntf2ComMdlCtrl_fieldHandles, g_beNDMWLoadIntf2ComMdlCtrl_fieldOffsets, base);
}

