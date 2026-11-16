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
    struct Obj_3bc240 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &g_beNDMWSaveIntfComMdlCtrl_vtable[0];
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWSaveIntfComMdlCtrl_vtable[0];
    FUN_003bc2d0((igSmartPointer<igObject> *)&obj.w6, -1);
    FUN_003bc2d0((igSmartPointer<igObject> *)&obj.w5, -1);
    FUN_00344030(&obj, 0);
    return t;
}

igSmartPointer<igObject> *FUN_003bc2d0(igSmartPointer<igObject> *self,int delete_storage) {
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

void beNDMWSaveIntfComMdlCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntfComMdlCtrl_Register);
}

static igMetaObjectCallback g_beNDMWSaveIntfComMdlCtrl_callbackList[] = { beMessenger_EnsureRegistered, beSaveIntfComMdlDataList_EnsureRegistered, 0 };

void *beNDMWSaveIntfComMdlCtrl_Register(void) {
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
    FUN_00187890,
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
    nameIndex = ObjectPointerList_FindIndex(meta->_metaFields, inheritedName);
    nameField = (igStringMetaField *)(((DW4VC_84_1 *)(inheritedName))->vX((int)(1)));
    igStringMetaField_SetDefaultText(nameField, "COMMDLCTRL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWSaveIntfComMdlCtrl_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, nameIndex, nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    messenger = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)messenger)->_metaObject = beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    openDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)openDataList)->_metaObject = (int)beSaveIntfComMdlDataList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)openDataList)->_construct = 1;
    closeDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)closeDataList)->_metaObject = (int)beSaveIntfComMdlDataList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)closeDataList)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWSaveIntfComMdlCtrl_fieldTable, g_beNDMWSaveIntfComMdlCtrl_fieldHandles, g_beNDMWSaveIntfComMdlCtrl_fieldOffsets, base);
}

