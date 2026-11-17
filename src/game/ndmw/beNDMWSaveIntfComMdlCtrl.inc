igMetaObject *g_beNDMWSaveIntfComMdlCtrl_metaObject;
int g_beNDMWSaveIntfComMdlCtrl_nameExternalEnumStorage;
igMetaField *g_beNDMWSaveIntfComMdlCtrl_messengerMetaField;
igMetaField *g_beNDMWSaveIntfComMdlCtrl_openDataListMetaField;
igMetaField *g_beNDMWSaveIntfComMdlCtrl_closeDataListMetaField;
igMetaField *g_beNDMWSaveIntfComMdlCtrl_posMetaField;

igMetaObject *beNDMWSaveIntfComMdlCtrl_GetMetaObject(void) {
    if (g_beNDMWSaveIntfComMdlCtrl_metaObject == 0 || !isValid(g_beNDMWSaveIntfComMdlCtrl_metaObject)) beNDMWSaveIntfComMdlCtrl_EnsureRegistered();
    return g_beNDMWSaveIntfComMdlCtrl_metaObject;
}

int beNDMWSaveIntfComMdlCtrl_GetVTable(void) {
    beNDMWSaveIntfComMdlCtrl obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    *(int **)&obj._vtable = &g_beNDMWSaveIntfComMdlCtrl_vtable[0];
    obj._openDataList = 0;
    obj._closeDataList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWSaveIntfComMdlCtrl_vtable[0];
    igSmartPointer_beSaveIntfComMdlDataList_Destruct((igSmartPointer<igObject> *)&obj._closeDataList, -1);
    igSmartPointer_beSaveIntfComMdlDataList_Destruct((igSmartPointer<igObject> *)&obj._openDataList, -1);
    beBaseInfoData_Destroy((beBaseInfoData *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beSaveIntfComMdlDataList_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
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

void beNDMWSaveIntfComMdlCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntfComMdlCtrl_Register);
}

static igMetaObjectCallback g_beNDMWSaveIntfComMdlCtrl_callbackList[] = { beMessenger_EnsureRegistered, beSaveIntfComMdlDataList_EnsureRegistered, 0 };

CallbackArray *beNDMWSaveIntfComMdlCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWSaveIntfComMdlCtrl_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWSaveIntfComMdlCtrl_GetMetaObjectFunction,
        "beNDMWSaveIntfComMdlCtrl",
        0x28, /* instance size */
        beNDMWSaveIntfComMdlCtrl_GetVTable,
        beNDMWSaveIntfComMdlCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWSaveIntfComMdlCtrl_callbackList /* callback list */
    );
}

void beNDMWSaveIntfComMdlCtrl_GetMetaObjectFunction(void)
{
    beNDMWSaveIntfComMdlCtrl_GetMetaObject();
}

static FieldFactory g_beNDMWSaveIntfComMdlCtrl_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igVec3fMetaField_CreateInstance,
};
static const char *g_beNDMWSaveIntfComMdlCtrl_fieldTable[] = {
    "_messenger",
    "_openDataList",
    "_closeDataList",
    "_pos",
};
static igMetaField **g_beNDMWSaveIntfComMdlCtrl_fieldHandles[] = {
    &g_beNDMWSaveIntfComMdlCtrl_messengerMetaField,
    &g_beNDMWSaveIntfComMdlCtrl_openDataListMetaField,
    &g_beNDMWSaveIntfComMdlCtrl_closeDataListMetaField,
    &g_beNDMWSaveIntfComMdlCtrl_posMetaField,
};
static int g_beNDMWSaveIntfComMdlCtrl_fieldOffsets[] = {
    16,
    20,
    24,
    28,
};

void beNDMWSaveIntfComMdlCtrl_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *messenger;
    void *openDataList;
    void *closeDataList;
    igMetaObject *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (igMetaObject *)(g_beNDMWSaveIntfComMdlCtrl_metaObject);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWSaveIntfComMdlCtrl_ctorTable, 4);
    inheritedName = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)meta->_metaFields, (int)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    igStringMetaField_SetDefaultText((igMetaField *)nameField, "COMMDLCTRL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWSaveIntfComMdlCtrl_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, nameIndex, (igMetaField *)nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    messenger = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    openDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)openDataList)->_metaObject = (int)beSaveIntfComMdlDataList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)openDataList)->_construct = 1;
    closeDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)closeDataList)->_metaObject = (int)beSaveIntfComMdlDataList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)closeDataList)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWSaveIntfComMdlCtrl_fieldTable, g_beNDMWSaveIntfComMdlCtrl_fieldHandles, g_beNDMWSaveIntfComMdlCtrl_fieldOffsets, base);
}

